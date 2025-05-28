#include <stdio.h>

double
*max_el(double *arr, unsigned len){
    double *res;
    res = arr;
    if (res != NULL){
        for (unsigned i = 0; i < len; i++, arr++){
            if (*arr > *res){
                res = arr;
            }
        }
    }
    return res;
}

void
switch_num(double *num1, double *num2){
    double el;
    el = *num2;
    *num2 = *num1;
    *num1 = el;
}

void
sort_arr(double *arr, unsigned len){
    double *num;
    for (unsigned i = 0; i < len; i++, arr++){
        num = max_el(arr, len - i);
        if (*num >= *arr){
            switch_num(num, arr);
        }
    }
}

int
main(void){
    unsigned len;
    scanf("%u", &len);
    static double arr[10000];
    for (unsigned i = 0; i < len; i++){
        scanf("%lf", &arr[i]);
    }
    if (len > 17){
        printf("%.1lf\n", *max_el(&arr[4], 14));
    }
    sort_arr(arr, len);
    for (unsigned i = 0; i < len; i++){
        printf("%.1lf ", arr[i]);
    }
    printf("\n");
}
