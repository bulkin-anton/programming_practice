#include <stdio.h>

int
main(void){
    char buf[82];
    if (fgets(buf, 82, stdin) == NULL){
        printf("EMPTY INPUT\n");
    }
    else{
        printf("%s", buf);
    }
    return 0;
}
