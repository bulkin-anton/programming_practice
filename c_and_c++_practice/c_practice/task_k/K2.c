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
    file = open(parms[2], O_RDONLY);
    if (fork() == 0){
        dup2(file, 0);
        execlp(parms[1], parms[1], NULL);
    }
    close(file);
    wait(NULL);
    return 0;
}
