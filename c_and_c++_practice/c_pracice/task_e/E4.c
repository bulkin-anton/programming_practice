#include <stdio.h>
#include <string.h>

enum {STR_SIZE = 82};

void
str_maxlen_prnt(char **str_pointers){
    char **pntr = str_pointers;
    int len, max_len = 0;
    while (*pntr != NULL){
        len = strlen(*pntr); 
        if (len > max_len){
            max_len = len;
        }
        pntr++;
    }
    pntr = str_pointers;
    while (*pntr != NULL){
        if (strlen(*pntr) == max_len){
            printf("%s\n", *pntr);
        }
        pntr++;
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
    str_maxlen_prnt(pntrs_arr);
    return 0;
}
