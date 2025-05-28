#include <stdio.h>
#include <limits.h>
#include <stdarg.h>

enum Type{INT, DOUBLE};

void vmax(enum Type t_arg, size_t cnt, ...){
    va_list parg;
    va_start(parg, cnt);
    int max_i = INT_MIN;
    double max_b = -10000000.0;
    for(size_t i = 0; i < cnt; i++){
        if (t_arg == INT){
            int new_arg = va_arg(parg, int);
            if (new_arg > max_i){
                max_i = new_arg;
            }
        }
        else{
            double new_arg = va_arg(parg, double);
            if (new_arg > max_b){
                max_b = new_arg;
            }
        }
    }
    va_end(parg);
    if (t_arg == INT){
        printf("%d\n", max_i);
    }
    else{
        printf("%g\n", max_b);
    }
}

int
main(void){
    vmax(INT, 1, 10);
    vmax(INT, 5, -40, 2, -23, -100000, 10);
    vmax(INT, 10, 10, -10, -90, -18889, 0, 0, 0, -19, -10, 9);
    vmax(INT, 15, -100, 10, INT_MIN, 2, 0, 5, 7, 8, 3, -1, -1000, -123241, 6, 1, -1000);
    vmax(DOUBLE, 1, 100.);
    vmax(DOUBLE, 5, -100., -234332.29483, -.01, -000000.0000, 100.);
    vmax(DOUBLE, 7, -192983749827.9287398472895, -84765872.9284375, 100., -4785., 
    -.47589723, 5.78364587648, 8.398745893984);
    vmax(DOUBLE, 2, 100.0, 100.);
}
