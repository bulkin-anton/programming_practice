#include <string.h>
#include <stdio.h>
#include <ctype.h>

void
str_change_toup(char **arr_str, int size){
    char *cur_str;
    if (arr_str == NULL){
        return;
    }
    for (int i = 0; i < size; i++){
        cur_str = arr_str[i];
        if ((cur_str != NULL) && (strlen(cur_str) > 2)){
            for (int j = 0; j < 3; j++){
                cur_str[j] = toupper(cur_str[j]);
            }
        }
    }
}

int
main(int parc, char *parms[]){
    if (parc == 1){
        return 0;
    }
    str_change_toup(parms + 1, parc - 1);
    for (int i = 1; i < parc; i++){
        if (parms[i] == NULL){
            printf("\n");
        }
        else{
            printf("%s\n", parms[i]);
        }
    }
    return 0;
}
