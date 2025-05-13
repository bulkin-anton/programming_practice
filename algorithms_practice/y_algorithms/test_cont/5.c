#include <stdio.h>
#include <stdlib.h>

int
main(void){
    int N, *stdts, cnt_l = 1, cnt_r;
    long long s = 0, h;
    scanf("%d", &N);
    cnt_r = N - 1;
    stdts = malloc(N * sizeof(int));
    for (int i = 0; i < N; ++i){
        scanf("%d", &stdts[i]);
    }
    for (int j = 0; j < N; j++){
        s += abs(stdts[j] - stdts[0]);
    }
    printf("%lld ", s);
    for (int i = 1; i < N; i++){
        h = stdts[i] - stdts[i - 1];
        s += (cnt_l - cnt_r) * h;
        printf("%lld ", s);
        cnt_l++;
        cnt_r--;
    }
    free(stdts);
    return 0;
}
