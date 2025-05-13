#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {STR_SIZE = 82};

char*
str_chng(char* str){
    size_t len = strlen(str);
    char buf[STR_SIZE], *pntr;
    pntr = buf;
    for (size_t i = 0; i < len; i++){
        if (isdigit(*str)){
            *pntr = *str;
            pntr++;
        }
        str++;
    }
    str -= len;
    for (size_t i = len - 1; i < len; i--){
        if (!(isdigit(str[i]))){
            pntr = strncat(pntr, &str[i], 1);
        }
    }
    str = strcpy(str, buf);
    return str;
}

int
main(void){
    char str_exmpl[STR_SIZE];
    fgets(str_exmpl, STR_SIZE, stdin);
    if (strlen(str_exmpl)){
        str_exmpl[strlen(str_exmpl) - 1] = 0;
    }
    printf("%s", str_chng(str_exmpl));
    return 0;
}
