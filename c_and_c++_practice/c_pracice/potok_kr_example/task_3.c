#include <stdio.h>

int
main(void){
    int a, b, n;
    scanf("%d%d%d", &a, &b, &n);
    for (long long i = (long long)a - 1; i < b; i++){
        for (long long j = (long long)a - 1; j < b; j++){
            if (i == (a - 1)){
                if (j == (a - 1)){
                    for (int k = 0; k < n; k++){
                        printf(" ");
                    }
                }
                else{
                    printf(" %*lld", n, j);
                }
            }
            else{
                if (j == (a - 1)){
                    printf("%*lld", n, i);
                }
                else{
                    if (j != b){
                        printf(" %*lld", n , (long long)i * j);
                    }
                }
            }
        }
        printf("\n");
    }
    return 0;
}
