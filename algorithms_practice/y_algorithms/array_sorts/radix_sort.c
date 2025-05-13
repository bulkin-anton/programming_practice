#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
phase_sort(char **strings, int n, int num_phase, int len, char **buckets[10]){
    int num, cnt[10] = {};
    for (int i = 0; i < n; i++){
        num = strings[i][len - num_phase] - '0';
        buckets[num][cnt[num]] = strings[i];
        cnt[num]++;
    }
    int j = 0;
    for (int i = 0; i < 10; i++){
        printf("Bucket %d: ", i);
        if (cnt[i] == 0){
            printf("empty\n");
        }
        else{
            for (int k = 0; k < cnt[i]; k++){
                printf("%s", buckets[i][k]);
                strings[j] = buckets[i][k];
                j++;
                buckets[i][k] = NULL;
                if ((k + 1) != cnt[i]){
                    printf(", ");
                }
            }
            printf("\n");
        }
    }
}

int
main(void){
    int n;
    char **strings, **buckets[10];
    scanf("%d\n", &n);
    strings = malloc(sizeof(char *) * n);
    for (int i = 0; i < 10; i++){
        buckets[i] = calloc(sizeof(char *), n);
    }
    for (int i = 0; i < n; i++){
        strings[i] = malloc(22 * sizeof(char));
        fgets(strings[i], 22 * sizeof(char), stdin);
        strings[i][strlen(strings[i]) - 1] = 0;
    }
    printf("Initial array:\n");
    for (int i = 0; i < n; i++){
        printf("%s", strings[i]);
        if ((i + 1) != n){
            printf(", ");
        }
    }
    printf("\n**********\n");
    int len = strlen(strings[0]);
    for (int i = 1; i <= len; i++){
        printf("Phase %d\n", i);
        phase_sort(strings, n, i, len, buckets);
        printf("**********\n");
    }
    for (int i = 0; i < 10; i++){
        free(buckets[i]);
    }
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++){
        printf("%s", strings[i]);
        if ((i + 1) != n){
            printf(", ");
        }
        free(strings[i]);
    }
    printf("\n");
    free(strings);
    return 0;
}
