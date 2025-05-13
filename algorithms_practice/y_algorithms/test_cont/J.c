#include <stdio.h>

int
main(void){
    int t;
    int n, a, b, mn;
    scanf("%d", &t);
    for (int i = 0; i < t; i++){
        scanf("%d %d %d", &n, &a, &b);
        mn = n / b;
        mn++;
        if (n % b == 0){
            mn--;
        }
        if (a * mn <= n){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}
