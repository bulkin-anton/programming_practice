#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
    grep -i "^[a-z_][a-z0-9_]*(" | cut "-d" "(" -f 1 | sort
*/

int
main(void){
    int fd_1[2], fd_2[2];
    pipe(fd_1);
    if (fork() == 0){
        dup2(fd_1[1], 1);
        close(fd_1[1]);
        close(fd_1[0]);
        execlp("grep", "grep", "-i", "^[a-z_][a-z0-9_]*(", (char *) NULL);
        return 1;
    }
    close(fd_1[1]);
    pipe(fd_2);
    if (fork() == 0){
        dup2(fd_1[0], 0);
        dup2(fd_2[1], 1);
        close(fd_1[0]);
        close(fd_2[0]);
        close(fd_1[0]);
        execlp("cut", "cut", "-d", "(", "-f", "1", (char *) NULL);
        return 1;
    }
    close(fd_1[0]);
    close(fd_2[1]);
    if (fork() == 0){
        dup2(fd_2[0], 0);
        close(fd_2[0]);
        execlp("sort", "sort", (char *) NULL);
        return 1;
    }
    close(fd_2[0]);
    while (wait(NULL) != -1){
    }
    return 0;
}
