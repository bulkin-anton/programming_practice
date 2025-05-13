#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>


void
sig_hndlr(int s){
    static char count[] = {'0', '\n'};
    count[0]++;
    write(1, &count, sizeof(count));
    if (count[0] > '4'){
        exit(0);
    }
}

int
main(void){
    pid_t pid;
    signal(SIGINT, sig_hndlr);
    if ((pid = fork()) == 0){
        while(1){
            usleep(10);
        }
    }
    for (int i = 0; i < 5; i++){
        usleep(50);
        kill(pid, SIGINT);
    }
    wait(NULL);
    return 0;
}
