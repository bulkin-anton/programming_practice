#include <stdio.h>
#include <stdlib.h>

int
main(void){
    int N, M, *nums, *ans, cnt;
    scanf("%d %d", &N, &M);
    nums = malloc(N * sizeof(int));
    ans = calloc(sizeof(int), N);
    ans[0] = N;
    int k = 1;
    for (int i = 0; i < N; i++){
        scanf("%d", &nums[i]);
    }
    for (int i = 0; i < (N / 2); i++){
        cnt = 0;
        for (int j = 0; j < (i + 1); j++){
            if (nums[i - j] == nums[i + j + 1]){
                cnt++;
            }
            else{
                break;
            }
        }
        if (cnt == (i + 1)){
            ans[k] = N - i - 1;
            k++;
        }
    }
    for (int i = k - 1; i >= 0; i--){
        printf("%d ", ans[i]);
    }
    printf("\n");
    free(nums);
    free(ans);
    return 0;
}
