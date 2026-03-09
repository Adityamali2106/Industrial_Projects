#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    for (int i = 1; argv[i] != NULL; i++)
    {
        printf("%s ",argv[i]);
    }
    
    printf("\n");
    return 0;
}

