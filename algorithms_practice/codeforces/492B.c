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
    int n, l, *a, d = 0;
    scanf("%d %d", &n, &l);
    a = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    qsort(a, n, sizeof(int), compare);
    for (int i = 0; i < (n - 1); i++){
        if (d < (abs(a[i] - a[i + 1]))){
            d = abs(a[i] - a[i + 1]);
        }
    }
    if (d / 2 < a[0]){
        d = 2 * a[0];
    }
    if (d / 2 < (l - a[n - 1])){
        d = l - a[n - 1];
        d *= 2;
    }
    printf("%f", d / 2.0);
    free(a);
    return 0;
}
