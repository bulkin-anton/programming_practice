#include <stdlib.h>
#include "vector_iterator.h"
#include "xabrt.h"

static int
VectorIterator__next(VectorIterator *i) {
    ++i->ptr;
    return 0;
}

static int
VectorIterator__get(VectorIterator *i, int *v) {
    *v = *i->ptr;
    return 0;
}

static int
VectorIterator__remove(VectorIterator *i) {
    free(i);
    return 0;
}

static int
VectorIterator__same(VectorIterator *i, VectorIterator *j, int *r) {
    *r = (i->ptr == j->ptr);
    return 0;
}

VectorIterator*
new_vector_iterator(int *v){
    VectorIterator *it = malloc(sizeof *it);
    it->ptr = (v);
    return it;
}

int
same(VectorIterator *i, VectorIterator *j){
    int r;
    xabrt(VectorIterator__same(i, j, &r));
    return r;
}

int
get(VectorIterator *i){
    int r;
    xabrt(VectorIterator__get(i, &r));
    return r;
}

void
next(VectorIterator *i){
    xabrt(VectorIterator__next(i));
}

void
remove_i(VectorIterator *s){
    xabrt(VectorIterator__remove(s));
}
