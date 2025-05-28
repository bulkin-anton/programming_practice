#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int
main(void){
    pid_t pid;
    int first, el;
    setbuf(stdin, 0);
    first = getc(stdin);
    while ((el = getc(stdin)) != EOF){
        pid = fork();
        while (pid == -1){
            wait(NULL);
            pid = fork();
        }
        if (pid == 0){
            if (first == el){
                putc(el, stdout);
                putc(el, stdout);
            }
            exit(0);
        }
    }
    while (wait(NULL) != -1);
    printf("\n");
    return 0;
}
