#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {STR_SIZE = 257};

int
main(int parc, char *parms[]){
    char *string_srch, string[STR_SIZE], chr;
    FILE *got_file, *help_file;
    unsigned long del_cntr, len, len_srch, len_str, str_pntr, found_str, cnt;
    if (parc >= 3){
        string_srch = parms[2];
        if (string_srch == NULL){
            return 0;
        }
        else{
            len_srch = strlen(string_srch);
            if ((got_file = fopen(parms[1], "r"))){
                help_file = tmpfile();
                while (fgets(string, STR_SIZE, got_file)){
                    len = strlen(string);
                    if (strchr(string, '\n')){
                        if ((len - 1) >= len_srch){
                            string[len - 1] = 0;
                            if (strstr(string, string_srch)){
                                string[len - 1] = '\n';
                                fwrite(string, sizeof(char), len, help_file);
                            }
                        }
                    }
                    else{
                        len_str = len;
                        str_pntr = ftell(help_file);
                        fwrite(string, sizeof(char), len, help_file);
                        while (fgets(string, STR_SIZE, got_file)){
                            len = strlen(string);
                            len_str += len;
                            if (strchr(string, '\n')){
                                fwrite(string, sizeof(char), len, help_file);
                                break;
                            }
                            else{
                                fwrite(string, sizeof(char), len, help_file);
                            }
                        }
                        fflush(help_file);
                        if (len_str <= len_srch){
                            fseek(help_file, str_pntr, SEEK_SET);
                        }
                        else{
                            found_str = 0;
                            for (unsigned long i = 0; (len_str - len_srch) >= i; i++){
                                fseek(help_file, str_pntr + i, SEEK_SET);
                                cnt = 0;
                                for (unsigned j = 0; j < len_srch; j++){
                                    fread(&chr, sizeof(char), 1, help_file);
                                    if (chr != string_srch[j]){
                                        break;
                                    }
                                    else{
                                        cnt++;
                                    }
                                }
                                if (cnt == len_srch){
                                    found_str = 1;
                                    break;
                                }
                            }
                            if (found_str){
                                str_pntr += len_str * sizeof(char);
                            }
                            fseek(help_file, str_pntr, SEEK_SET);
                        }
                    }
                }
                chr = '\0';
                str_pntr = ftell(help_file);
                fseek(help_file, 0, SEEK_END);
                del_cntr = ftell(help_file) - str_pntr;
                fseek(help_file, str_pntr, SEEK_SET);
                for (unsigned long i = 0; i < del_cntr; i++){
                    fwrite(&chr, sizeof(char), 1, help_file);
                }
                fclose(got_file);
                fflush(help_file);
                got_file = fopen(parms[1], "w");
                fseek(help_file, 0, SEEK_SET);
                while (fread(&chr, sizeof(char), 1, help_file)){
                    if (chr == 0){
                        break;
                    }
                    fprintf(got_file, "%c", chr);
                }
                fclose(help_file);
            }
            fclose(got_file);
        }
    }
    return 0;
}
