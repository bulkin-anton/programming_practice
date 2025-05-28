#include <stdio.h>
#include <string.h>

enum {STR_SIZE = 82};

int
main(void){
    unsigned len, min_len = STR_SIZE;
    char string[STR_SIZE], min_str[STR_SIZE] = {};
    while(fgets(string, STR_SIZE, stdin)){
        len = strlen(string);
        if (len < min_len){
            strcpy(min_str, string);
        }
        else if (len == min_len){
            if (strcmp(string, min_str) < 0){
                strcpy(min_str, string);
            }
        }
    }
    printf("%s", min_str);
    return 0;
}
