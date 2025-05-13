#include <stdio.h>
#include <stdlib.h>

int
main(int parc, char *args[]){
    FILE *fp, *help_file;
    int num;
    unsigned long cnt = 0;
    if (parc >= 2){
        if ((fp = fopen(args[1], "r"))){
            help_file = tmpfile();
            while ((fscanf(fp, "%d", &num)) == 1){
                cnt++;
                fwrite(&num, sizeof(int), 1, help_file);
            }
            fclose(fp);
            fp = fopen(args[1], "w");
            fflush(help_file);
            fseek(help_file, 0, SEEK_SET);
            for (unsigned long i = cnt; i != 0; i--){
                fseek(help_file, (i - 1) * sizeof(int), SEEK_SET);
                fread(&num, sizeof(int), 1, help_file);
                fprintf(fp, "%d\n", num);
            }
            fflush(fp);
            fclose(help_file);
        }
        fclose(fp);
    }
    return 0;
}
