#include <stdio.h>
#include <stdlib.h>

int
main(void){
    unsigned long long k, *floors, s = 0, buf;
    int j, n, len = 0;
    scanf("%llu", &k);
    scanf("%d", &n);
    floors = malloc(sizeof(unsigned long long) * n);
    for (int i = 0; i < n; i++){
        scanf("%llu", &floors[i]);
        if (floors[i] != 0){
            len = i;
        }
    }
    if (len == 0){
        return 0;
    }
    for (int i = n - 1; i >= 0; i--){
        s += (floors[i] / k) * 2 * (i + 1);
        floors[i] %= k;
        if ((floors[i] != 0) && (i != 0)){
            buf = floors[i];
            j = i - 1;
            s += 2 * (i + 1);
            while ((buf != k) && (j >= 0)){
                if ((floors[j] + buf) >= k){
                    buf = k;
                    i = j;
                    floors[j] -= (k - buf);
                }
                else{
                    j--;
                    buf += floors[j];
                    floors[j] = 0;
                }
            }
            if (j == 0){
                s += 2;
                printf("%llu\n", s);
                free(floors);
                return 0;
            }
        }
    }
    printf("%llu", s);
    free(floors);
    return 0;
}
