#include <stdio.h>
#include <string.h>

enum {STR_SIZE = 50002};

int
main(void){
    static char str[STR_SIZE];
    char *pntr;
    int len, cnt = 0, max_cnt = 0;
    fgets(str, STR_SIZE, stdin);
    int len_str = strlen(str);
    str[len_str - 1] = 0;
    for (int i = 1; i <= (len_str / 2); i++){
        pntr = str;
        while (strncmp(pntr, &pntr[i], i) == 0){
            pntr = &pntr[i];
        }
        len = strlen(pntr);
        if (len < (2 * i)){
            for (int k = 0; k < (len - i + 1); k++){
                if (str[k] != pntr[k]){
                    cnt = 0;
                    break;
                }
                else{
                    cnt++;
                }
            }
        }
        else{
            cnt = 0;
        }
        if (cnt != 0){
            max_cnt = i;
            break;
        }
    }
    if (max_cnt == 0){
        max_cnt = len_str;
    }
    printf("%d\n", max_cnt);
    return 0;
}
