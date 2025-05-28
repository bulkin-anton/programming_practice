#include <stdio.h>
#include <stdlib.h>

struct list_t{
    struct list_t *next;
    int num;
};

int
main(void){
    int num;
    struct list_t *pntr, *first = NULL, *new;
    while(scanf("%d", &num) == 1){
        if (first){
            (*pntr).next = malloc(sizeof(struct list_t));
            pntr = (*pntr).next;
        }
        else{
            pntr = malloc(sizeof(struct list_t));
            first = pntr;
        }
        (*pntr).num = num;
        (*pntr).next = NULL;
    }
    pntr = first;
    while (pntr){
        if ((*pntr).num > 50){
            new = malloc(sizeof(struct list_t));
            (*new).num = (*pntr).num;
            (*new).next = first;
            first = new;
        }
        pntr = (*pntr).next;
    }
    pntr = first;
    while (pntr){
        printf("%d ", (*pntr).num);
        new = pntr;
        pntr = (*pntr).next;
        free(new);
    }
    return 0;
}
