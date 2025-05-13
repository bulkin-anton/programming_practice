#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {STR_SIZE = 257};

int
main(int parc, char *parms[]){
    char *string_srch, string[STR_SIZE], chr;
    FILE *got_file, *help_file;
    unsigned len_srch, len;
    if (parc >= 3){
        string_srch = parms[2];
        len_srch = strlen(string_srch);
        if ((got_file = fopen(parms[1], "r"))){
            help_file = tmpfile();
            while (fgets(string, STR_SIZE, got_file)){
                len = strlen(string);
                string[len - 1] = 0;
                if (((len - 1) >= len_srch)  && (strstr(string, string_srch))){
                    string[len - 1] = '\n';
                    fwrite(string, sizeof(char), len, help_file);
                }
            }
            fclose(got_file);
            got_file = fopen(parms[1], "w");
            fseek(help_file, 0, SEEK_SET);
            while (fread(&chr, sizeof(char), 1, help_file)){
                fprintf(got_file, "%c", chr);
            }
            fclose(help_file);
        }
        fclose(got_file);
    }
    return 0;
}
