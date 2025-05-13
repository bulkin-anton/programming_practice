#include <stdio.h>

int
main(void){
    unsigned long long sum = 0;
    char lit;
    while((scanf("%c", &lit)) == 1){
        if ((lit >= '0') && (lit <= '9')){
            sum += lit - '0';
        }
        if ((lit >= 'a') && (lit <= 'f')){
            sum += lit - 'a' + 10;
        }
        if ((lit >= 'A') && (lit <= 'F')){
            sum += lit - 'A' + 10;
        }
    }
    printf("%llu\n", sum);
    return 0;
}
