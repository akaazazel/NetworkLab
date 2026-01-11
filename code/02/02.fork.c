#include <stdio.h>
#include <unistd.h>

void main()
{
    int pid;
    pid = fork();
    if (pid > 0)
    {
        printf("Iam Parent\n");
    }
    else
    {
        printf("Iam Child!\n");
    }
}
