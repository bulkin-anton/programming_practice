#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

enum {CASE_SIZE = 1024};

typedef void (*res_t)(char *);

typedef struct str_switch{
    const char *case_num[CASE_SIZE];
    res_t funcs[CASE_SIZE], func_deflt;
} StrSwitch;

void
func_add(char *str){
    printf("ADD\n");
}

void
func_sub(char *str){
    printf("SUB\n");
}

void
func_num_check(char *str){
    char *pntr;
    long int res;
    if (str){
        errno = 0;
        res = strtol(str, &pntr, 10);
        if ((errno == 0) && (pntr != str) && (*pntr == '\0')){
            if ((res >= INT_MIN) && (res <= INT_MAX)){
                printf("NUMBER\n");
                return;
            }
        }
    }
    printf("UNKNOWN\n");
}

void
switch_exec(StrSwitch a, char *str){
    for (size_t i = 0; i < (sizeof(a.case_num) / sizeof(a.case_num[0])); i++){
        if (a.funcs[i]){
            if (str){
                if (strcmp(str, a.case_num[i]) == 0){
                    a.funcs[i](str);
                    return;
                }
            }
            else{
                if (a.case_num[i] == NULL){
                    a.funcs[i](str);
                    return;
                }
            }
        }
    }
    a.func_deflt(str);
}

int
main(int parc, char *parms[]){
    char str_add[] = "add";
    char str_sub[] = "sub";
    StrSwitch comp = {};
    comp.case_num[0] = str_add;
    comp.case_num[1] = str_sub;
    comp.funcs[0] = func_add;
    comp.funcs[1]= func_sub;
    comp.func_deflt = func_num_check;
    for (int i = 1; i < parc; i++){
        switch_exec(comp, parms[i]);
    }
    return 0;
}
