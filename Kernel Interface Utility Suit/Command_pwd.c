#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

////////////////////////////////////////////////////////////////////////////////////
//
// 	./touchx
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
	char Buffer[1024] = {'\0'};

	getcwd(Buffer,sizeof(Buffer));

	printf("%s\n",Buffer);
	return 0;
}



