#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int
main(int parmc, char *parms[]){
    int fd = open(parms[1], O_RDWR);
    char x;
    if (read(fd, &x, sizeof(x)) > 0){
        x = x ^ 2;
        x = x ^ 8;
        lseek(fd, -sizeof(char), SEEK_CUR);
        write(fd, &x, sizeof(x));
    }
    close(fd);
    return 0;
}
