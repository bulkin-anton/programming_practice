#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int seconds = 0;
int c_sig = 0;

void
sigint_hndlr(int s){
    c_sig = 1;
    signal(SIGINT, sigint_hndlr);
}

void
alarm_hndlr(int s){
    seconds++;
    signal(SIGALRM, alarm_hndlr);
    alarm(1);
}

int
main(void){
    signal(SIGINT, sigint_hndlr);
    signal(SIGALRM, alarm_hndlr);
    unsigned long long num = 0;
    scanf("%llu", &num);
    alarm(1);
    while (num > 0){
        if (seconds == 5){
            printf("%llu\n", num);
            seconds = 0;
        }
        if (c_sig){
            printf("%d\n", 5 - seconds);
            c_sig = 0;
        }
        num--;
    }
    return 0;
}
