#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int
main(int parc, char *args[]){
    FILE *fp, *my_file_num, *my_file_chr;
    int num;
    unsigned long long cnt = 0;
    char chr;
    if ((fp = fopen(args[1], "r+"))){
        my_file_num = fopen("help_chng_num.txt", "w+");
        my_file_chr = fopen("help_chng_char.txt", "w+");
        chr = fgetc(fp);
        while (!feof(fp)){
            if ((isdigit(chr)) || (chr == '-')){
                if (chr == '-'){
                    chr = fgetc(fp);
                    if (isdigit(chr)){
                        fseek(fp, ftell(fp) - 2, SEEK_SET);
                        fscanf(fp, "%d", &num);
                        fprintf(my_file_num, "%d\n", num);
                        fprintf(my_file_chr, "1");
                        cnt++;
                        printf("%d\n", num);
                    }
                    else{
                        fprintf(my_file_chr, "%c", '-');
                        fflush(my_file_chr);
                        continue;
                    }
                }
                else{
                    fseek(fp, ftell(fp) - 1, SEEK_SET);
                    fscanf(fp, "%d", &num);
                    fprintf(my_file_num, "%d\n", num);
                    fprintf(my_file_chr, "1");
                    cnt++;
                }
            }
            else{
                fprintf(my_file_chr, "%c", chr);
                fflush(my_file_chr);
            }
            chr = fgetc(fp);
        }
        fflush(my_file_num);
        fclose(my_file_num);
        fclose(my_file_chr);
        my_file_num = fopen("help_chng_num.txt", "r");
        my_file_chr = fopen("help_chng_char.txt", "r");
        fseek(fp, 0, SEEK_SET);
        while (cnt > 0){
            chr = fgetc(my_file_chr);
            while ((!feof(my_file_chr)) && (chr != '1')){
                fprintf(fp, "%c", chr);
                chr = fgetc(my_file_chr);
            }
            if (cnt != 0){
                printf("%llu\n", cnt);
                for (int i = 0; i < cnt; i++){
                    fscanf(my_file_num, "%d", &num);
                }
                fseek(my_file_num, 0, SEEK_SET);
                fprintf(fp, "%d", num);
            }
            cnt--;
        }
        fclose(my_file_num);
        fclose(my_file_chr);
        fflush(fp);
        remove("help_chng_char.txt");
        remove("help_chng_num.txt");
    }
    fclose(fp);
    return 0;
}
