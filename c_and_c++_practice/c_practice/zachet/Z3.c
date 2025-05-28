#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int cnt = 0, end = 0;

void
sigusr_hndlr(int s){
    cnt++;
}

void
sigterm_hndlr(int s){
    end++;
}

void
son_proc(char **argv1, char **argv2){
    int fd[2];
    while(1){
        if (cnt > 2){
            cnt -= 3;
            pipe(fd);
            if (fork() == 0){
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd[0]);
                execvp(argv1[0], argv1);
                exit(1);
            }
            close(fd[1]);
            if (fork() == 0){
                dup2(fd[0], 0);
                close(fd[0]);
                execvp(argv2[0], argv2);
                exit(1);
            }
            while(wait(NULL) != -1);
        }
        if ((end > 0) && (cnt < 3)){
            break;
        }
        usleep(2000);
    }
    exit(0);
}

int
main(int parc, char *parms[]){
    char buf[] = "--";
    pid_t pid;
    int n;
    char **argv2 = NULL, **argv1 = &parms[1];
    for (int i = 1; i < parc; i++){
        if (strstr(parms[i], buf) != NULL){
            parms[i] = NULL;
            argv2 = &parms[i + 1];
            break;
        }
    }
    if ((pid = fork()) == 0){
        signal(SIGUSR1, sigusr_hndlr);
        signal(SIGTERM, sigterm_hndlr);
        son_proc(argv1, argv2);
    }
    while(scanf("%d", &n) == 1){
        if (n == 0){
            kill(pid, SIGUSR1);
        } else if (n > 0){
            usleep(n);
        }
    }
    kill(pid, SIGTERM);
    wait(NULL);
    return 0;
}
