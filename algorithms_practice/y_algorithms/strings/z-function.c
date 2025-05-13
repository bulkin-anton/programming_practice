#include <stdio.h>
#include <string.h>

enum {STR_SIZE = 1000002};

int
z_func(char *string, char *pos){
    int len = 0;
    int len_str = strlen(pos);
    for (int i = 0; i < len_str; i++){
        if (pos[i] == string[i]){
            len++;
        }
        else{
            break;
        }
    }
    return len;
}

int
main(void){
    static char string[STR_SIZE];
    fgets(string, STR_SIZE, stdin);
    if (strchr(string, '\n') != NULL){
        *strchr(string, '\n') = 0;
    }
    int len = strlen(string);
    printf("0 ");
    for (int i = 1; i < len; i++){
        printf("%d ", z_func(string, &string[i]));
    }
    printf("\n");
    return 0;
}
