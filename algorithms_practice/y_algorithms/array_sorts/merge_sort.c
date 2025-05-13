#include <stdio.h>
#include <stdlib.h>

void
arr_merge(long long int *arr1, int l, int r, int len){
    if (l >= r){
        return;
    }
    int mid = l + (r - l) / 2;
    arr_merge(arr1, l, mid, len);
    arr_merge(arr1, mid + 1, r, len);
    long long int *arr = malloc(sizeof(long long int) * len);
    for (int k = l; k <= r; k++){
        arr[k] = arr1[k];
    }
    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++){
        if (i > mid) {
            arr1[k] = arr[j];
            j++;
        } else if (j > r) {
            arr1[k] = arr[i];
            i++;
        } else if (arr[j] < arr[i]) {
            arr1[k] = arr[j];
            j++;
        } else {
            arr1[k] = arr[i];
            i++;
        }
    }
    free(arr);
}

int
main(void){
    int N;
    long long int *nums;
    scanf("%d", &N);
    nums = malloc(N * sizeof(long long int));
    for (int i = 0; i < N; i++){
        scanf("%lld", &nums[i]);
    }
    arr_merge(nums, 0, N - 1, N);
    for (int i = 0; i < N; i++){
        printf("%lld ", nums[i]);
    }
    printf("\n");
    free(nums);
    return 0;
}
