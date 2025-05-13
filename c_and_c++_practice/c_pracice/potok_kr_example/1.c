#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[]){
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    if (fork() == 0){
        dup2(fd1[1], 1);
        close(fd1[1]);
        close(fd1[0]);
        execlp(argv[1], argv[1], (char *) NULL);
        exit(1);
    }
    close(fd1[1]);
    pipe(fd2);
    if (fork() == 0){
        int status;
        dup2(fd1[0], 0);
        close(fd1[0]);
        close(fd2[0]);
        if (fork() == 0){
            int fd = open(argv[3], O_CREAT | O_TRUNC | O_WRONLY, 0666);
            dup2(fd, 1);
            close(fd);
            close(fd2[1]);
            execlp(argv[2], argv[2], (char *) NULL);
            exit(1);
        }
        wait(&status);
        dup2(fd2[1], 1);
        close(fd2[1]);
        if (((WIFEXITED(status) == 1) && (WEXITSTATUS(status) == 0)) == 0){
            if (fork() == 0){
                execlp(argv[4], argv[4], (char *) NULL);
                exit(1);
            }
            wait(NULL);
        }
    }
    close(fd1[0]);
    close(fd2[1]);
    if (fork() == 0){
        dup2(fd2[0], 0);
        close(fd2[0]);
        execlp(argv[5], argv[5], (char *) NULL);
        exit(1);
    }
    close(fd2[0]);
    while(wait(NULL) != -1){
    }
    return 0;
}
