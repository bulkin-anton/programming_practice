#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "pipeline.h"
#include <stdlib.h>
#include <string.h>

static char ***pipearr = NULL;
static int prog_num = 0;

int
add_to_pipeline(const char *array[], int size){
    if (size < 1){
        return -1;
    }
    prog_num++;
    pipearr = realloc(pipearr, sizeof(char **) * prog_num);
    pipearr[prog_num - 1] = malloc(sizeof(char *) * (size + 1));
    for (int i = 0; i < size; i++){
        pipearr[prog_num - 1][i] = malloc(sizeof(char) * (strlen(array[i]) + 1));
        strcpy(pipearr[prog_num - 1][i], array[i]);
    }
    pipearr[prog_num - 1][size] = NULL;
    return 0;
}

int run_pipeline(void){
    int fd_next[2] = {0, 1}, fd_prev[2];
    for (int i = 0; i < prog_num; i++){
        fd_prev[0] = fd_next[0];
        fd_prev[1] = fd_next[1];
        if (i != (prog_num - 1))
        {
            pipe(fd_next);
        }
        if (fork() == 0)
        {
            if (i > 0)
            {
                dup2(fd_prev[0], 0);
                close(fd_prev[0]);
                close(fd_prev[1]);
            }
            if (i != (prog_num - 1))
            {
                dup2(fd_next[1], 1);
                close(fd_next[0]);
                close(fd_next[1]);
            }
            execvp(pipearr[i][0], pipearr[i]);
            return 0;
        }
        if (i > 0)
        {
            close(fd_prev[0]);
            close(fd_prev[1]);
        }
    }
    while(wait(NULL) != -1);
    return 0;
}

void
free_pipeline(void){
    int j = 0;
    for (int i = 0; i < prog_num; i++){
        j = 0;
        while (pipearr[i][j] != NULL){
            free(pipearr[i][j++]);
        }
        free(pipearr[i]);
    }
    free(pipearr);
}
