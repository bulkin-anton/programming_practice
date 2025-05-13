#include <stdio.h>

int
main(void){
    int len1, len2;
    static double arr1[10000], arr2[10000];
    double *el1 = NULL, *el2 = NULL, el_chng;
    scanf("%d", &len1);
    for (int i = 0; i < len1; i++){
        scanf("%lf", &arr1[i]);
        if ((el1 == NULL) && (arr1[i] < 0)){
            el1 = &arr1[i];
        }
    }
    scanf("%d", &len2);
    for (int i = 0; i < len2; i++){
        scanf("%lf", &arr2[i]);
        if (arr2[i] > 0){
            el2 = &arr2[i];
        }
    }
    if (el1 && el2){
        el_chng = *el1;
        *el1 = *el2;
        *el2 = el_chng;
    }
    for (int i = 0; i < len1; i++){
        printf("%1lf ", arr1[i]);
    }
    printf("\n");
    for (int i = 0; i < len2; i++){
        printf("%1lf ", arr2[i]);
    }
    printf("\n");
    return 0;
}
