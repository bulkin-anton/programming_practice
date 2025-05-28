#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

enum {FILE_SIZE = 32};

void
write_file(int w_file, int r_file, char c){
    long pos_w, pos_r;
    pos_w = lseek(w_file, 0, SEEK_CUR);
    pos_r = lseek(r_file, 0, SEEK_CUR);
    while (((pos_w + 1) == pos_r) ||
    ((pos_r == 0) && ((pos_w + 1) == FILE_SIZE))){
        usleep(50);
        pos_r = lseek(r_file, 0, SEEK_CUR);
    }
    write(w_file, &c, 1);
    if (lseek(w_file, 0, SEEK_CUR) == FILE_SIZE){
        lseek(w_file, 0, SEEK_SET);
    }
}

int
read_file(int w_file, int r_file, char *c){
    long pos_w, pos_r;
    pos_r = lseek(r_file, 0, SEEK_CUR);
    pos_w = lseek(w_file, 0, SEEK_CUR);
    if (waitpid(-1, NULL, WNOHANG) > 0){
        if (pos_r != pos_w){
            if (pos_r == FILE_SIZE){
                lseek(r_file, 0, SEEK_SET);
            }
            if (pos_w != 0){
                read(r_file, c, 1);
                return 1;
            }
        }
        return 0;
    }
    else{
        if (pos_r != pos_w){
            if (pos_r == FILE_SIZE){
                lseek(r_file, 0, SEEK_SET);
                if (pos_w == 0){
                    return 2;
                }
            }
            read(r_file, c, 1);
            return 1;
        }
        else{
            return 2;
        }
    }
}

int
main(void){
    char c, template[] = "myfileXXXXXX";
    int w_file, r_file, res;
    w_file = mkstemp(template);
    r_file = open(template, O_RDONLY);
    unlink(template);
    if (fork() == 0){
        while (read(0, &c, 1)){
            write_file(w_file, r_file, c);
        }
        close(w_file);
        close(r_file);
        exit(0);
    }
    while ((res = read_file(w_file, r_file, &c)) != 0){
        if (res == 1){
            write(1, &c, 1);
        }
        else if (res == 2){
            usleep(50);
        }
    }
    close(w_file);
    close(r_file);
    return 0;
}
