#include "print.h"
#include <stdio.h>
#include <stdarg.h>

static void output(const char buf[])
{
    printf("%s", buf);
    fflush(stdout);
}

static char bufer[BUF_SIZE];

void
print(const char format[], ...){
    int i = 0, k = 0;
    va_list arg;
    va_start(arg, format);
    while (bufer[k] != 0){
        k++;
    }
    while (format[i] != 0){
        if (k == (BUF_SIZE - 1)){
            bufer[k] = 0;
            output(bufer);
            k = 0;
            for(int j = 0; j < BUF_SIZE; j++){
                bufer[j] = 0;
            }
        }
        if (format[i] == '%'){
            bufer[k] = va_arg(arg, int);
        }
        else{
            bufer[k] = format[i];
        }
        i++;
        k++;
        if (bufer[k-1] == 10){
            bufer[k] = 0;
            output(bufer);
            k = 0;
            for(int j = 0; j < BUF_SIZE; j++){
                bufer[j] = 0;
            }
        }
    }
    va_end(arg);
}

void
flush(void){
    int i = 0;
    while ((bufer[i] != 0)&&(i != BUF_SIZE)){
        printf("%c", bufer[i]);
        i++;
    }
    for (int j = 0; j < BUF_SIZE; j++){
        bufer[i] = 0;
    } 
}
