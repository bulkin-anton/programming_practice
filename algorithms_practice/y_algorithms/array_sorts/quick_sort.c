#include <stdio.h>
#include <stdlib.h>

void
sort(long long int *arr, int size){
    long long int pivot;
    int l = 0;
    int r = size - 1;
    pivot = arr[size / 2];
    while (l <= r){
        while ((arr[r] > pivot)){
            r--;
        }
        while ((arr[l] < pivot)){
            l++;
        }
        if (l <= r){
            int tmp = arr[l];
            arr[l] = arr[r];
            arr[r] = tmp;
            l++;
            r--;
        }
    }
    if (l < size)
        sort(&arr[l], size - l);
    if (r > 0)
        sort(arr, r + 1);
}

int
main(void){
    int N;
    long long int *a;
    scanf("%d", &N);
    a = malloc(sizeof(*a) * N);
    for (int i = 0; i < N; i++){
        scanf("%lld", &a[i]);
    }
    sort(a, N);
    for (int i = 0; i < N; i++){
        printf("%lld ", a[i]);
    }
    printf("\n");
    free(a);
    return 0;
}
