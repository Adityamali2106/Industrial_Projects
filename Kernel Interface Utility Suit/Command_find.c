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
	if(argc < 2)
	{
		printf("Error : Insufficient arguments \n");
		printf("Use as : ./lnx -s/Nothing FileName LinkFileName\n");
		return -1;
	}

	int iRet = 0;
	int i = 0;
	char path[1024];

	memset(path,'\0',sizeof(path));

	strcpy(path,argv[1]);
	
	for (i = 2; i < argc; i++)
	{
		strcat(path,"/");
		strcat(path,argv[i]);
	}
	
	printf("%s",path);

	return 0;
}
