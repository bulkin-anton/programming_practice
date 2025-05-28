#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

void
proc(int num, FILE *fp){
    if (num == 1){
        while (1){
            int n1;
            fseek(fp, 0, SEEK_SET);
            if (fread(&n1 , sizeof(int), 1, fp) == 1){
                printf("%d\n", num);
                exit(0);
            }
        }
    }
    else if (num == 2){
        int n2 = 2;
        printf("%d\n", num);
        fwrite(&n2, sizeof(int), 1, fp);
        fflush(fp);
        exit(0);
    }
}

int
main(void){
    FILE *myfile;
    myfile = tmpfile();
    if (fork() == 0){
        proc(1, myfile);
    }
    if (fork() == 0){
        proc(2, myfile);
    }
    while(wait(NULL) != -1);
    fclose(myfile);
    return 0;
}
