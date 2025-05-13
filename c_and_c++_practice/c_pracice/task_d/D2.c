#include <stdio.h>
#include <string.h>

enum {STR_SIZE = 82};

char*
my_strcat(char *dest, const char *src){
    if (dest != NULL){
        char* pntr;
        pntr = dest + strlen(dest);
        while (*src != 0){
            *pntr++ = *src++;
        }
        *pntr = 0;
        return dest;
    }
    else{
        return (char*)src;
    }
}

int
main(void){
    char str1[2 * STR_SIZE], str2[STR_SIZE];
    fgets(str1, STR_SIZE, stdin);
    fgets(str2, STR_SIZE, stdin);
    str1[strlen(str1) - 1] = 0;
    str2[strlen(str2) - 1] = 0;
    printf("%s", (my_strcat(str1, str2)));
    return 0;
}
