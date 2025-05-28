#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int
main(int parc, char *parms[]){
    int file;
    char el[2];
    if (parc < 2){
        return 0;
    }
    if ((file = open(parms[1], O_RDWR)) != -1){
        if (read(file, el, sizeof(el)) > 1){
            el[1] = el[0];
            lseek(file, 0, SEEK_SET);
            write(file, el, sizeof(el));
        }
    }
    close(file);
    return 0;
}
