#include <stdio.h>
#include <stdlib.h>
void
multiply_matrix(double **res, double **l_matr,
double **r_matr, unsigned n, unsigned m, unsigned q){
    for (unsigned i = 0; i < n; i++){
        for (unsigned j = 0; j < q; j++){
            res[i][j] = 0;
            for (unsigned k = 0; k < m; k++){
                res[i][j] += l_matr[i][k] * r_matr[k][j];
            }
        }
    }
}

int
main(void){
    unsigned rows1, cols1, rows2, cols2;
    double **mult_res, **matr_1, **matr_2;
    scanf("%u", &rows1);
    scanf("%u", &cols1);
    matr_1 = malloc(rows1 * sizeof(*matr_1));
    for (unsigned i = 0; i < rows1; i++){
        matr_1[i] = malloc(cols1 * sizeof(**matr_1));
        for (unsigned j = 0; j < cols1; j++){
            scanf("%lf", &matr_1[i][j]);
        }
    }
    scanf("%u", &rows2);
    scanf("%u", &cols2);
    matr_2 = malloc(rows2 * sizeof(*matr_2));
    for (unsigned i = 0; i < rows2; i++){
        matr_2[i] = malloc(cols2 * sizeof(**matr_2));
        for (unsigned j = 0; j < cols2; j++){
            scanf("%lf", &matr_2[i][j]);
        }
    }
    mult_res = malloc(rows1 * sizeof(*mult_res));
    for (unsigned i = 0; i < rows1; i++){
        mult_res[i] = malloc(cols2 * sizeof(**matr_2));
    }
    if (cols1 == rows2){
        multiply_matrix(mult_res, matr_1, matr_2, rows1, cols1, cols2);
        for (unsigned i = 0; i < rows1; i++){
            for(unsigned j = 0; j < cols2; j++){
                printf("%.1lf ", mult_res[i][j]);
            }
            printf("\n");
        }
    }
    for (unsigned i = 0; i < rows1; i++){
        free(mult_res[i]);
        free(matr_1[i]);
    }
    for (unsigned i = 0; i < rows2; i++){
        free(matr_2[i]);
    }
    free(matr_1);
    free(matr_2);
    free(mult_res);
    return 0;
}
