#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <fcntl.h>

int
main(int parc, char *parms[]){
    int file;
    if (parc < 3){
        return 0;
    }
    file = creat(parms[2], 0666);
    if (fork() == 0){
        dup2(file, 1);
        execlp(parms[1], parms[1], NULL);
    }
    close(file);
    wait(NULL);
    return 0;
}
