#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////////
//
// 	./rmx
//	argv[0]
//	
//	argc = 1
//
////////////////////////////////////////////////////////////////////////////////////

/*
	Call the system call getcwd
	print the result of getcwd
*/


int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		printf("Error : Insufficient arguments \n");
		printf("Use as : ./rm Path\n");
		return -1;
	}	


	if(access(argv[1],F_OK) == 0)
	{
		if(unlink(argv[1]) == -1)
		{
			printf("Error : '%s': No such file or directory\n",argv[1]);
			return -1;
		}
		else
		{
			printf("Success : File gets deleted \n");
		}
	}
	else
	{
		printf("Error : Unable to Delete as file is not present\n");
		return -1;
	}

	return 0;
}



