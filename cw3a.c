#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h> 
#include <sys/types.h>

void defaultHandler(int signal) 
{
    printf("Received signal %d - %s - Default handling\n", signal, strsignal(signal));
    exit(0);
}

void ignoreHandler(int signal) 
{
    printf("Received signal %d - %s - Ignoring\n", signal, strsignal(signal));
}

void customHandler(int signal) 
{
    printf("Received signal %d - %s - Custom handling\n", signal, strsignal(signal));
    printf("PID: %d\n", getpid());
    exit(0);
}

int main(int argc, char *argv[]) 
{
    if(argc < 3) 
    {
        printf("Not enough arguments provided.\n");
        return 1;
    }

    int arg1 = atoi(argv[1]);
    int arg2 = atoi(argv[2]);

    sleep(1);

    if(arg1 == 1) 
    {
        if(signal(arg2, defaultHandler) == SIG_ERR)
        {
            printf("Failed to set default handler for signal %d\n", arg2);
            return 1;
        }
    }
    else if(arg1 == 2) 
    {
        if(signal(arg2, ignoreHandler) == SIG_ERR)
        {
            printf("Failed to set ignore handler for signal %d\n", arg2);
            return 1;
        }
    }
    else if(arg1 == 3) 
    {
        if(signal(arg2, customHandler) == SIG_ERR)
        {
            printf("Failed to set custom handler for signal %d\n", arg2);
            return 1;
        }
    }

    pause();

    return 0;
}