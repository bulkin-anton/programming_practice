#include <stdio.h>
#include <stdlib.h>

struct BiderList{
    int num;
    struct BiderList *prev, *next;
};

void
del_element(struct BiderList *list_pntr,
struct BiderList *el_pntr){
    if ((*el_pntr).prev != NULL){
        (*(*el_pntr).prev).next = (*el_pntr).next;
    }
    if ((*el_pntr).next != NULL){
        (*(*el_pntr).next).prev = (*el_pntr).prev;
    }
}

void
usel_to_end(struct BiderList *list_pntr,
struct BiderList *usel_pntr){
    if ((*(*usel_pntr).next).prev != NULL){
        (*(*(*usel_pntr).next).prev).next = usel_pntr;
        (*usel_pntr).prev = (*(*usel_pntr).next).prev;
    }
    else{
        (*list_pntr).next = usel_pntr;
    }
    (*(*usel_pntr).next).prev =  usel_pntr;
}

void
add_el(struct BiderList *list_pntr, int num){
    struct BiderList *el_pntr;
    el_pntr = malloc(sizeof(struct BiderList));
    (*el_pntr).num = num;
    if (list_pntr != NULL){
        (*el_pntr).next = list_pntr;
        usel_to_end(list_pntr, el_pntr);
    }
}

void
remake_list(struct BiderList **list_pntr){
    struct BiderList *pntr, *save_pntr, *usl_pntr;
    int list_pointer_deleted;
    pntr = *list_pntr;
    usl_pntr = NULL;
    do{
        list_pointer_deleted = 0;
        if ((*pntr).num > 100){
            if (pntr != *list_pntr){
                save_pntr = pntr;
                pntr = (*pntr).next;
                del_element(*list_pntr, save_pntr);
                (*save_pntr).next = *list_pntr;
                usel_to_end(*list_pntr, save_pntr);
                if (usl_pntr == NULL){
                    usl_pntr = save_pntr;
                }
            }
            else{
                if (usl_pntr == NULL){
                    usl_pntr = pntr;
                }
                pntr = (*pntr).next;
                *list_pntr = pntr;
                list_pointer_deleted = 1;
            }
        }
        else{
            if ((*pntr).num % 2 != 0){
                if (pntr == *list_pntr){
                    if (*list_pntr == (**list_pntr).next){
                        free(*list_pntr);
                        *list_pntr = NULL;
                        break;
                    }
                    else{
                        *list_pntr = (**list_pntr).next;
                        list_pointer_deleted = 1;
                    }
                }
                pntr = (*pntr).next;
                save_pntr = (*pntr).prev;
                del_element(*list_pntr, save_pntr);
                free(save_pntr);
            }
            else{
                pntr = (*pntr).next;
            }
        }
    } while ((*list_pntr) && ((pntr != *list_pntr) ||
    (list_pointer_deleted)) && (pntr != usl_pntr));
}

int
main(void){
    int x;
    struct BiderList *list_pntr, *pntr;
    if (scanf("%d", &x) == 1){
        list_pntr = malloc(sizeof(struct BiderList));
        (*list_pntr).next = list_pntr;
        (*list_pntr).prev = list_pntr;
        (*list_pntr).num = x;
        while(scanf("%d", &x) == 1){
            add_el(list_pntr, x);
        }
        remake_list(&list_pntr);
        if (list_pntr){
            pntr = list_pntr;
            do{
                pntr = (*pntr).prev;
                if ((*pntr).next != list_pntr){
                    free((*pntr).next);
                }
                printf("%d ", (*pntr).num);
            } while (pntr != list_pntr);
            printf("\n");
            free(list_pntr);
        }
    }
    return 0;
}
