#include <stdio.h>
#include <string.h>

int
main(int parc, char *parms[]){
    unsigned len, min_len = -1;
    if (parc == 1){
        return 0;
    }
    for (int i = 1; i < parc; i++){
        if (parms[i] == NULL){
            min_len = 0;
        }
        else{
            len = strlen(parms[i]);
            if (len < min_len){
                min_len = len;
            }
        }
    }
    for (int i = 1; i < parc; i++){
        if (parms[i] == NULL){
            printf("\n");
        }
        else{
            len = strlen(parms[i]);
            if (len == min_len){
                printf("%s\n", parms[i]);
            }
        }
    }
    return 0;
}
