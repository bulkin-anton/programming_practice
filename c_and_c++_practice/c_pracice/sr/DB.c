#include <stdio.h>
#include <string.h>

enum {STR_SIZE = 82};

void
str_change(char *str){
    unsigned len, cnt_C = 0, cnt_D = 0;
    char *pntr;
    if (str == NULL){
        return;
    }
    pntr = str;
    len = strlen(pntr);
    for (unsigned i = 0; i < len; i++, pntr++){
        if (*pntr == 'C'){
            cnt_C++;
        }
        if (*pntr == 'D'){
            cnt_D++;
        }
    }
    pntr = str;
    if (cnt_C > cnt_D){
        for (unsigned i = 0; i < len; i++, pntr++){
            if (*pntr == 'A'){
                *pntr = 'B';
            }
        }
    }
}

int
main(void){
    char string[STR_SIZE];
    fgets(string, STR_SIZE, stdin);
    if (strchr(string, '\n')){
        *strchr(string, '\n') = 0;
    }
    str_change(string);
    printf("%s", string);
}
