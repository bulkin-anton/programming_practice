#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {STR_SIZE = 82};

int
str_input(char **str, unsigned *len_str){
    char *pntr;
    unsigned len = 0, max_len = STR_SIZE;
    *str = malloc(STR_SIZE * sizeof(char));
    pntr = *str;
    while(fgets(pntr, STR_SIZE, stdin)){
        len += strlen(pntr);
        if (strchr(pntr, '\n')){
            len--;
            (*str)[len] = 0;
            *len_str = len;
            return 1;
        }
        else{
            pntr = *str + len; 
            if ((max_len - len) < STR_SIZE){
                max_len *= 2;
                *str = realloc(*str, max_len * sizeof(char));
                if (*str == NULL){
                    return 0;
                }
                pntr = *str + len;
            }
        }
    }
    return 0;
}

int
main(void){
    char *string, *max_str = NULL;
    unsigned len, max_len = 0;
    while (str_input(&string, &len)){
        if (len >= max_len){
            max_len = len;
            free(max_str);
            max_str = string;
        }
        else{
            free(string);
        }
    }
    printf("%s\n", max_str);
    free(string);
    free(max_str);
    return 0;
}
