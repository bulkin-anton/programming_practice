#include <stdio.h>

enum {COL_SIZE = 2000, ROW_SIZE = 3000};

int
matrix_check(int a[][COL_SIZE], int n, int m){
    if (n != m){
        return 0;
    }
    for (int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if ((j < i) && (a[i][j] != 0)){
                return 0;
            }
        }
    }
    return 1;
}

int
main(void){
    int n, m, res;
    static int matrix[ROW_SIZE][COL_SIZE];
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    res = matrix_check(matrix, n, m);
    if (res){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
    return 0;
}
