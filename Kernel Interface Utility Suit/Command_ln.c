#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

////////////////////////////////////////////////////////////////////////////////////
//
// 	./catx 		-s			FileName		LinkFilename
//	argv[0]		argv[1]		argv[2]			argv[3]
//	
//	argc = 4	
//
////////////////////////////////////////////////////////////////////////////////////

/*
	Acccept file name and link file name from command line 
	check wether file is existing or not
	If it is existing then create hard link else if the 2nd argument is -s than create soft link
	if it is not exiating then
	Display NO such file or Directory as a error
*/

#define MAX_BUFFER_SIZE 1024

int main(int argc,char *argv[])
{
	int Option = 0;
	if (argc == 3)
	{
		Option = 1;
	}
	else if(argc == 4)
	{
		Option = 2;
	}
	else if(argc != 3)
	{
		printf("Error : Insufficient arguments \n");
		printf("Use as : ./lnx -s/Nothing FileName LinkFileName\n");
		return -1;
	}

	int iRet = 0;
	if(Option == 1)
	{
		if(access(argv[1],F_OK) != 0)
		{
			printf("ln: %s: No such file or directory\n",argv[1]);
			return -1;
		}
		else
		{		
			iRet = link(argv[1],argv[2]);

			if (iRet == -1)
			{
				printf("%s\n",strerror(errno));
				return -1;
			}
			
			printf("Hard Link is created as : %s",argv[2]);
		}
	}
	else if(Option == 2)
	{
		if(access(argv[2],F_OK) != 0)
		{
			printf("ln : %s: No such file or directory\n",argv[1]);
			return -1;
		}
		else
		{
			iRet = symlink(argv[2],argv[3]);

			if (iRet == -1)
			{
				printf("%s\n",strerror(errno));
				return -1;
			}

			printf("Symbolic Link is created as : %s",argv[3]);
		}
	}

	return 0;
}



