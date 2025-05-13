#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int
main(int parc, char *parms[]){
    int status;
    if (parc > 1){
        if (fork() == 0){
            execvp(parms[1], &parms[1]);
        }
        if (wait(&status) != -1){
            if (WIFSIGNALED(status)){
                printf("%d\n", WTERMSIG(status));
            }
            else{
                printf("%d\n", WEXITSTATUS(status));
            }
        }
    }
    return 0;
}
