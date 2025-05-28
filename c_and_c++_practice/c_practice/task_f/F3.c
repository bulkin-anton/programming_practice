#include <stdio.h>
#include <stdlib.h>

int
main(void){
    int x, *arr;
    size_t max_len = 1, len = 0;
    arr = (int*)malloc(sizeof(int));
    while (scanf("%d", &x) == 1){
        len++;
        if (len > max_len){
            max_len *= 2;
            arr = realloc(arr, max_len*sizeof(int));
        }
        arr[len - 1] = x;
    }
    for (size_t i = len; i != 0; i--){
        printf("%d ", arr[i-1]);
    }
    printf("\n");
    free(arr);
    return 0;
}
