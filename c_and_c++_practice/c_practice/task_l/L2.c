#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int
main(int parc, char *parms[]){
    int fd[2];
    pipe(fd);
    if (fork() == 0){
        int status;
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        if (fork() == 0){
            execlp(parms[1], parms[1], (char *) NULL);
            return 1;
        }
        wait(&status);
        if (!((WIFEXITED(status)) && (WEXITSTATUS(status) == 0))){
            if (fork() == 0){
                execlp(parms[2], parms[2], (char *) NULL);
                return 1;
            }
            wait(NULL);
        }
        return 0;
    }
    if (fork() == 0){
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        execvp(parms[3], &parms[3]);
        return 1;
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
