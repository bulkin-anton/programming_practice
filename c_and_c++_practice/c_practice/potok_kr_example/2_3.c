#include <unistd.h>
#include <sys/wait.h>

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
    if (fork() == 0){
        if (fork() == 0){
            execlp(argv[1], argv[1], (char *) NULL);
        }
        if (wait_func(&status)){
            return 0;
        } else{
            if (fork() == 0){
                execlp(argv[2], argv[2], (char *) NULL);
            }
            if (wait_func(&status)){
                return 0;
            } else{
                return 1;
            }
        }
    }
    if (wait_func(&status)){
        if (fork() == 0){
            execlp(argv[3], argv[3], (char *) NULL);
        }
        if (wait_func(&status)){
            return 0;
        } else{
            return 1;
        }
    } else{
        return 1;
    }
}
