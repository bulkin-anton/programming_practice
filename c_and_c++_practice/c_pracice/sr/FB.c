#include <stdio.h>
#include <stdlib.h>

enum {ARR_SIZE = 1024};

int
main(void){
    int *arr, len = 0, max_len = ARR_SIZE, num;
    arr = (int *)malloc(sizeof(int) * max_len);
    while (scanf("%d", &num) == 1){
        len++;
        if (len > max_len){
            max_len *= 2;
            arr = realloc(arr, sizeof(int) * max_len);
        }
        arr[len - 1] = num;
    }
    for (int i = 0; i < (len / 2); i++){
        printf("%d\n", arr[i] + arr[len - i - 1]);
    }
    free(arr);
    return 0;
}
