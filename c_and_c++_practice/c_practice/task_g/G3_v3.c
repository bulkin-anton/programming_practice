#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int
main(int parc, char *args[]){
    FILE *fp;
    int num, *arr_num;
    unsigned long long cnt = 0, max_len = 1;
    arr_num = malloc(sizeof(int));
    if (parc >= 2){
        if ((fp = fopen(args[1], "r"))){
            while ((fscanf(fp, "%d", &num)) == 1){
                if ((cnt + 1) < max_len){
                    arr_num[cnt] = num;
                }
                else{
                    max_len *= 2;
                    arr_num = realloc(arr_num, max_len*sizeof(int));
                    if (arr_num == NULL){
                        break;
                    }
                    arr_num[cnt] = num;
                }
                cnt++;
            }
            fclose(fp);
            fp = fopen(args[1], "w+");
            while (cnt != 0){
                num = arr_num[cnt - 1];
                fprintf(fp, "%d\n", num);
                fflush(fp);
                cnt--;
            }
            fflush(fp);
        }
        fclose(fp);
    }
    free(arr_num);
    return 0;
}
