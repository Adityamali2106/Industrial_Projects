#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char *argv[])
{
	if (argc == 2)
	{
		if ((strcmp(argv[1],"--version")) == 0)
		{
			printf("whoami (GNU coreutils) 9.4 \n Copyright (C) 2023 Free Software Foundation, Inc.\n");
			printf("License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\n");
			printf("Written by Aditya Mali.");
		}
		else
		{
			printf("whoami: invalid option %s\n",argv[1]);
			printf("Try 'whoami --help' for more information.\n");
		}
	}
	else if (argc == 2)
	{
		if ((strcmp(argv[1],"--help")) == 0)
		{
			printf("Usage: whoami [OPTION]...\n");
			printf("Print the user name associated with the current effective user ID.");			
			printf("Same as id -un.\n");
      		printf("\t\t--help        display this help and exit\n");
      		printf("\t\t--version     output version information and exit\n");
		}
		else
		{
			printf("whoami: invalid option %s\n",argv[1]);
			printf("Try 'whoami --help' for more information.\n");
		}
	}
	else if (argc == 1)
	{
		printf("%s \n",getlogin());
	}
	

	return 0;
}

