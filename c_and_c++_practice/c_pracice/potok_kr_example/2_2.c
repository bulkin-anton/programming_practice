#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(void){
    unsigned n, i = 1;
    scanf("%u", &n);
    printf("%u", i);
    fflush(stdout);
    if (n != 1){
        printf(" ");
        fflush(stdout);
    }
    while (i < n){
        i++;
        if (fork() == 0){
            printf("%u", i);
            fflush(stdout);
            if (i < n){
                printf(" ");
                fflush(stdout);
            }
            return 0;
        }
        wait(NULL);
    }
    printf("\n");
    return 0;
}
