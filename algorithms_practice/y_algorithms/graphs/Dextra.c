#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <limits.h>

int
main(void){
    int N, S, F;
    static int matr[100][100];
    int *vertexes, *way, *vert_checked;
    int vertex_chosen, min_value;
    scanf("%d %d %d", &N, &S, &F);
    vertexes = malloc(sizeof(int) * N);
    way = malloc(sizeof(int) * N);
    vert_checked = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++){
        way[i] = S - 1;
        vertexes[i] = INT_MAX;
        vert_checked[i] = 0;
        for (int j = 0; j < N; j++){
            scanf("%d", &matr[i][j]);
        }
    }
    vertexes[S - 1] = 0;
    for (int i = 0; i < N; i++){
        vertex_chosen = 0;
        min_value = INT_MAX;
        for (int j = 0; j < N; j++){
            if ((vert_checked[j] == 0) &&
            (vertexes[j] < min_value)){
                vertex_chosen = j;
                min_value = vertexes[j];
            }
        }
        if (min_value == INT_MAX){
            break;
        }
        vert_checked[vertex_chosen] = 1;
        for (int j = 0; j < N; j++){
            if (matr[vertex_chosen][j] > 0){
                if (vertexes[j] > (min_value +
                matr[vertex_chosen][j])){
                    vertexes[j] = min_value + matr[vertex_chosen][j];
                    way[j] = vertex_chosen;
                }
            }
        }
    }
    if (vertexes[F - 1] < INT_MAX){
        int *way_print = malloc(sizeof(int) * N);
        int i = 0, vert = F - 1;
        while (vert != (S - 1)){
            way_print[i] = vert;
            i++;
            vert = way[vert];
        }
        way_print[i] = S - 1;
        for (int j = i; j >= 0; j--){
            printf("%d ", way_print[j] + 1);
        }
        printf("\n");
        free(way_print);
    }
    else{
        printf("-1\n");
    }
    free(vertexes);
    free(way);
    free(vert_checked);
    return 0;
}
