#include <stdio.h>

int
main(void){
    int n, cnt = 0, sum = 0, x;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 3; j++){
            scanf("%d", &x);
            sum += x;
        }
        if (sum > 1){
            cnt++;
        }
        sum = 0;
    }
    printf("%d", cnt);
    return 0;
}
