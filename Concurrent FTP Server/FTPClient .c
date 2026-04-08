//////////////////////////////////////////////////////////////////////////////////////////////////
//
//                Client Application
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
//      Function Name   : ReadLine
//      Description     : It is used to write the data into line recived from server
//      Input           : Server Socket number, data recived from server(out parameter), number of byes recived from server
//      Output          : number of bytes
//      Author          : Aditya Vijay Mali
//      Date            : 08/02/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////


int ReadLine(int Sock,char *line,int max)
{
    int i = 0;
    char ch = '\0';
    int n = 0;

    while(i < max - 1)
    {
        n = read(Sock,&ch,1);

        if(n <= 0)
        {
            break;
        }

        line[i++] = ch;

        if(ch == '\n')
        {
            break;
        }
    }   // End of while
    line[i] = '\0';

    return i;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//
//      Commandline argument application
//      1st Argument : IP Adderss 
//      2nd Argument : Port number
//      3rd Argument : Target File name
//      4th Argument : New File Name
//
//      ./Client    127.0.0.1    9000   Demo.txt    a.txt
//      argv[0]     argv[1]     argv[2] argv[3]     argv[4]
//
//      argc = 5
//
//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//
//      Entry Point function for the application
//      Description     : It is used to request a file from 'server' if server has that file it will
//                        return the header as file exists or not and size of that file (in bytes).
//                        if server sends a positive signal then this function creats a new file and 
//                        writes the data into it.
//      Date            : 08/02/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc,char *argv[])
{
    int Port = 0;                   // argv[2]
    int Sock = 0;
    int iRet = 0;

    char *ip = NULL;                // argv[1]
    char *Filename = NULL;          // argv[3]
    char *OutFilename = NULL;       // argv[4]

    char Header[64] = {'\0'};
    
    struct sockaddr_in ServerAddr;

    if(argc < 5 || argc > 5)
    {
        printf("Unable to proceed as invalid number of arguments");

        printf("Please provide below arguments \n");
        
        printf("1st Argument : IP Adderss \n");
        printf("2nd Argument : Port number");
        printf("3rd Argument : Target File name\n");
        printf("4th Argument : New File Name");

        return -1;
    }

    // Store command line arguments into the variables
    ip = argv[1];
    Port = atoi(argv[2]);
    Filename = argv[3];
    OutFilename = argv[4];

    /////////////////////////////////////////////////////////////////////////////
    //      Step 1 : Create TCP socket
    /////////////////////////////////////////////////////////////////////////////
    
    Sock = socket(AF_INET,SOCK_STREAM,0);

    if(Sock < 0)
    {
        printf("Unable to create the Client socket \n");
        return -1;
    }

    /////////////////////////////////////////////////////////////////////////////
    //      Step 2 : Connect with server
    /////////////////////////////////////////////////////////////////////////////

    memset(&ServerAddr,0,sizeof(ServerAddr));

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(Port);


    // Convrt the IP address into binary format
    inet_pton(AF_INET,ip,&ServerAddr.sin_addr);

    iRet = connect(Sock,(struct sockaddr *)&ServerAddr,sizeof(ServerAddr));

    if(iRet == -1)
    {
        printf("Unable to connect with server \n");
        
        close(Sock);
        
        return -1;
    }

    /////////////////////////////////////////////////////////////////////////////
    //      Step 9 : Send file name
    /////////////////////////////////////////////////////////////////////////////

    write(Sock,Filename,strlen(Filename));
    write(Sock,"\n",1);

    /////////////////////////////////////////////////////////////////////////////
    //      Step 4 : Read the Header
    /////////////////////////////////////////////////////////////////////////////
    iRet = ReadLine(Sock,Header,sizeof(Header));

    if(iRet <= 0)
    {
        printf("Server gets Disconnected abnormally\n");
        close(Sock);
        return -1;
    }

    long FileSize = 0;

    printf("Header line received from Server %s\n",Header);

    sscanf(Header,"OK %ld",&FileSize);

    printf("File size received from Server : %ld\n",FileSize);

    /////////////////////////////////////////////////////////////////////////////
    //      Step 5 : Create new file
    /////////////////////////////////////////////////////////////////////////////

    int outfd = 0;

    outfd = open(OutFilename, O_CREAT | O_WRONLY | O_TRUNC,0777);

    if(outfd < 0)
    {
        printf("Unable to create downloaded file \n");
        return -1;
    }

    char Buffer[1024] = {'\0'};
    long received = 0;
    long remaining = 0;
    int n = 0;
    int toRead = 0;

    while(received < FileSize)
    {
        remaining = FileSize - received;

        if(remaining > 1024)
        {
            toRead = 1024;
        }
        else
        {
            toRead = remaining;
        }

        n = read(Sock,Buffer,toRead);

        write(outfd,Buffer,n);

        received = received + n;
    }

    close(outfd); // Close the new file
    close(Sock); // Close the Client socket

    if(received == FileSize)
    {
        printf("Download Successful\n");
    }
    else
    {
        printf("Download Unsuccesful\n");
    }

    return 0;
}   // End of main