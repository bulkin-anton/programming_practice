#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {STR_SIZE = 7};

unsigned long
max(unsigned long a, unsigned long b){
    if (a > b){
        return a;
    }
    return b;
}

int
main(int parc, char *parms[]){
    char *string_srch, *string, *string_add, *string_src, chr, *string_null;
    FILE *got_file, *help_file;
    unsigned long len_srch, len_prev, len_nxt, found_str, pos_str, cnt;
    if (parc >= 3){
        string_srch = parms[2];
        if (string_srch == NULL){
            return 0;
        }
        len_srch = strlen(string_srch);
        string = (char *)calloc(max(STR_SIZE, len_srch), sizeof(char));
        string_add = (char *)calloc(max(STR_SIZE, len_srch), sizeof(char));
        string_src = (char *)calloc(2 * max(STR_SIZE, len_srch), sizeof(char));
        string_null = (char *)calloc(2 * max(STR_SIZE, len_srch), sizeof(char));
        if ((got_file = fopen(parms[1], "r"))){
            help_file = tmpfile();
            while (fgets(string, max(STR_SIZE, len_srch), got_file)){
                len_prev = strlen(string);
                if (strchr(string, '\n')){
                    string[len_prev - 1] = 0;
                    if (((len_prev - 1) >= len_srch)  &&
                    (strstr(string, string_srch))){
                        string[len_prev - 1] = '\n';
                        fwrite(string, sizeof(char), len_prev, help_file);
                    }
                }
                else{
                    found_str = 0;
                    pos_str = ftell(help_file);
                    strcpy(string_src, string);
                    while (fgets(string_add, max(STR_SIZE, len_srch), got_file)){
                        len_nxt = strlen(string_add);
                        if (!(found_str)){
                            if (strchr(string_add, '\n')){
                                string_add[len_nxt - 1] = 0;
                                strcpy((string_src + len_prev), string_add);
                                if (((len_prev + len_nxt) >= len_srch) &&
                                (strstr(string_src, string_srch))){
                                    found_str = 1;
                                    string_add[len_nxt - 1] = '\n';
                                    fwrite(string_src, sizeof(char),
                                    (len_prev + len_nxt), help_file);
                                }
                                else{
                                    break;
                                }
                            }
                            else{
                                strcpy((string_src + len_prev), string_add);
                                if (((len_prev + len_nxt) >= len_srch) &&
                                (strstr(string_src, string_srch))){
                                    found_str = 1;
                                    fwrite(string_src, sizeof(char),
                                    (len_prev + len_nxt), help_file);
                                }
                                else{
                                    fwrite(string, sizeof(char), len_prev, help_file);
                                    len_prev = len_nxt;
                                    strcpy(string_src, string_null);
                                    strcpy(string, string_null);
                                    strcpy(string_src, string_add);
                                    strcpy(string, string_add);
                                }
                            }
                        }
                        else{
                            fwrite(string_add, sizeof(char), len_nxt, help_file);
                            if (strchr(string_add, '\n')){
                                break;
                            }
                        }
                    }
                    if (!(found_str)){
                        fseek(help_file, pos_str, SEEK_SET);
                    }
                }
            }
            pos_str = ftell(help_file);
            fseek(help_file, 0, SEEK_END);
            cnt = ftell(help_file) - pos_str;
            fseek(help_file, pos_str, SEEK_SET);
            for (unsigned long i = 0; i < cnt; i++){
                fwrite(string_null, sizeof(char), 1, help_file);
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
        free(string);
        free(string_add);
        free(string_null);
        free(string_src);
        fclose(got_file);
    }
    return 0;
}
