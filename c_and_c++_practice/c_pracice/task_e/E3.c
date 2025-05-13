#include <stdio.h>
#include <string.h>
enum {STR_SIZE = 82};

void
str_prnt(char **str_pointers){
    while (*str_pointers != NULL){
        if (strlen(*str_pointers) > 2){
            printf("%c%c%c\n", **str_pointers,
            *(*str_pointers + 1), *(*str_pointers + 2));
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
    str_prnt(pntrs_arr);
    return 0;
}
