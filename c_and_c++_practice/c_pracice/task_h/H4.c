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
    static unsigned cnt_add = 0;
    cnt_add++;
    if (cnt_add % 2 != 0){
        printf("%u\n", cnt_add);
    }
}

void
func_sub(char *str){
    static unsigned cnt_sub = 0;
    cnt_sub++;
    if (cnt_sub == 2){
        exit(0);
    }
}

void
func_default(char *str){
    return;
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
    comp.func_deflt = func_default;
    for (int i = 1; i < parc; i++){
        switch_exec(comp, parms[i]);
    }
    return 0;
}
