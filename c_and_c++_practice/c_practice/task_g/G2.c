#include <stdio.h>
#include <stdlib.h>

int
main(int parc, char *args[]){
    char lit1;
    FILE *fp;
    if ((fp = fopen(args[1], "r+"))){
        lit1 = fgetc(fp);
        if (!feof(fp)){
            fgetc(fp);
            if (!(feof(fp))){
                fseek(fp, 1, SEEK_SET);
                fputc(lit1, fp);
                fflush(fp);
            }
        }
    }
    fclose(fp);
    return 0;
}
