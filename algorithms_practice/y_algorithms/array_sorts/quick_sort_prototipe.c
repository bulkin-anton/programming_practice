#include <stdio.h>
#include <stdlib.h>

int
main(void){
    int N;
    long long int *a, x;
    scanf("%d", &N);
    a = malloc(sizeof(*a) * N);
    for (int i = 0; i < N; i++){
        scanf("%lld", &a[i]);
    }
    scanf("%lld", &x);
    int cnt = 0;
    for (int i = 0; i < N; i++){
        if (a[i] < x){
            a[cnt] = a[i];
            cnt++;
        }
    }
    printf("%d\n%d\n", cnt, N - cnt);
    free(a);
    return 0;
}
