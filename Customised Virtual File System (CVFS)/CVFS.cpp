///////////////////////////////////////////////////////////////////////////////////////
//
//  Header File Inclusion
//
///////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <cerrno>

///////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros
//
///////////////////////////////////////////////////////////////////////////////////////

// Maximum file size that we allow in the projexct
#define MAXFILESIZE 50

#define MAXOPENFILES 20

#define MAXINODE 5

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0

#define REGULARFILE 1
#define SPECIALFILE 2

///////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros for error handling
//
///////////////////////////////////////////////////////////////////////////////////////

#define ERR_INVALID_PARAMETER -1

#define ERR_NO_INODES -2

#define ERR_FILE_ALREADY_EXIST -3
#define ERR_FILE_NOT_EXIST -4

#define ERR_PERMISSION_DENIED -5

#define ERR_INSUFFICIENT_SPACE -6
#define ERR_INSUFFICIENT_DATA -7

#define ERR_MAX_FILES_OPEN -8

///////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Structures
//
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    BootBlock
//  Discription    :    Holds the information to boot the OS
//
///////////////////////////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};

///////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    SuperBlock
//  Discription    :    Holds the information About the File System
//
///////////////////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};

///////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    Inode
//  Discription    :    Holds the Information About The File
//
///////////////////////////////////////////////////////////////////////////////////////

#pragma pack(1)
struct Inode
{
    char FileName[20];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int ReferenceCount;
    int Permission;
    char *Buffer; // Actual file Allocation Address
    struct Inode *next;
};

typedef struct Inode INODE;
typedef struct Inode *PINODE;
typedef struct Inode **PPINODE;

///////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    FileTable
//  Discription    :    Holds the information About opened file
//
///////////////////////////////////////////////////////////////////////////////////////

struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Mode;
    PINODE ptrinode;
};

typedef FileTable FILETABLE;
typedef FileTable *PFILETABLE;

///////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    UAREA
//  Discription    :    Holds the information about Process
//
///////////////////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES];
};

///////////////////////////////////////////////////////////////////////////////////////
//
//  Global variables or objects used in the Project
//
///////////////////////////////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
UAREA uareaobj;

PINODE head = NULL;

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : InitialiseUAREA
//  Description   : It is used to initialise UAREA members
//  Auther        : Aditya Vijay Mali
//  Date          : 13/01/2026
//
///////////////////////////////////////////////////////////////////////////////////////

