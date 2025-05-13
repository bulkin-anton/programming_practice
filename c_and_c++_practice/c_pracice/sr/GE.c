#include <stdio.h>

int
main(void){
    char el, arr[] = {0x53, 0x45, 0x43, 0x55, 0x52, 0x45};
    int i = 0;
    while (fread(&el, 1, 1, stdin) == 1){
        el = el ^ arr[i];
        i = (i + 1) & (sizeof(arr) / sizeof(char));
        fwrite(&el, 1, 1, stdout);
    }
    return 0;
}
