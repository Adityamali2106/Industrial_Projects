#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

////////////////////////////////////////////////////////////////////////////////////
//
// 	./touchx 		FileName
//	argv[0]		argv[1]
//	
//	argc = 2
//
////////////////////////////////////////////////////////////////////////////////////

/*
	Acccept file name from command line 
	check wether file is existing or not
	If it is existing return
	if it is not exiating
	Creat that file 
*/


int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		printf("Error : Insufficient arguments \n");
		printf("Use as : ./touchx FileName\n");
		return -1;
	}

	if(access(argv[1],F_OK) == 0)
	{
		return 0;
	}
	else
	{
		creat(argv[1],0777);
	}

	return 0;
}



