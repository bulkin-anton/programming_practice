#include <stdio.h>

int
main(int parc, char *parms[]){
    FILE *fp, *myfile;
    int cnt = 0, cnt_str = 0;
    char el;
    if (parc < 2){
        return 0;
    }
    if ((fp = fopen(parms[1], "r+"))){
        myfile = tmpfile();
        (el = fgetc(fp));
        while (!(feof(fp))){
            if (el == '\n'){
                cnt_str++;
            }
            (el = fgetc(fp));
        }
        fseek(fp, 0, SEEK_END);
        while (cnt != 2){
            fseek(fp, -sizeof(char), SEEK_CUR);
            (el = fgetc(fp));
            if (el == '\n'){
                cnt++;
            }
            fseek(fp, -sizeof(char), SEEK_CUR);
        }
        (el = fgetc(fp));
        (el = fgetc(fp));
        while (!(feof(fp))){
            fputc(el, myfile);
            (el = fgetc(fp));
        }
        fseek(fp, 0, SEEK_SET);
        while (cnt_str != 1){
            (el = fgetc(fp));
            if (el == '\n'){
                cnt_str--;
            }
            fputc(el, myfile);
        }
        fflush(myfile);
        fseek(myfile, 0, SEEK_SET);
        fseek(fp, 0, SEEK_SET);
        (el = fgetc(myfile));
        while (!(feof(myfile))){
            fputc(el, fp);
            (el = fgetc(myfile));
        }
        fclose(myfile);
        fflush(fp);
    }
    fclose(fp);
    return 0;
}
