#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

enum {SIZE = 256};

int
main(void){
    char el, **argv, *str;
    pid_t pid;
    int status, exit_status = 0;
    int argc = 1, cnt = 0;
    while (scanf("%c", &el) == 1){
        argc = 1;
        argv = malloc(sizeof(*argv) * argc);
        cnt = 0;
        str = NULL;
        while ((el != '\n') && (el != ';')){
            if (el != ' '){
                if (str == NULL){
                    str = calloc(SIZE, sizeof(char));
                    str[cnt++] = el;
                } else{
                    str[cnt++] = el;
                    if (cnt % SIZE == 0){
                        str = realloc(str, sizeof(char) * 2 * cnt);
                    }
                }
            } else{
                if (str != NULL){
                    argv[argc - 1] = str;
                    argv = realloc(argv, sizeof(char *) *
                    (argc + 1));
                    argc++;
                    str = NULL;
                    cnt = 0;
                }
            }
            if (scanf("%c", &el) != 1){
                break;
            }
        }
        if (str != NULL){
            str[cnt] = 0;
            argv[argc - 1] = str;
            argv = realloc(argv, sizeof(char *) * (argc + 1));
            argc++;
            str = NULL;
            cnt = 0;
        }
        argv[argc - 1] = NULL;
        if ((pid = fork()) == 0){
            execvp(argv[0], argv);
            exit(127);
        } else if (pid == -1){
            for (int i = 0; i < (argc - 1); i++){
                free(argv[i]);
            }
            free(argv);
            exit(1);
        }
        wait(&status);
        if (WIFEXITED(status)){
            exit_status = WEXITSTATUS(status);
        } else{
            exit_status = 128 + WTERMSIG(status);
        }
        for (int i = 0; i < (argc - 1); i++){
            free(argv[i]);
        }
        free(argv);
    }
    return exit_status;
}
