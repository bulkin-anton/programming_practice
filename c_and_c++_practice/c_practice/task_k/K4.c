#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <fcntl.h>

int
main(int parc, char *parms[]){
    int file, status;
    if (parc < 5){
        return 0;
    }
    if (fork() == 0){
        file = open(parms[3], O_WRONLY | O_APPEND | O_CREAT, 0666);
        dup2(file, 1);
        if (fork() == 0){
            execlp(parms[1], parms[1], NULL);
        }
        wait(&status);
        if (!((WIFEXITED(status) && (WEXITSTATUS(status) == 0)))){
            if (fork() == 0){
                execlp(parms[2], parms[2], NULL);
            }
            wait(&status);
            close(file);
            if (WIFEXITED(status) && (WEXITSTATUS(status) == 0)){
                return 0;
            }
            else{
                return 1;
            }
        }
        else{
            close(file);
            return 0;
        }
    }
    wait(&status);
    if (WIFEXITED(status) && (WEXITSTATUS(status) == 0)){
        if (fork() == 0){
            execlp(parms[4], parms[4], NULL);
        }
        wait(NULL);
    }
    return 0;
}
