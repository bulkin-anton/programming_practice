#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[]){
    char *pntr, end_arr[4] = "end";
    for (int i = 1; i < argc; i++){
        printf("%s\n", argv[i]);
    }
    for (int i = 1; i < argc; i++){
        pntr = strstr(argv[i], end_arr);
        if ((pntr) && (strlen(pntr) > 2)){
            pntr += 3;
            pntr = strstr(pntr, end_arr);
            if ((pntr) && (strlen(pntr) > 3)){
                printf("%s\n", (pntr + 3));
            }
        }
    }
    return 0;
}
