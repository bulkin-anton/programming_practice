#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int
main(int parc, char *parms[]){
    char arr[] = "--";
    int fd[2], arg_2 = 0;
    for (int i = 1; i < parc; i++){
        if (strcmp(parms[i], arr) == 0){
            arg_2 = i + 1;
            parms[i] = (char *) NULL;
            break;
        }
    }
    pipe(fd);
    if (fork() == 0){
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execvp(parms[1], &parms[1]);
    }
    if (fork() == 0){
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        execvp(parms[arg_2], &parms[arg_2]);
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
