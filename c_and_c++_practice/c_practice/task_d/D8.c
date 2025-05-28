#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {STR_SIZE = 82};

void
num_finder(const char* str, unsigned *res_pntr,
unsigned *len_pntr, const char** pos_pntr){
    const char *pntr, *postn = NULL;
    unsigned len = 0, res = 0, i = 1;
    while(i < 10){
        pntr = strchr(str, '0' + i);
        if(postn && pntr){
            if (strlen(postn) < strlen(pntr)){
                postn = pntr;
                res = 1;
            }
        }
        else{
            if (pntr){
                postn = pntr;
                res = 1;
            }
        }
        i++;
    }
    pntr = postn;
    if (res){
        while ((strlen(pntr) > 0) && (isdigit(*pntr))){
            len++;
            pntr++;
        }
    }
    else{
        postn = NULL;
        len = 0;
    }
    pntr = strchr(str, '0');
    if (pntr != NULL){
        if (postn == NULL){
            postn = pntr;
            len = 1;
            res = 1;
        }
        else{
            if ((strlen(pntr) > 2) && (!(isdigit(*(pntr + 1)))) &&
            (strlen(pntr) > strlen(postn))){
                postn = pntr;
                len = 1;
                res = 1;
            }
            
        }
    }
    *res_pntr = res;
    *len_pntr = len;
    *pos_pntr = postn;
}

int
main(void){
    char str_in[STR_SIZE], num[STR_SIZE], max[STR_SIZE] = {}, *max_arr, *num_arr;
    const char *ans_pntr, *postn;
    unsigned ans_res, ans_len, ans_exist = 0;
    max_arr = max;
    num_arr = num;
    postn = str_in;
    fgets(str_in, STR_SIZE, stdin);
    if (strlen(str_in)){
        str_in[strlen(str_in) - 1] = 0;
    }
    num_finder(str_in, &ans_res, &ans_len, &ans_pntr);
    while (ans_res){
        ans_exist = 1;
        for(size_t i = 0; i < strlen(num_arr); i++){
            num_arr[i] = 0;
        }
        strncpy(num_arr, ans_pntr, ans_len);
        if ((ans_len > strlen(max_arr)) || ((ans_len == strlen(max_arr) &&
        (strcmp(max_arr, num_arr) < 1)))){
            for(size_t i = 0; i < strlen(max_arr); i++){
                max_arr[i] = 0;
            }
            strcpy(max_arr, num_arr);
        }
        postn = ans_pntr + ans_len;
        num_finder(postn, &ans_res, &ans_len, &ans_pntr);
    }
    if (ans_exist){
        printf("%s", max);
    }
}
