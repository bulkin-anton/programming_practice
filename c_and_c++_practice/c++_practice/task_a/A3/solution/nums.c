#include "nums.h"
#include <stdlib.h>
#include <stdio.h>
static int *nums = NULL, c = 0, s = 0;

void
append_nums(int n){
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

int
cnt_nums(void){
    return s;
}

int
cmp_end_nums(void){
    if (s >= 2 && nums[s - 1] == nums[s - 2]){
        return 1;
    }
    return 0;
}

void
delete_last_num(void){
    nums = realloc(nums, (--s) * sizeof *nums);
    c = s;
}

int
get_num(int i){
    return nums[i];
}

void
free_nums(void){
    free(nums);
}
