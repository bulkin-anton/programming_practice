#include <stdlib.h>
#include <stdio.h>

int
main(void){
    unsigned N;
    int *arr;
    scanf("%d", &N);
    arr = malloc(sizeof(int) * N);
    for (unsigned i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }
    for (unsigned i = N; i != 0; i--){
        printf("%d\n", arr[i - 1]);
    }
    free(arr);
    return 0;
}
