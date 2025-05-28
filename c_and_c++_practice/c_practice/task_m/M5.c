#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
//volatile global signal hndlr
int can_work = 1;
int son_can_work = 0;

void
son_hndlr(int s){
    son_can_work = 1;
}

void
father_hndlr(int s){
    signal(SIGUSR2, father_hndlr);
    can_work = 1;
}

void
son_func(int fd){
    while (son_can_work == 0){
        usleep(2000);
    }
    int k;
    lseek(fd, 0, SEEK_SET);
    read(fd, &k, sizeof(int));
    k++;
    lseek(fd, 0, SEEK_SET);
    write(fd, &k, sizeof(int));
    kill(getppid(), SIGUSR2);
    exit(0);
}

int
main(void){
    int n, num = 0, cnt_sons = 0, sig_cnt = 0;
    pid_t pid;
    char template[] = "mflXXXXXX";
    int fd = mkstemp(template);
    unlink(template);
    signal(SIGUSR2, father_hndlr);
    signal(SIGUSR1, son_hndlr);
    write(fd, &num, sizeof(int));
    static pid_t son_pids[1000] = {};
    scanf("%d", &n);
    while (1){
        if (cnt_sons < n){
            if ((pid = fork()) == 0){
                son_func(fd);
            }
            else if (pid == -1){
                while ((pid = fork()) == -1){
                    if (sig_cnt < cnt_sons){
                        if (can_work){
                            can_work = 0;
                            kill(son_pids[sig_cnt++], SIGUSR1);
                        }
                        else{
                            usleep(1000);
                        }
                    }
                    waitpid(-1, NULL, WNOHANG);
                }
                if (pid == 0){
                    son_func(fd);
                }
            }
            if (pid > 0){
                son_pids[cnt_sons] = pid;
                cnt_sons++;
            }
        }
        if (sig_cnt == n){
            break;
        }
        else{
            if (cnt_sons == n){
                while (sig_cnt < n){
                    while (can_work == 0){
                        usleep(2000);
                    }
                    can_work = 0;
                    kill(son_pids[sig_cnt++], SIGUSR1);
                }
            }
            if (sig_cnt < cnt_sons){
                if (can_work){
                    can_work = 0;
                    kill(son_pids[sig_cnt++], SIGUSR1);
                }
            }
        }
        waitpid(-1, NULL, WNOHANG);
    }
    while (wait(NULL) != -1){
    }
    lseek(fd, 0, SEEK_SET);
    read(fd, &num, sizeof(int));
    close(fd);
    printf("%d\n", num);
    return 0;
}
