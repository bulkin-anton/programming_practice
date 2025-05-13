#include <stdio.h>

int
main(void){
    int var;
    scanf("%d", &var);
    if (var == 0){
        printf("A\nB\nB\nC\nC\n");
    }
    else if (var == 1){
        printf("A\nB\nC\nB\nC\n");
    }
    else{
        printf("UNKNOWN\n");
    }
    scanf("%d", &var);
    if (var == 0){
        printf("1\n2\n2\n");
    }
    else if (var == 1){
        printf("2\n1\n2\n");
    }
    else if (var == 2){
        printf("2\n2\n1\n");
    }
    else{
        printf("UNKNOWN\n");
    }
    return 0;
}
