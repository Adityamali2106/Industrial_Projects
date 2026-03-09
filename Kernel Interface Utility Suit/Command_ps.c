#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <ctype.h>

////////////////////////////////////////////////////////////////////////////////////
//
// 	./psx
//	argv[0]
//	
//	argc = 1
//
////////////////////////////////////////////////////////////////////////////////////

/*
	Open the directory /proc
	Open all subfirectors whose name is integer
	Inside that directory opn comm file 
	Display the name inside that file
*/

int is_numeric(const char *str) {
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

int main(int argc,char *argv[])
{
	DIR *dir = NULL;
	DIR *Subdir = NULL;

	struct dirent *ptr = NULL;
	struct dirent *SubPtr = NULL;

	int fd = 0;
	int iRet = 0;

	char Buffer[1024];
	char path[1024];

	dir = opendir("/proc");

	if(NULL == dir)
	{
		printf("Error : %s",strerror(errno));
		return -1;
	}
	printf("%p",dir);

	while ((ptr = readdir(dir)) != NULL)
	{
		if ((strcmp(ptr->d_name,".")) == 0 || (strcmp(ptr->d_name,"..")) == 0)
		{
			continue;
		}

		if(is_numeric(ptr->d_name))
		{
			printf("%s",ptr->d_name);

			snprintf(path, sizeof(path), "/proc/%s/comm", ptr->d_name);
			
			fd = open(path,O_RDONLY);
			if (fd == -1)
			{
				printf("Error : %s",strerror(errno));
				return -1;
			}
			

			memset(Buffer,'\0',sizeof(Buffer));

			iRet = read(fd,Buffer,sizeof(Buffer));

			if (iRet == 0)
			{
				continue;
			}			

			write(1,Buffer,iRet);
			printf("\n");

			close(fd);
		}			
	}		
	
	closedir(dir);
	return 0;
}



