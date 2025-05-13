#include <stdio.h>

int
main(void){
    int t;
    int n, k;
    scanf("%d", &t);
    for (int i = 0; i < t; i++){
        scanf("%d %d", &n, &k);
        printf("%d\n", ((k / (n - 1))) * n + (k % (n - 1)) - !((k % (n - 1))));
    }
    return 0;
}
