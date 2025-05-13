#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "vector_iterator.h"

typedef struct {
    int *nums;
    int cap;
    int sz;
} Vector;

int max_v(Vector *s, int *m);

void push_back_v(Vector *v, int n);

VectorIterator* begin_v(Vector *v);

VectorIterator* end_v(Vector *v);

void remove_v(Vector *s);

#endif
