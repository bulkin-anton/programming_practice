#include <stdio.h>
#include <string.h>

int
main(int parc, char *parms[]){
    FILE *fp;
    char el, prev_el = 0;
    int prev_empty = 0;
    if (parc == 1){
        return 0;
    }
    if ((fp = fopen(parms[1], "r"))){
        while (fscanf(fp, "%c", &el) == 1){
            if (prev_empty){
                printf("%c", el);
            }
            if (el == '\n'){
                if ((prev_el == 0) || (prev_el == '\n')){
                    prev_empty = 1;
                }
                else{
                    prev_empty = 0;
                }
            }
            prev_el = el;
        }
    }
    fclose(fp);
    return 0;
}
