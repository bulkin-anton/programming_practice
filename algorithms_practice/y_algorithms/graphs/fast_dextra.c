#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct ways_t{
    int start, finish, len;
} Roads;

int
compare_ways(const void *el1, const void *el2){
    if ((*((const Roads*) el1)).start < (*((const Roads*) el2)).start){
        return -1;
    }
    else if ((*((const Roads*) el1)).start > (*((const Roads*) el2)).start){
        return 1;
    }
    else{
        if ((*((const Roads*) el1)).len < (*((const Roads*) el2)).len){
            return -1;
        }
        else{
            return 1;
        }
    }
    return 0;
}

int
main(void){
    Roads *ways;
    int N, K, A, B;
    scanf("%d %d", &N, &K);
    ways = malloc(sizeof(Roads) * K * 2);
    for (int i = 0; i < K; i++){
        scanf("%d %d %d", &ways[i].start, &ways[i].finish, &ways[i].len);
        ways[K + i].finish = ways[i].start;
        ways[K + i].start = ways[i].finish;
        ways[K + i].len = ways[i].len;
    }
    scanf("%d %d", &A, &B);
    qsort(&ways[0], 2 * K, sizeof(Roads), compare_ways);
    for (int i = 0; i < 2*K; i++){
        printf("%d %d\n", ways[i].start, ways[i].len);
    }
    free(ways);
    return 0;
}
