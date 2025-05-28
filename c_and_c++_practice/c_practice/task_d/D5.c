#include <stdio.h>
#include <string.h>

enum {STR_SIZE = 82};

int
str_eq(const char str1[], const char str2[]){
    while ((*str1 != 0) && (*str2 != 0)){
        while ((*str1 != 0) && (*str1 == ' ')){
            str1++;
        }
        while ((*str2 != 0) && (*str2 == ' ')){
            str2++;
        }
        if (*str1 != *str2){
            return 0;
        }
        str1++;
        str2++;
    }
    while(*str1 != 0){
        if (*str1 != ' '){
            return 0;
        }
        str1++;
    }
    while(*str2 != 0){
        if (*str2 != ' '){
            return 0;
        }
        str2++;
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
    if (str_eq(str1, str2)){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
}
