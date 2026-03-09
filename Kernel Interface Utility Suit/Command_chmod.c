#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////////
//
// 	./chmodX	permissions	Dest.txt
//	argv[0]		argv[1]		argv[2]
//	
//	argc = 3
//
////////////////////////////////////////////////////////////////////////////////////

int main(int argc,char *argv[])
{
	int iRet = 0;
	if(argc != 3)
	{
		printf("Error : Insufficient arguments\n");
		printf("Use command as : ./chmod permissions(755) Destination.txt \n");
		return -1;
	}
	
	if (access(argv[2],F_OK) == -1)
	{
		printf("Unable to change permissions as no such file\n");
		return -1;
	}
	
	
	iRet = chmod(argv[2],atoi(argv[1]));

	if (iRet == 0)
	{
		printf("Permissions changed to : %d",atoi(argv[1]));
	}
	else
	{
		printf("%s",strerror(errno));
	}
	
	return 0;
}



