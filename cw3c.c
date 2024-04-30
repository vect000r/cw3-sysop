#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork error");
        return 1;
    case 0:;
        // proces potomny
        // proces potomny staje sie liderem wlasnej grupy procesow przez funkcje setpgid
        
        if (setpgid(0, 0) == -1)
        {
            perror("setpgid error");
            return 1;
        }
        
        // ustawiamy ignorowanie sygnału
        if (signal(SIGUSR1, SIG_IGN) == SIG_ERR)
        {
            printf("Signal error");
        }
        
        // uruchamiamy program cw3c1 za pomocą execlp
        if (execlp("./cw3c1.x", "./cw3c1.x", NULL) == -1)
        {
            perror("execlp error");
            return 1;
        }
        break;
    default:
        // proces macierzysty:
        sleep(2);
        
        // uzyskujemy pid grupy procesów za pomocą getpgid
        
        int pgid = getpgid(pid);
        if (pgid == -1)
        {
            perror("getpgid error");
            return 1;
        }
        if (kill(-pgid, 0) == 0)
        {
            // wysyłamy sygnał SIGUSR1 do grupy procesów
            printf("Signal sent to child process:\n");
            sleep(4);
            if (kill(-pgid, SIGUSR1) == -1)
            {
                perror("kill error");
                return 1;
            }
        }
        else
        {
            printf("Child process doesn't exist\n");
        }
        
        int statusParent;
        
        // czekamy aż procesy potomne się zakończą i wypisujemy ich status zakończenia
        
        pid_t waitResult = wait(&statusParent);
        if (waitResult == -1)
        {
            perror("wait error");
            return 1;
        }
        if (WIFEXITED(statusParent))
        {
            printf("Child process returned: %d\n", WEXITSTATUS(statusParent));
        }
        else if (WIFSIGNALED(statusParent))
        {
            
            // jeśli proces potomny został zakończony przez sygnał, wypisujemy informacje o sygnale
            
            int signal_num = WTERMSIG(statusParent);
            printf("Child process with pid:(%d) ended by signal: %d (%s) Child process status: %d\n", pid, signal_num, strsignal(signal_num), statusParent);
        }
        break;
    }
    return 0;
}