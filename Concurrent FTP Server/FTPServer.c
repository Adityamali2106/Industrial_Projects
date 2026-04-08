//////////////////////////////////////////////////////////////////////////////////////////////////
//
//                Server Application
//      Author          : Aditya Vijay Mali
//      Date            : 08/02/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdbool.h>

//////////////////////////////////////////////////////////////////////////////////////////////////
//
//      Commandline argument application
//      1st Argument :   Port Number
//      ./Server    9000
//      argv[0]     argv[1]
//
//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name   : SendFileToClient
//      Description     : It is used to open the file that client requested if found then first 
//                        send the header to cliend and then send the actual data.
//      Input           : Client Socket number, Name of file
//      Output          : Nothing
//      Author          : Aditya Vijay Mali
//      Date            : 08/02/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////

void SendFileToClient(int ClientSocket,char * FileName)
{
    int fd = 0;
    struct stat sobj;
    char Buffer[1024];
    int BytesRead = 0;
    char Header[64] = {'\0'};

    printf("File name is %s : %ld \n",FileName,strlen(FileName));

    fd = open(FileName,O_RDONLY);

    // Unable to open file 
    if(fd < 0)
    {
        write(ClientSocket,"ERR\n",4);
        return;
    }

    stat(FileName,&sobj);

    // Header "OK 1700"
    snprintf(Header,sizeof(Header),"OK %ld\n",(long)sobj.st_size);

    // Write header to client
    write(ClientSocket,Header,strlen(Header));

    // Send actual file contents
    while((BytesRead = read(fd,Buffer,sizeof(Buffer))) > 0)
    {
        // Send data to client
        write(ClientSocket,Buffer,BytesRead);
    }

    close(fd);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      Entry point function for the application
//      Description : It is used to accept a client request and create a new process to handel the multiple client request. 
//                    each new process the new handels the separate client (this project usease multi processing approch).
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc,char *argv[])
{
    int ServerSocket = 0;
    int ClientSocket = 0;
    int Port = 0;
    int iRet = 0;

    char Filename[50] = {'\0'}; 
    pid_t pid = 0;

    /////////////////////////////////////////////////////////////////////////////////////
    //
    //    struct sockaddr_in {
    //        sa_family_t     sin_family;     /* AF_INET */
    //        in_port_t       sin_port;       /* Port number */
    //        struct in_addr  sin_addr;       /* IPv4 address */
    //    };
    //
    /////////////////////////////////////////////////////////////////////////////////////

    struct sockaddr_in ServerAddr;
    struct sockaddr_in ClientAddr;

    socklen_t AddrLen = sizeof(ClientAddr);

    if((argc < 2) || (argc > 2))
    {
        printf("Unable to proceed as invalid number of arguments \n");
        printf("Please provide port number \n");
        return -1;
    }

    // Port number of server
    Port = atoi(argv[1]);

    /////////////////////////////////////////////////////////////////////////////////////
    //      step 1 : Create TCP socket
    /////////////////////////////////////////////////////////////////////////////////////

    ServerSocket = socket(AF_INET,SOCK_STREAM,0);

    if(ServerSocket < 0)
    {
        printf("Unable to create server socket \n");
        return -1;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    //      step 2 : Bind socket to IP address
    /////////////////////////////////////////////////////////////////////////////////////

    memset(&ServerAddr,0,sizeof(ServerAddr));

    // Initialise the structure 

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port);
    ServerAddr.sin_addr.s_addr = INADDR_ANY;

    iRet = bind(ServerSocket,(struct sockaddr *)&ServerAddr,sizeof(ServerAddr));

    if(iRet == -1)
    {
        printf("Unable to bind\n");
        close(ServerSocket);
        return -1;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////
    //      step 3 : Listen for client connection
    /////////////////////////////////////////////////////////////////////////////////////

    iRet = listen(ServerSocket,11);

    if(iRet == -1)
    {
        printf("Server unable to listen the request \n");
        close(ServerSocket);
        return -1;
    }

    printf("Server is running on port : %d \n",Port);

    /////////////////////////////////////////////////////////////////////////////////////
    //      Loop which accepts client request continiously
    /////////////////////////////////////////////////////////////////////////////////////

    // Loop to accept multiple client request
    while(1)
    {
        ///////////////////////////////////////////////////////////////////////////////
        //      step 4 : Accept the client request
        ///////////////////////////////////////////////////////////////////////////////

        memset(&ClientAddr,0,sizeof(ClientAddr));
        
        printf("Server is wating for client request...\n");

        ClientSocket = accept(ServerSocket,(struct sockaddr *)&ClientAddr,&AddrLen);

        if(ClientSocket < 0)
        {
            printf("Unable to accept client request\n");
            continue;   // for while
        }

        printf("Client gets Connected : %s\n",inet_ntoa(ClientAddr.sin_addr));

        ///////////////////////////////////////////////////////////////////////////////
        //      step 5 : Crete new process to handel client request
        ///////////////////////////////////////////////////////////////////////////////

        pid = fork();
        if(pid < 0)
        {
            printf("Unable to create a new process for client request \n");

            close(ClientSocket);

            continue;
        }

        // New process gets created for client
        if(pid == 0)
        {
            printf("New Process is created for client request\n");

            close(ServerSocket);

            iRet = read(ClientSocket,Filename,sizeof(Filename));
            
            printf("Requested file by client : %s\n",Filename);

            Filename[strcspn(Filename,"\r\n")] = '\0';
            
            SendFileToClient(ClientSocket,Filename);

            close(ClientSocket);

            printf("File transfer done & client disconnected\n");

            exit(0);        // Kill the child process
        }   // End of if(fork)
        else
        {
            close(ClientSocket);
        }

    }   // End of while

    return 0;
}   // End of main