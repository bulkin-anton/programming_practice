#include <stdio.h>
#include "nums.h"

static void read_numbers(int);
static void shrink_numbers(void);
static void print_numbers(void);

int
main(void)
{
    read_numbers(20);
    shrink_numbers();
    read_numbers(200);
    print_numbers();
    free_nums();
}


void
read_numbers(int max)
{
    int n;
    while (cnt_nums() < max && scanf("%d", &n) == 1){
        append_nums(n);
    }
}

void
shrink_numbers(void)
{
    while (cmp_end_nums()) {
        delete_last_num();
    }
}

void
print_numbers(void)
{
    for (int k = 0; k < cnt_nums(); ++k) {
        printf("%d\n", get_num(k));
    }
}
