#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>



int main() 
{
    int status;
    pid_t pid = fork();
    if (pid == -1) 
    {
        perror("fork");
        return 1;
    } 
    else if (pid == 0) 
    {
        if (execlp("./cw3a.x", "./cw3a.x", "3", "2", NULL) == -1) 
        {
            perror("execl");
            return 1;
        }
    } 
    else 
    {
        sleep(2);
        if (kill(pid, SIGINT) == -1) 
        {
            perror("kill");
            return 1;
        }
        waitpid(pid, &status, 0);
        
        printf("Exit status of child: %d\nPID of child: %d\n", WEXITSTATUS(status), pid);
        if (WIFSIGNALED(status)) 
        {
            int signal_number = WTERMSIG(status);
            const char* signal_name = strsignal(signal_number);
            printf("Child process terminated by signal: %s (%d)\n", signal_name, signal_number);
        }
        
    }
    return 0;
}
