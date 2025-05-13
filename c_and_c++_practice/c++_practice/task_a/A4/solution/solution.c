#include <stdio.h>
#include "xabrt.h"
#include "vector.h"
#include "vector_iterator.h"
#include "vectors.h"

#define VECTOR(v) Vector v = {.nums = 0, .cap = 0, .sz = 0};

#define VECTORS(v) Vectors v = {.nums = 0, .cap = 0, .sz = 0};

int
main(void)
{
    VECTOR(v);
    int n;
    while (scanf("%d", &n) == 1) {
        push_back_v(&v, n);
    }
    VECTORS(w); {
        VectorIterator *i = begin_v(&v);
        VectorIterator *e = end_v(&v);
        while (! same(i, e)) {
            push_back_vs(&w, get(i));
            next(i);
        }
        remove_i(i);
        remove_i(e);
    }

    int m1;
    if (max_v(&v, &m1) == 0) {
        printf("%d\n", m1);
    } else {
        printf("empty\n");
    }

    int m2;
    if (max_vs(&w, &m2) == 0) {
        printf("%d\n", m2);
    } else {
        printf("empty\n");
    }

    remove_v(&v);
    remove_vs(&w);
}
