#include <math.h>
#include <stdio.h>

long double
min(long double a, long double b){
    if (a > b){
        return b;
    }
    else return a;
}

long double
max(long double a, long double b){
    if (a < b){
        return b;
    }
    else return a;
}
int
main(void){
    long long xa, ya, xb, yb;
    long double lena, lenb;
    scanf("%lld", &xa);
    scanf("%lld", &ya);
    scanf("%lld", &xb);
    scanf("%lld", &yb);
    lena = sqrt(xa*xa + ya*ya);
    lenb = sqrt(xb*xb + yb*yb);
    printf("%Lf\n", min(lena+lenb, (max(lena, lenb) - min(lena, lenb))
    + min(lena, lenb)*acos((xa*xb + ya*yb)/(lena * lenb))));
    return 0;
}
