#include <stdio.h>
#include <stdlib.h>

int
main(int parc, char *args[]){
    unsigned str_cnt = 1;
    char lit;
    FILE *fp;
    if ((fp = fopen(args[1], "r"))){
        lit = fgetc(fp);
        while(!(feof(fp))){
            if (!(str_cnt % 2)){
                printf("%c", lit);
            }
            if (lit == '\n'){
                str_cnt++;
            }
            lit = fgetc(fp);
        }
    }
    fclose(fp);
    return 0;
}
