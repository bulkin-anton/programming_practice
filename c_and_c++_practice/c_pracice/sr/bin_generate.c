#include <stdio.h>

int
main(void){
    int a[] = {1};
    FILE *fp;
    fp = fopen("file.bin", "w");
    fwrite(&a, sizeof(int), sizeof(a)/sizeof(int), fp);
    fflush(fp);
    fclose(fp);
    return 0;
}
