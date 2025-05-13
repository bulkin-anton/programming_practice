#include <stdio.h>
#include <string.h>

enum {STR_SIZE = 82};

void
str_begin_prnt(char **str_pointers){
    while (*str_pointers != NULL){
        if (strstr(*str_pointers, "begin")){
            printf("%s\n", *str_pointers);
        }
        str_pointers++;
    }
}

int
main(void){
    char *pntrs_arr[STR_SIZE / 2] = {}, buf[STR_SIZE], *pntr;
    int len, letter = 0, j = 0;
    fgets(buf, STR_SIZE, stdin);
    pntr = buf;
    len = strlen(buf);
    if (len){
        buf[len - 1] = 0;
    }
    for (int i = 0; i < len; i++, pntr++){
        if ((*pntr >= 'A') && (*pntr <= 'z')){
            if (!(letter)){
                letter = 1;
                pntrs_arr[j] = pntr;
                j++;
            }
        }
        else{
            *pntr = 0;
            letter = 0;
        }
    }
    str_begin_prnt(pntrs_arr);
    return 0;
}
