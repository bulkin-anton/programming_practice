#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int
wait_func(int *status){
    wait(status);
    if ((WIFEXITED(*status)) && (WEXITSTATUS(*status) == 0)){
        return 1;
    } else{
        return 0;
    }
}

int
main(int argc, char *argv[]){
    int status;
    int fd[2];
    pipe(fd);
    if (fork() == 0){
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);
        if (fork() == 0){
            int fd1 = open(argv[2], O_RDONLY);
            dup2(fd1, 0);
            close(fd1);
            execlp(argv[1], argv[1], (char *) NULL);
        }
        if (wait_func(&status) != 0){
            return 0;
        } else{
            if (fork() == 0){
                execlp(argv[3], argv[3], (char *) NULL);
            }
            wait(NULL);
        }
    }
    close(fd[1]);
    if (fork() == 0){
        dup2(fd[0], 0);
        close(fd[0]);
        int fd1 = open(argv[3], O_WRONLY | O_CREAT, 0666);
        dup2(fd1, 1);
        close(fd1);
        execlp(argv[5], argv[5], (char *) NULL);
    }
    while(wait(NULL) != -1);
    close(fd[0]);
}
