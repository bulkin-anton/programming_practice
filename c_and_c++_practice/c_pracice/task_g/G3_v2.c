#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int
main(int parc, char *args[]){
    FILE *fp, *my_file_chr;
    int num, *arr_num;
    unsigned long long cnt = 0, max_len = 1;
    char chr;
    arr_num = malloc(sizeof(int));
    if ((fp = fopen(args[1], "r+"))){
        my_file_chr = fopen("help_chng_char.txt", "w+");
        chr = fgetc(fp);
        while (!feof(fp)){
            if ((isdigit(chr)) || (chr == '-')){
                if (chr == '-'){
                    chr = fgetc(fp);
                    if (isdigit(chr)){
                        fseek(fp, ftell(fp) - 2, SEEK_SET);
                        fscanf(fp, "%d", &num);
                        if ((cnt + 1) < max_len){
                            arr_num[cnt] = num;
                        }
                        else{
                            max_len *= 2;
                            arr_num = realloc(arr_num, max_len*sizeof(int));
                            arr_num[cnt] = num;
                        }
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
                    if ((cnt + 1) < max_len){
                        arr_num[cnt] = num;
                    }
                    else{
                        max_len *= 2;
                        arr_num = realloc(arr_num, max_len*sizeof(int));
                        arr_num[cnt] = num;
                    }
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
        fclose(my_file_chr);
        my_file_chr = fopen("help_chng_char.txt", "r");
        fseek(fp, 0, SEEK_SET);
        while (cnt != 0){
            chr = fgetc(my_file_chr);
            while ((!feof(my_file_chr)) && (chr != '1')){
                fprintf(fp, "%c", chr);
                chr = fgetc(my_file_chr);
            }
            if (cnt != 0){
                num = arr_num[cnt - 1];
                fprintf(fp, "%d", num);
            }
            cnt--;
        }
        fclose(my_file_chr);
        fflush(fp);
        remove("help_chng_char.txt");
    }
    free(arr_num);
    fclose(fp);
    return 0;
}
