#include <stdio.h>

int
main(void){
    int a, b, n;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &n);
    if ((((float) a) / n) > (((float) b) / n)){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
    return 0;
}
