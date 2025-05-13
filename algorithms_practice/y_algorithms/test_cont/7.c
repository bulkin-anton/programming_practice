#include <stdio.h>

int max(int a, int b){
    if (a > b){
        return a;
    }
    return b;
}

int min(int a, int b){
    if (a < b){
        return a;
    }
    return b;
}

int
check_square(int a[][1000], int N,
int M, int i, int j, int size){
    for (int k = i; k < (i + size); k++){
        for (int l = j; l < (j + size); l++){
            if ((k >= N) || (l >= M) || (a[k][l] == 0)){
                return 0;
            }
        }
    }
    return 1;
}

int
main(void){
    int N, M, el, max_size = 0, size;
    static int arr[1000][1000];
    scanf("%d", &N);
    scanf("%d", &M);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            scanf("%d", &arr[i][j]);
        }
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            el = arr[i][j];
            size = 0;
            if (el == 1){
                size = 1;
                for (int k = 2; k <= min(N, M); k++){
                    if (check_square(arr, N, M, i, j, k)){
                        size = k;
                    }
                    else{
                        break;
                    }
                }
            }
            if (size > max_size){
                max_size = size;
            }
        }
    }
    printf("%d\n", max_size);
    return 0;
}
