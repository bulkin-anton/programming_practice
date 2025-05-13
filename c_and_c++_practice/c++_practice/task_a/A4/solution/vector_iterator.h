#ifndef __VECTOR_ITERATOR_H__
#define __VECTOR_ITERATOR_H__

typedef struct {
    int *ptr;
} VectorIterator;

VectorIterator* new_vector_iterator(int *v);

int same(VectorIterator *i, VectorIterator *j);

int get(VectorIterator *i);

void next(VectorIterator *i);

void remove_i(VectorIterator *s);

#endif
