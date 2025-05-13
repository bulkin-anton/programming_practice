#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int
main(void){
    int fd[2];
    pipe(fd);
    if (fork() == 0){
        close(fd[0]);
        int cnt = 0;
        char el;
        while (read(0, &el, 1) == 1){
            cnt++;
            if ((cnt % 2) == 0){
                write(fd[1], &el, 1);
            }
        }
        close(fd[1]);
        return 0;
    }
    close(fd[1]);
    if (fork() == 0){
        if (fork() == 0){
            int cnt_el = 0;
            char lit;
            while (read(fd[0], &lit, 1) == 1){
                cnt_el++;
                if ((cnt_el % 2) == 0){
                    write(1, &lit, 1);
                }
            }
            close(fd[0]);
            return 0;
        }
        close(fd[0]);
        wait(NULL);
        return 0;
    }
    close(fd[0]);
    while (wait(NULL) != -1){
    }
    return 0;
}
