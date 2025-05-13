#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
func_sort1(const void *arg1, const void *arg2){
    return strcmp(*((char **) arg2), *((char **) arg1));
}

int
func_sort2(const void *arg1, const void *arg2){
    long unsigned int len1, len2;
    len1 = strlen(*(char **) arg1);
    len2 = strlen(*(char **) arg2);
    if (len1 % 2 == 0){
        if (len2 % 2 == 0){
            return strcmp(*((char **) arg1), *((char **) arg2));
        }
        else{
            return -1;
        }
    }
    else{
        if (len2 % 2 == 0){
            return 1;
        }
        else{
            return strcmp(*((char **) arg2), *((char **) arg1));
        }
    }
}

int
main(int parc, char *parms[]){
    if (parc > 1){
        qsort(&parms[1], parc - 1, sizeof(char*), func_sort1);
        for (int i = 1; i < parc; i++){
            printf("%s\n", parms[i]);
        }
        qsort(&parms[1], parc - 1, sizeof(char*), func_sort2);
        for (int i = 1; i < parc; i++){
            printf("%s\n", parms[i]);
        }
    }
    return 0;
}