void InitialiseUAREA()
{
    strcpy(uareaobj.ProcessName, "Myexe");

    int i = 0;
    for (i = 0; i < MAXOPENFILES; i++)
    {
        uareaobj.UFDT[i] = NULL;
    }

    printf("Marvellous CVFS : UAREA gets initialised succesfully \n");
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : InitialiseSuperBlock
//  Description   : It is used to initialise Super Block members
//  Auther        : Aditya Vijay Mali
//  Date          : 13/01/2026
//
///////////////////////////////////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    printf("Marvellous CVFS : Super block gets initialised succesfully \n");
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : CreateDILB
//  Description   : It is used to creat LinkedList of inodes
//  Auther        : Aditya Vijay Mali
//  Date          : 13/01/2026
//
///////////////////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    for (i = 0; i <= MAXINODE; i++)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        strcpy(newn->FileName, "\0");
        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->ActualFileSize = 0;
        newn->FileType = 0;
        newn->ReferenceCount = 0;
        newn->Permission = 0;
        newn->Buffer = NULL;
        newn->next = NULL;

        if (temp == NULL) // LL is Empty
        {
            head = newn;
            temp = head;
        }
        else // LL contains atlist one node
        {
            temp->next = newn;
            temp = temp->next;
        }
    }

    printf("Marvellous CVFS : DILB created succesfully \n");
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : StartAuxillaryDataInitilisation
//  Description   : It is used to call all such function which are used to initialise
//                  Auxillary data
//  Auther        : Aditya Vijay Mali
//  Date          : 13/01/2026
//
///////////////////////////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitilisation()
{
    strcpy(bootobj.Information, "Booting processs of Marvellous CVFS is done");

    printf("%s\n", bootobj.Information);

    InitialiseSuperBlock();

    CreateDILB();

    InitialiseUAREA();

    printf("Marvellous CVFS : Auxillary data initialised succesfully\n");
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : DisplayHelp
//  Description   : It is used to display the help page
//  Auther        : Aditya Vijay Mali
//  Date          : 14/01/2026
//
///////////////////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("-----------------------------------------------------------------\n");
    printf("------------- Marvellous CVFS help page succesfully -------------\n");
    printf("-----------------------------------------------------------------\n");

    printf("man     : It is used to display manual page\n");
    printf("clear   : It is use to clear the terminal\n");
    printf("creat   : It is use to create new file\n");
    printf("write   : It is use to write the data into file\n");
    printf("read    : It is use to read the data from file\n");
    printf("stat    : It is use to display statistical information \n");
    printf("unlink  : It is use to Delete the file\n");
    printf("exit    : it is used to terminate Marvellous CVFS\n");

    printf("-----------------------------------------------------------------\n");
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : ManPageDiaplay
//  Description   : It is used to display man page
//  Auther        : Aditya Vijay Mali
//  Date          : 14/01/2026
//
///////////////////////////////////////////////////////////////////////////////////////

void ManPageDiaplay(char Name[])
{
    if (strcmp("ls", Name) == 0)
    {
        printf("About : It is use to list the name of files\n");
        printf("Usage : ls\n");
    }
    else if (strcmp("man", Name) == 0)
    {
        printf("About : It is use diaplay manual page\n");
        printf("Usage : man command_name\n");
        printf("command_name : It is the name of command\n");
    }
    else if (strcmp("exit", Name) == 0)
    {
        printf("About : It is use to terminate the shell\n");
        printf("Usage : exit\n");
    }
    else if (strcmp("clear", Name) == 0)
    {
        printf("About : It is use to clear the shell\n");
        printf("Usage : clear\n");
    }

    else
    {
        printf("No manual entry for %s\n", Name);
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : IsFileExist
//  Description   : It is used to Check wather file is already exist or not
//  Input         : It accepts file name
//  Output        : It return the true or flase
//  Auther        : Aditya Vijay Mali
//  Date          : 1/01/2026
//
///////////////////////////////////////////////////////////////////////////////////////

bool IsFileExist(
    char *name // File name
)
{
    PINODE temp = head;
    bool bFalg = false;

    while (temp != NULL)
    {
        if ((strcmp(name, temp->FileName) == 0) && (temp->FileType == REGULARFILE))
        {
            bFalg = true;
            break;
        }
        temp = temp->next;
    }
    return bFalg;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : CreateFile
//  Description   : It is used to create new regular file
//  Input         : It accepts file name and permissions
//  Output        : It return the file descripter
//  Auther        : Aditya Vijay Mali
//  Date          : 1/01/2026
//
///////////////////////////////////////////////////////////////////////////////////////

int CreateFile(
    char *name,    // Name of new file
    int permission // permission for that file
)
{
    PINODE temp = head;
    int i = 0;

    printf("Total Number of Inodes remaining : %d\n", superobj.FreeInodes);

    // if name is missing
    if (name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    // if the permission value is wrong
    // permission -> 1 -> READ
    // permission -> 2 -> WRITE
    // permission -> 3 -> READ + WRITE
    if (permission < 1 || permission > 3)
    {
        return ERR_INVALID_PARAMETER;
    }

    // If the inodes are full
    if (superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;
    }

    // if file is already present
    if (IsFileExist(name) == true)
    {
        return ERR_FILE_ALREADY_EXIST;
    }

    // Search Empty Inode

    while (temp != NULL)
    {
        if (temp->FileType == 0)
        {
            break;
        }
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("There is no Inode \n");
        return ERR_NO_INODES;
    }

    // Search for empty UFDT entry
    // NOTE : 0,1,2 are reserved
    for (i = 3; i < MAXOPENFILES; i++)
    {
        if (uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }

    // UFDT is Full
    if (i == MAXFILESIZE)
    {
        return ERR_MAX_FILES_OPEN;
    }

    // Allocate memory for File table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

    // Initialise File table
    uareaobj.UFDT[i]->ReadOffset = 0;
    uareaobj.UFDT[i]->WriteOffset = 0;
    uareaobj.UFDT[i]->Mode = permission;

    // Connect File table with Inode

    uareaobj.UFDT[i]->ptrinode = temp;

    // Initialise elements of Inode
    strcpy(uareaobj.UFDT[i]->ptrinode->FileName, name);
    uareaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
    uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
    uareaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
    uareaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
    uareaobj.UFDT[i]->ptrinode->Permission = permission;

    // Allocate memory for file data

    uareaobj.UFDT[i]->ptrinode->Buffer = (char *)malloc(MAXFILESIZE);

    superobj.FreeInodes--;

    return i; // File Descriptor
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : LsFile
//  Description   : It is used to list all files
//  Input         : Nothing
//  Output        : Nothing
//  Auther        : Aditya Vijay Mali
//  Date          : 16/01/2026
//
///////////////////////////////////////////////////////////////////////////////////////

void LsFile()
{
    PINODE temp = head;

    printf("-----------------------------------------------------------------\n");
    printf("-------------- Marvellous CVFS started succesfully --------------\n");
    printf("-----------------------------------------------------------------\n");

    while (temp != NULL)
    {
        if (temp->FileType != 0)
        {
            printf("%d\t%s\t%d\n", temp->InodeNumber, temp->FileName, temp->ActualFileSize);
        }

        temp = temp->next;
    }

    printf("-----------------------------------------------------------------\n");
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : UnlinkFile
//  Description   : It is used to Delete the file
//  Input         : File Name
//  Output        : Nothing
//  Auther        : Aditya Vijay Mali
//  Date          : 22/01/2026
//
///////////////////////////////////////////////////////////////////////////////////////

int UnlinkFile(
    char *name)
{
    int i = 0;

    if (name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if (IsFileExist(name) == false)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // Travel the UFDT
    for (i = 0; i < MAXOPENFILES; i++)
    {
        if (uareaobj.UFDT[i] != NULL)
        {
            if (strcmp(uareaobj.UFDT[i]->ptrinode->FileName, name) == 0)
            {
                // Deallocate memory of Buffer
                free(uareaobj.UFDT[i]->ptrinode->Buffer);
                uareaobj.UFDT[i]->ptrinode->Buffer = NULL;

                // Reset all values of inode
                // Dont deallocate memory of inode

                uareaobj.UFDT[i]->ptrinode->FileSize = 0;
                uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
                uareaobj.UFDT[i]->ptrinode->FileType = 0;
                uareaobj.UFDT[i]->ptrinode->ReferenceCount = 0;
                uareaobj.UFDT[i]->ptrinode->Permission = 0;
                memset(uareaobj.UFDT[i]->ptrinode->FileName, '\0', sizeof(uareaobj.UFDT[i]->ptrinode->FileName));

                // Deallocate memory of file table
                free(uareaobj.UFDT[i]);

                // Set NULL to UFDT
                uareaobj.UFDT[i] = NULL;

                // Increment free inodes count
                superobj.FreeInodes++;

                break; // IMP
            } // End of if
        } // End of if
    } // End of For

    return EXECUTE_SUCCESS;
} // End of UnlinkFile

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : WriteFile
//  Description   : It is used to write the data into the file
//  Input         : File Descriptor
//                  Address of Buffer which contains data
//                  Size of data that we want to write
//  Output        : Number of bytes succesfully written
//  Auther        : Aditya Vijay Mali
//  Date          : 22/01/2026
//
///////////////////////////////////////////////////////////////////////////////////////

int WriteFile(
    int fd,
    char *data,
    int size)
{
    printf("File descriptor : %d\n", fd);
    printf("Data that we want to write : %s\n", data);
    printf("Number of bytes that we want to erite %d\n", size);

    // Invalid fd
    if (fd < 0 || fd > MAXOPENFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    // FD points to NULL
    if (uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // There is no permission to write
    if (uareaobj.UFDT[fd]->ptrinode->Permission < WRITE)
    {
        return ERR_PERMISSION_DENIED;
    }

    // Insufficient space
    if ((MAXFILESIZE - uareaobj.UFDT[fd]->WriteOffset) < size)
    {
        return ERR_INSUFFICIENT_SPACE;
    }

    // Write the data into the file

    strncpy(uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->WriteOffset, data, size);

    // Update the write offset
    uareaobj.UFDT[fd]->WriteOffset = uareaobj.UFDT[fd]->WriteOffset + size;

    // update the actual file size
    uareaobj.UFDT[fd]->ptrinode->ActualFileSize = uareaobj.UFDT[fd]->ptrinode->ActualFileSize + size;

    return size;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : ReadFile
//  Description   : It is used to read the data from the file
//  Input         : File Descriptor
//                  Address of empty Buffer
//                  Size of data that we want to read
//  Output        : Number of bytes succesfully read
//  Auther        : Aditya Vijay Mali
//  Date          : 22/01/2026
//
///////////////////////////////////////////////////////////////////////////////////////

int ReadFile(
    int fd,
    char *data,
    int size)
{
    // Invalid Fd
    if (fd < 0 || fd > MAXOPENFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    if (data == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if (size <= 0)
    {
        return ERR_INVALID_PARAMETER;
    }

    if (uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // Filter for permission
    if (uareaobj.UFDT[fd]->ptrinode->Permission < READ)
    {
        return ERR_PERMISSION_DENIED;
    }

    // Insuuficeint data
    if ((MAXFILESIZE - uareaobj.UFDT[fd]->ReadOffset) < size)
    {
        return ERR_INSUFFICIENT_DATA;
    }

    // Read the data
    strncpy(data, uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->ReadOffset, size);

    // Update the read offset

    uareaobj.UFDT[fd]->ReadOffset = uareaobj.UFDT[fd]->ReadOffset + size;

    return size;

} // End of ReadFile

///////////////////////////////////////////////////////////////////////////////////////
//
//  Entry Point Function of The Project
//
///////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char str[80] = {'\0'};
    char Command[5][20] = {{'\0'}};
    char InputBuffer[MAXFILESIZE] = {'\0'};

    char *EmptyBuffer = NULL;

    int iCount = 0;
    int iRet = 0;

    StartAuxillaryDataInitilisation();

    printf("-----------------------------------------------------------------\n");
    printf("-------------- Marvellous CVFS started succesfully --------------\n");
    printf("-----------------------------------------------------------------\n");

    // Infinite Listening Shell
    while (1)
    {
        fflush(stdin);

        strcpy(str, "");

        printf("\nMarvellous CVFS : > ");
        fgets(str, sizeof(str), stdin);

        iCount = sscanf(str, "%s %s %s %s %s", Command[0], Command[1], Command[2], Command[3], Command[4]);

        fflush(stdin);

        if (iCount == 1)
        {
            //  Marvellous CVFS : > exit
            if (strcmp("exit", Command[0]) == 0)
            {
                printf("Thank you for using MArvellous CVFS\n");
                printf("Deallocating all the allocated resources\n");

                break;
            }
            //  Marvellous CVFS : > ls
            else if (strcmp("ls", Command[0]) == 0)
            {
                LsFile();
            }
            //  Marvellous CVFS : > help
            else if (strcmp("help", Command[0]) == 0)
            {
                DisplayHelp();
            }
            //  Marvellous CVFS : > clear
            else if (strcmp("clear", Command[0]) == 0)
            {
                #ifdef _WIN32
                                system("cls");
                #else
                                system("clear");
                #endif
            }

        } // End of else if 1
        else if (iCount == 2)
        {
            //  Marvellous CVFS : > man ls
            if (strcmp("man", Command[0]) == 0)
            {
                ManPageDiaplay(Command[1]);
            }

            //  Marvellous CVFS : > unlink Demo.txt
            if (strcmp("unlink", Command[0]) == 0)
            {
                iRet = UnlinkFile(Command[1]);

                if (iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Unable to create file as parramitters are invalid \n");
                }

                if (iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Unable to Delete as there is no such file \n");
                }

                if (iRet == EXECUTE_SUCCESS)
                {
                    printf("File gets succesfully deleted \n");
                }
            }
            // Marvellous CVFS : > write 2
            else if (strcmp("write", Command[0]) == 0)
            {
                printf("Enter the data that you want to write: \n");
                fgets(InputBuffer, MAXFILESIZE, stdin);

                iRet = WriteFile(atoi(Command[1]), InputBuffer, strlen(InputBuffer) - 1);

                if (iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parametters \n");
                }
                else if (iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : There is no such file \n");
                }
                else if (iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Unable to write as there is no permission \n");
                }
                else if (iRet == ERR_INSUFFICIENT_SPACE)
                {
                    printf("Error : Unable to write as there is no space \n");
                }
                else
                {
                    printf("%d bytes gets successful written\n", iRet);
                }
            }
            else
            {
                printf("There no such Command\n");
            }

        } // End of else if 2
        else if (iCount == 3)
        {
            //  Marvellous CVFS : > creat Ganesh.txt 3
            if (strcmp("creat", Command[0]) == 0)
            {
                iRet = CreateFile(Command[1], atoi(Command[2]));

                if (iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Unable to create file as parramitters are invalid \n");
                    printf("please refer man page\n");
                }

                if (iRet == ERR_NO_INODES)
                {
                    printf("ERROR : Unable to create file as there is no inode\n");
                }

                if (iRet == ERR_FILE_ALREADY_EXIST)
                {
                    printf("ERROR : Unable to create becaue the file is already present\n");
                }

                if (iRet == ERR_MAX_FILES_OPEN)
                {
                    printf("ERROR : Unable to Create file \n");
                    printf("Max opened files limit reached\n");
                }

                printf("File gets succesfully created with FD : %d \n", iRet);
            }
            // Marvellous CVFS : > read 3 10
            if (strcmp("read", Command[0]) == 0)
            {
                EmptyBuffer = (char *)malloc(sizeof(atoi(Command[2])));

                iRet = ReadFile(atoi(Command[1]), EmptyBuffer, atoi(Command[2]));

                if (iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalid parametter \n");
                }
                else if (iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : File not exists \n");
                }
                else if (iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Permission denied");
                }
                else if (iRet == ERR_INSUFFICIENT_DATA)
                {
                    printf("Error : Insufficient data \n");
                }
                else
                {
                    printf("Read operation is Succesful\n");
                    printf("Data from file is : %s \n", EmptyBuffer);

                    free(EmptyBuffer);
                }
            }
        } // End of else if 3
        else if (iCount == 4)
        {

        } // End of else if 4
        else if ((strcmp(str, "\n")) == 0)
        {
            continue;
        } // End of else if 5
        else
        {
            printf("Command not found\n");
            printf("Please refer help option to get more information \n");
        } // End of else
    } // End of while

    return 0;
} // End of main

//  help.txt read and write on console in displayHelp function
//  ManPageDiaplay add discription from man page