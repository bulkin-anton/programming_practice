#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct list_item{
    char *str;
    struct list_item *next, *prev;
};

void
display(struct list_item **head)
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    struct list_item *temp = *head;
    do
    {
        fputs(temp->str, stdout);
        printf(" ");
        temp = temp->next;
    } while (temp != *head);

    printf("\n");
}

void
process(struct list_item ** list, const char * str)
{
    if (list == NULL) {
        return;
    }
    if (*list == NULL) {
        return;
    }
    struct list_item *pntr = NULL, *buf, *new;
    struct list_item *end = (**list).prev;
    int len, stop = 1;
    do{
        if (pntr == NULL){
            pntr = *list;
        } else{
            pntr = (*pntr).next;
        }
        if (pntr == end){
            stop = 0;
        }
        if (strstr((*pntr).str, str) != NULL){
            len = strlen((*pntr).str);
            for (int i = 0; i < len; i++){
                new = malloc(sizeof(*pntr));
                (*new).str = malloc(len + 1);
                strcpy((*new).str, (*pntr).str);
                (*new).next = (*pntr).next;
                (*new).prev = pntr;
                (*(*pntr).next).prev = new;
                (*pntr).next = new;
                pntr = new;
            }
        } else{
            if (pntr == *list){
                *list = (*pntr).next;
            } else{
                buf = (*pntr).next;
                (*(*pntr).next).prev = (*pntr).prev;
                (*(*pntr).prev).next = (*pntr).next;
                (*(**list).prev).next = pntr;
                (*pntr).next = *list;
                (*pntr).prev = (**list).prev;
                (**list).prev = pntr;
                pntr = (*buf).prev;
            }
        }
    } while (stop);
}

struct list_item *
read_list(void)
{
	struct list_item *begin = NULL;
	char name[100];
	int c, i = 0, flag = 1;
	do {
		c = getchar();
		if (isspace(c)) {
			name[i] = '\0';
			struct list_item *lis = malloc(sizeof(struct list_item));
			lis->str = malloc(strlen(name) + 1);
			strcpy(lis->str, name);
//			printf("%s\n", name);
			if (flag) {
				begin = lis;
				lis->next = lis;
				lis->prev = lis;
				flag = 0;
			} else {
				lis->prev = begin->prev;
				lis->next = begin;
				begin->prev->next = lis;
				begin->prev = lis;
			}
			i = 0;
		} else {
			name[i++] = (char) c;
		}
	} while (c != EOF && c != '\n');
	return begin;
}

int
main(void){
    const char *substring = "abc";

    struct list_item *head = read_list();

    process(&head, substring);

    printf("Output:\n");
    display(&head);
    struct list_item *pntr = (*head).prev;
    while (pntr != head){
        if ((*pntr).next != head){
            free((*(*pntr).next).str);
            free((*pntr).next);
        }
        pntr = (*pntr).prev;
    }
    if ((*pntr).next != head){
            free((*(*pntr).next).str);
            free((*pntr).next);
    }
    free((*head).str);
    free(head);
    return 0;
}
