#include <stdio.h>
#include <stdlib.h>

int
compare(const void *a,const void *b){
    if ((*((int *) a)) > (*((int *) b))){
        return 1;
    }
    return -1;
}

int
main(void){
    int n, m, *c, k, mid, l, r;
    scanf("%d", &n);
    c = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++){
        scanf("%d", &c[i]);
        if (i){
            c[i] += c[i - 1];
        }
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++){
        scanf("%d", &k);
        k++;
        l = 0;
        r = n - 1;
        while (r >= l){
            mid = (r + l) / 2;
            if (c[mid] > k){
                r = mid - 1;
            } else if (c[mid] < k){
                l = mid + 1;
            } else break;
        }
        printf("%d\n", mid + 1);
    }
    free(c);
    return 0;
}
