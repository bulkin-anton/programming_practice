#include <stdio.h>

int
devide_num(int num1, int num2){
    while (num1 && num2)
        if (num1 >= num2)
           num1 -= num2;
        else
           num2 -= num1;
    return (num1 | num2);
}

int
main(void){
    int a, b, c, d, dev;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    scanf("%d", &d);
    dev = devide_num(a, b);
    a /= dev;
    b /= dev;
    dev = devide_num(c, d);
    c /= dev;
    d /= dev;
    a *= d;
    c *= b;
    b *= d;
    a += c;
    dev = devide_num(a, b);
    printf("%d %d\n", a/dev, b/dev);
}
