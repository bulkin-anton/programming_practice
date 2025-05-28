#include <stdio.h>

int
main(int parc, char *parms[]){
    FILE *fp;
    int src_num, num, zero_cnt = 0;
    if (parc < 2){
        return 0;
    }
    if (!(fp = fopen(parms[1], "r+"))){
        fclose(fp);
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) < sizeof(int) * 2){
        fclose(fp);
        return 0;
    }
    fseek(fp, -2 * sizeof(int), SEEK_END);
    fread(&src_num, sizeof(int), 1, fp);
    fseek(fp, 0, SEEK_SET);
    while ((fread(&num, sizeof(int), 1, fp)) == 1){
        if (num == 0){
            zero_cnt++;
        }
        if (zero_cnt == 2){
            break;
        }
    }
    if (zero_cnt == 2){
        fseek(fp, ftell(fp) - sizeof(int), SEEK_SET);
        fwrite(&src_num, sizeof(int), 1, fp);
        fflush(fp);
    }
    fclose(fp);
    return 0;
}
