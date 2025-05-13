#include <stdio.h>
#include <string.h>

enum{SIZE = 82};

int
main(int parc, char *parms[]){
    FILE *fd, *my_file;
    fd = fopen(parms[1], "r");
    my_file = tmpfile();
    char str[SIZE], buf[SIZE];
    fgets(str, SIZE, stdin);
    str[strlen(str) - 1] = 0;
    while(fgets(buf, SIZE, fd) != NULL){
        if (strstr(buf, str) != NULL){
            fputs(buf, my_file);
        }
    }
    fclose(fd);
    fd = fopen(parms[1], "w");
    fseek(my_file, 0, SEEK_SET);
    while(fgets(buf, SIZE, my_file) != NULL){
        fputs(buf, fd);
    }
    fclose(fd);
    return 0;
}
