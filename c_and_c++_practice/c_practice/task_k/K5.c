#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

enum {STR_SIZE = 2048};

void
str_write(int file_wr, char *buf, long unsigned *str_cnt){
    long unsigned cnt = *str_cnt;
    char *pntr, *prev_pntr = buf;
    while ((pntr = strchr(prev_pntr, '\n')) != NULL){
        if (cnt != 2){
            write(file_wr, prev_pntr, pntr - prev_pntr + 1);
        }
        cnt++;
        if ((pntr != (&buf[sizeof(buf) - 1])) || (*pntr == '\n')){
            prev_pntr = pntr + 1;
        }
        else{
            break;
        }
    }
    if (cnt != 2){
        write(file_wr, prev_pntr, strlen(prev_pntr));
    }
    *str_cnt = cnt;
}

int
main(int parc, char *parms[]){
    int file, myfile, n;
    long unsigned str_cnt = 1;
    char template[] = "myfileXXXXXX";
    static char buffer[STR_SIZE] = {};
    if (parc < 2){
        return 0;
    }
    myfile = mkstemp(template);
    unlink(template);
    file = open(parms[1], O_RDONLY);
    if (file == -1){
        return 0;
    }
    while ((n = read(file, buffer, sizeof(buffer) - 1)) == (sizeof(buffer) - 1)){
        if (str_cnt < 3){
            str_write(myfile, buffer, &str_cnt);
        }
        else{
            write(myfile, buffer, n);
        }
    }
    for (int i = n; i < sizeof(buffer); i++){
        buffer[i] = 0;
    }
    str_write(myfile, buffer, &str_cnt);
    lseek(myfile, 0, SEEK_SET);
    close(file);
    file = open(parms[1], O_WRONLY | O_TRUNC, 0666);
    while ((n = read(myfile, buffer, sizeof(buffer))) == sizeof(buffer)){
        write(file, buffer, sizeof(buffer));
    }
    write(file, buffer, n);
    close(file);
    close(myfile);
    return 0;
}
