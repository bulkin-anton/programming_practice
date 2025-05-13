#ifndef __VECTORS_H__
#define __VECTORS_H__

#include "vector_iterator.h"

typedef struct {
    int *nums;
    int cap;
    int sz;
} Vectors;

int max_vs(Vectors *s, int *m);

void push_back_vs(Vectors *v, int n);

VectorIterator* begin_vs(Vectors *v);

VectorIterator* end_vs(Vectors *v);

void remove_vs(Vectors *s);

#endif
