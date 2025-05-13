#include <string.h>
#include "splitter.h"
#include <stdlib.h>

static char *delimiter = NULL;
static char **array = NULL;
static int pos = 0;
static int array_len;

void
set_delimiter(const char *str){
    if (delimiter != NULL){
        free(delimiter);
    }
    delimiter = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(delimiter, str);
}

void
set_array(int parc, const char *parms[]){
    array = malloc(parc * sizeof(char *));
    array_len = parc;
    for (int i = 0; i < parc; i++){
        array[i] = malloc((strlen(parms[i]) + 1) * sizeof(char));
        strcpy(array[i], parms[i]);
    }
}

void
free_splitter(void){
    for (int i = 0; i < array_len; i++){
        free(array[i]);
    }
    free(array);
}

int
next_block(int *begin, int *end){
    if (pos == array_len){
        return -1;
    }
    for (int i = pos; i < array_len; i++){
        if (strcmp(delimiter, array[i]) == 0){
            *begin = pos;
            pos = i + 1;
            *end = i;
            return 0;
        }
    }
    *begin = pos;
    pos = array_len;
    *end = pos;
    return 0;
}
