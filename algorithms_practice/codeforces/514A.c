#include <stdio.h>

int
main(void){
    int n = 0, x;
    scanf("%d", &x);
    while (x != 0){
        if ((x % 10) > (9 - (x % 10))){
            n *= 10;
            n += 9 - (x % 10);
        } else{
            n *= 10;
            n += x % 10;
        }
        x /= 10;
    }
    x = 0;
    while (n != 0){
        x *= 10;
        x += n % 10;
        n /= 10;
    }
    if (x == 0){
        printf("%d", 9);
    } else printf("%d", x);
    return 0;
}
