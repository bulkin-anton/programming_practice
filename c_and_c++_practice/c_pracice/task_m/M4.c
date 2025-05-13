#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
    Problem: an alarm signal can be recieved
    while decreasing process of a number
    Solution: creating a copy of a number in cpy_num
    ************************
    Problem: an alarm signal can be recieved between
    the end of function "dec" and increasing of decr_in_progress
    Solution: if res_decreasing is changed from NULL to
    new pointer of a number string - the function has ended,
    however, decr_in_progress is not increased
*/

int seconds = 0;
char *num = NULL;
char *res_decreasing = NULL;
int decr_in_progress = 0;
char *cpy_num;
char left[2] = {'0', '\n'};

void
sigint_hndlr(int s){
    signal(SIGINT, sigint_hndlr);
    left[0] = '0' + 5 - (seconds % 5);
    write(1, left, sizeof(left));
}

void
alarm_hndlr(int s){
    signal(SIGALRM, alarm_hndlr);
    seconds++;
    if ((seconds % 5) == 0){
        seconds /= 5;
        if (decr_in_progress){
            if (res_decreasing == NULL){
                write(1, cpy_num, strlen(cpy_num) * sizeof(char));
                write(1, "\n", sizeof(char));
            }
            else{
                write(1, res_decreasing, strlen(res_decreasing) * sizeof(char));
                write(1, "\n", sizeof(char));
            }
        }
        else{
            write(1, num, strlen(num) * sizeof(char));
            write(1, "\n", sizeof(char));
        }
    }
    alarm(1);
}

int
main(int parc, char *parms[]){
    signal(SIGINT, sigint_hndlr);
    signal(SIGALRM, alarm_hndlr);
    num = parms[1];
    cpy_num = malloc(sizeof(char) * (strlen(num) + 1));
    strcpy(cpy_num, num);
    alarm(1);
    while (!((strlen(num) == 1) && (num[0] == '0'))){
        decr_in_progress = 1;
        res_decreasing = dec(num);
        decr_in_progress = 0;
        num = res_decreasing;
        strcpy(cpy_num, num);
        res_decreasing = NULL;
    }
    free(cpy_num);
    return 0;
}
