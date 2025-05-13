#include <string.h>
#include <stdlib.h>

void process(struct List *pl, const char *str){
    struct Node *pntr, *last_check;
    int res;
    pntr = (*pl).first;
    last_check = (*pl).last;
    while (1){
        res = strcmp((*pntr).elem, str);
        if (res >= 0){
            (*(*pntr).prev).next = (*pntr).next;
            (*(*pntr).next).prev = (*pntr).prev;
            if (res == 0){
                if (pntr == (*pl).first){
                    (*pl).first = (*pntr).next;
                }
                free((*pntr).elem);
                free(pntr);
            }
            else{
                (*(*pl).last).next = pntr;
                (*pntr).prev = (*pl).last;
                (*pl).last = pntr;
                if (pntr == (*pl).first){
                    (*pl).first = (*pntr).next;
                }
            }
        }
        if (pntr == last_check){
            break;
        }
        else{
            pntr = (*pntr).next;
        }
    }
}
