#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
/*
    1) There is no active waiting because sons wait for a signal
    from a father in usleep cycle, and father (if he had created
    all sons, but had not sent all signals to them) waits the
    completion of file managing in usleep cycle too. There will not
    be extra waiting due to the fact that usleep() will be
    interupted by a signal from son
    2) Correct work is being implemented by system of signals:
    father sends a signal as soon as no son is working with a
    file to next son (next element of array of son's pids) SIGUSR1.
    Son function of USRSIG1 handler changes global variable
    son_can_work to 1. Son waits till this moment in usleep cycle.
    After that - works wirh file. Then, sends a sinal USRSIG2 to
    a father to show that he had finished work with file. After
    getting a signal, father sends a new signal to next son.
*/

int son_in_progress = 0;
int son_can_work = 0;

void
son_sig_hndlr(int s){
    son_can_work = 1;
}

void
father_sig_hndlr(int s){
    son_in_progress = 0;
}

void
son_proc(int fd){
    while (son_can_work == 0){
        usleep(1000);
    }
    int num1;
    lseek(fd, 0, SEEK_SET);
    read(fd, &num1, sizeof(int));
    num1++;
    lseek(fd, 0, SEEK_SET);
    write(fd, &num1, sizeof(int));
    close(fd);
    kill(getppid(), SIGUSR2);
    _exit(0);
}

int
main(void){
    char template[] = "mflXXXXXX";
    pid_t pid, *son_pids;
    int n, num = 0, son_cnt = 0, son_end_cnt = 0;
    int fd = mkstemp(template);
    unlink(template);
    scanf("%d", &n);
    write(fd, &num, sizeof(int));
    son_pids = malloc(sizeof(pid) * n);
    signal(SIGUSR2, father_sig_hndlr);
    signal(SIGUSR1, son_sig_hndlr);
    while(1){
        if (son_cnt < n){
            son_cnt++;
            if ((pid = fork()) == 0){
                free(son_pids);
                son_proc(fd);
            }
            else if (pid == -1){
                while((pid = fork()) == -1){
                    if (son_in_progress == 1){
                        wait(NULL);
                    }
                    else{
                        son_in_progress = 1;
                        son_end_cnt++;
                        kill(son_pids[son_end_cnt - 1], SIGUSR1);
                    }
                }
                if (pid == 0){
                    free(son_pids);
                    son_proc(fd);
                }
            }
            son_pids[son_cnt - 1] = pid;
        }
        if ((son_in_progress) && (son_cnt == n)){
            while (son_in_progress){
                usleep(1000);
            }
        }
        if (son_in_progress == 0){
            if (son_end_cnt < son_cnt){
                son_in_progress = 1;
                son_end_cnt++;
                kill(son_pids[son_end_cnt - 1], SIGUSR1);
            }
            else if (son_end_cnt == n){
                break;
            }
        }
    }
    while (wait(NULL) != -1);
    lseek(fd, 0, SEEK_SET);
    read(fd, &n, sizeof(int));
    printf("%d\n", n);
    close(fd);
    free(son_pids);
    return 0;
}
