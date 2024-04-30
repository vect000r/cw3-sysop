#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <wait.h>


int main()
{
    for (int i = 0; i < 3; i++)
    {
        pid_t pid = fork();
        switch (pid)
        {
        case -1:
            perror("fork error");
            return 1;
        case 0:
            // proces potomny 
            // uruchamiamy program cw3a za pomocą execlp
            
            if (execlp("./cw3a.x", "./cw3a.x", "1", "10", NULL) == -1)
            {
                perror("execlp error");
                return 2;
            }
            break;
        default:
            // proces macierzysty
            break;
        }
    }
    int status;
    pid_t wpid;
    while ((wpid = wait(&status)) > 0)
    {
        if (WIFEXITED(status))
        {
            printf("Child process (PID: %d) exited with status: %d\n", wpid, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            int signal_num = WTERMSIG(status);
            printf("Child process (PID: %d) terminated by signal: %d (%s)\n", wpid, signal_num, strsignal(signal_num));
        }
        else
        {
            perror("wait error");
            return 3;
        }
    }
    return 0;
}