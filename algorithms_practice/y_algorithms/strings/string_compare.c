#include <stdio.h>
#include <string.h>

enum {STR_SIZE = 200002};

int
main(void){
    static char str[STR_SIZE];
    fgets(str, STR_SIZE, stdin);
    int q;
    int l, a, b;
    scanf("%d", &q);
    for (int i = 0; i < q; i++){
        scanf("%d %d %d", &l, &a, &b);
        if (strncmp(&str[a], &str[b], l) == 0){
            printf("yes\n");
        }
        else{
            printf("no\n");
        }
    }
    return 0;
}
