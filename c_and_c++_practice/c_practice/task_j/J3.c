#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int
main(int parc, char *parms[]){
    int status;
    char *p2;
    if (parc > 2){
        p2 = parms[parc - 1];
        parms[parc - 1] = NULL;
        if (fork() == 0){
            execvp(parms[1], &parms[1]);
        }
        wait(&status);
        if ((WIFEXITED(status)) && (WEXITSTATUS(status) == 0)){
            if (fork() == 0){
                execlp(p2, p2, NULL);
            }
            wait(&status);
        }
    }
    return 0;
}
