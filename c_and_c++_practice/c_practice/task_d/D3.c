#include <stdio.h>
#include <string.h>

enum {STR_SIZE = 82};

int
substr(const char* srch, const char* src){
    size_t len = strlen(srch);
    if (len){
        if (strlen(src)){
            srch += len - 1;
            src += strlen(src) - 1;
            for (int i = 0; i < len; i++){
                if (*srch != *src){
                    return 0;
                }
                srch--;
                src--;
        
            }
        }
        else{
            return 0;
        }
    }
    return 1;
}

int
main(void){
    char str1[STR_SIZE], str2[STR_SIZE];
    fgets(str1, STR_SIZE, stdin);
    fgets(str2, STR_SIZE, stdin);
    if (strlen(str1)){
        str1[strlen(str1) - 1] = 0;
    }
    if (strlen(str2)){
        str2[strlen(str2) - 1] = 0;
    }
    if (substr(str1, str2)){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
}
