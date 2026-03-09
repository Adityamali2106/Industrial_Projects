#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int Option = 0;
	
	// 1 : ls -a
	// 2 = ls -i

	if(argc == 1)
	{
		Option = 1;
	}
	else if(strcmp(argv[1], "-u") == 0)
	{
		Option = 2;
	}
	else if(strcmp(argv[1], "-g") == 0)
	{
		Option = 3;
	}
	else if(strcmp(argv[1], "-G") == 0)
	{
		Option = 4;
	}
	else 
	{
		printf("Error : There is no such opstion \n");
	}

	if (Option == 1)
	{
		FILE *fp = NULL;
		char line[40] = {'\0'};

		fp = fopen("/etc/group","r");

		if (fp == NULL)
		{
			return -1;
		}

		printf("uid = %d %s \n",getuid(),getlogin());

		printf("gid = %d %s \n",getgid(),getlogin());

		printf("groups = %d %s \n",getgid(),getlogin());

		while(fgets(line,sizeof(line),fp)!= NULL)
    	{
        	if(strncmp(line,"adm:x:",6) == 0 ||
            	strncmp(line,"cdrom:x:",8) == 0 ||   
            	strncmp(line,"sudo:x:",7) == 0 ||
            	strncmp(line,"dip:x:",6) == 0 ||
				strncmp(line,"plugdev:x:",10) == 0 ||
				strncmp(line,"users:x:",8) == 0 ||
				strncmp(line,"lpadmin:x:",10) == 0
        	  )
        	{
            	printf("%s",line);
        	}
    	}
	}
	else if (Option == 2)
	{
		printf("uid = %d %s \n",getuid(),getlogin());
	}
	else if (Option == 3)
	{
		printf("gid = %d %s \n",getgid(),getlogin());
	}
	else if (Option == 4)
	{
		FILE *fp = NULL;
		char line[40] = {'\0'};
		char arr[60] = {'\0'};

		fp = fopen("/etc/group","r");

		if (fp == NULL)
		{
			return -1;
		}

		printf("%d ",getuid());
		while(fgets(line,sizeof(line),fp)!= NULL)
    	{
        	if(strncmp(line,"adm:x:",6) == 0)
			{
				strncat(arr,(line+6),1);
				strcat(arr," ");
			}
			else if (strncmp(line,"cdrom:x:",8) == 0 )
			{
				strncat(arr,(line+8),2);
				strcat(arr," ");
			}
			else if(strncmp(line,"sudo:x:",7) == 0)
			{
				strncat(arr,(line+7),2);
				strcat(arr," ");
			}
			else if (strncmp(line,"dip:x:",6) == 0)
			{
				strncat(arr,(line+6),2);
				strcat(arr," ");
			}
			else if(strncmp(line,"plugdev:x:",10) == 0)
			{
				strncat(arr,(line+10),2);
				strcat(arr," ");
			}
			else if(strncmp(line,"users:x:",8) == 0)
			{
				strncat(arr,(line+8),3);
				strcat(arr," ");
			}
			else if(strncmp(line,"lpadmin:x:",10) == 0)
        	{
            	strncat(arr,(line+10),3);
				strcat(arr," ");
        	}
    	}

		printf("%s\n",arr);
	}
			
	return 0;
}

