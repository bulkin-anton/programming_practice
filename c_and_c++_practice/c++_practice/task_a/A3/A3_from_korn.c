#include <stdio.h>
#include <stdlib.h>

int *nums = 0, c = 0, s = 0;

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
}


void
read_numbers(int max)
{
    int n;
    while (s < max && scanf("%d", &n) == 1) {
        if (c == s) {
            if (c == 0) {
                c = 100;
            } else {
                c = 2 * c;
            }
            nums = realloc(nums, c * sizeof *nums);
        }
        nums[s++] = n;
    }
}

void
shrink_numbers(void)
{
    while (s >= 2 && nums[s - 1] == nums[s - 2]) {
        nums = realloc(nums, (--s) * sizeof *nums);
    }
}

void
print_numbers(void)
{
    for (int k = 0; k < s; ++k) {
        printf("%d\n", nums[k]);
    }
}
