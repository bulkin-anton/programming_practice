#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {STR_SIZE = 8};

int
func_sort(const void *arg1, const void *arg2){
    return strcmp(*((char **) arg1), *((char **) arg2));
}

void
*my_bsearch(void *key, void *base, size_t len, size_t size,
int (*func_cmp_str)(const void *, const void *)){
    int left = 0, right = len - 1, mid;
    void *pntr;
    int res;
    while (right >= left){
        mid = (left + right) / 2;
        pntr = (void *)((char *)base + size * mid);
        res = func_cmp_str(pntr, key);
        if (res < 0){
            left = mid + 1;
        }
        else{
            if (res == 0){
                return pntr;
            }
            else{
                right = mid - 1;
            }
        }
    }
    return NULL;
}

int
main(int parc, char *parms[]){
    char string[STR_SIZE], **res, *str, *ent_srch;
    qsort(&parms[1], parc - 1, sizeof(char*), func_sort);
    fgets(string, STR_SIZE*sizeof(char), stdin);
    ent_srch = strchr(string, '\n');
    if (ent_srch != NULL){
        *ent_srch = 0;
    }
    str = &string[0];
    res = my_bsearch(&(str), &parms[1], parc - 1, sizeof(char *), func_sort);
    if (res != NULL){
        printf("%ld\n", (((char *)res - (char *)(&parms[1]))/sizeof(char *)) + 1);
    }
    else{
        printf("0\n");
    }
    return 0;
}
