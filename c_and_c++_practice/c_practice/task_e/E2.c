#include <stdio.h>

enum {MAX_SIZE = 100};

void
multiply_matrix(double res[MAX_SIZE][MAX_SIZE],
const double l_matr[MAX_SIZE][MAX_SIZE],
const double r_matr[MAX_SIZE][MAX_SIZE], 
unsigned n, unsigned m, unsigned q){
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
    static double mult_res[MAX_SIZE][MAX_SIZE],
    matr_1[MAX_SIZE][MAX_SIZE], matr_2[MAX_SIZE][MAX_SIZE];
    scanf("%u", &rows1);
    scanf("%u", &cols1);
    for (unsigned i = 0; i < rows1; i++){
        for (unsigned j = 0; j < cols1; j++){
            scanf("%lf", &matr_1[i][j]);
        }
    }
    scanf("%u", &rows2);
    scanf("%u", &cols2);
    for (unsigned i = 0; i < rows2; i++){
        for (unsigned j = 0; j < cols2; j++){
            scanf("%lf", &matr_2[i][j]);
        }
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
    return 0;
}
