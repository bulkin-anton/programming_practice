#include <stdio.h>
#include <string.h>

enum {STR_SIZE = 82};

void
str_to_from(char *source, char *str){
    char *to_pntr, *from_pntr, *chng_str;
    unsigned len_from, len_str, len_to;
    to_pntr = source;
    from_pntr = strstr(source, "<-");
    *from_pntr = 0;
    from_pntr++;
    *from_pntr = 0;
    from_pntr++;
    if (*from_pntr == 0){
        return;
    }
    else{
        chng_str = strstr(str, from_pntr);
        if (chng_str == NULL){
            return;
        }
        len_from = strlen(from_pntr);
        if (*to_pntr == 0){
            len_str = strlen(chng_str);
            for (unsigned i = 0; i < (len_str - len_from); i++){
                chng_str[i] = chng_str[i + len_from];
            }
        }
        else{
            len_to = strlen(to_pntr);
            for (unsigned i = 0; i < len_to; i++){
                chng_str[i] = to_pntr[i];
            }
            chng_str += strlen(to_pntr);
            len_str = strlen(chng_str);
            len_from -= strlen(to_pntr);
            for (unsigned i = 0; i < (len_str - len_from); i++){
                chng_str[i] = chng_str[i + len_from];
            }
        }
        str += strlen(str) - len_from;
        for (unsigned i = 0; i < len_from; i++){
            str[i] = 0;
        }
    }
}

int
main(void){
    char string[STR_SIZE] = {}, source[STR_SIZE] = {};
    fgets(source, STR_SIZE, stdin);
    fgets(string, STR_SIZE, stdin);
    if (strchr(string, '\n')){
        *strchr(string, '\n') = 0;
    }
    if (strchr(source, '\n')){
        *strchr(source, '\n') = 0;
    }
    str_to_from(source, string);
    printf("%s\n", string);
    return 0;
}
