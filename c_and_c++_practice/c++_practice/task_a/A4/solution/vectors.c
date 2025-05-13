#include <stdlib.h>
#include "vector_iterator.h"
#include "vectors.h"
#include "xabrt.h"

static int Vector__remove(Vectors*);
static int Vector__begin(Vectors*, VectorIterator**);
static int Vector__end(Vectors*, VectorIterator**);
static int VectorS__push_back(Vectors*, int);


void
push_back_vs(Vectors *v, int n){
    xabrt(VectorS__push_back(v, n));
}

void
remove_vs(Vectors *s){
    xabrt(Vector__remove(s));
}

VectorIterator*
begin_vs(Vectors *v){
    VectorIterator *i;
    xabrt(Vector__begin(v, &i));
    return i;
}

VectorIterator*
end_vs(Vectors *v){
    VectorIterator *i;
    xabrt(Vector__end(v, &i));
    return i;
}

int
max_vs(Vectors *s, int *m)
{
    int ret = 1;
    VectorIterator *it = begin_vs(s);
    VectorIterator *e = end_vs(s);
    while (!same(it, e)) {
        if (ret) {
            ret = 0;
            *m = get(it);
        } else if (*m < get(it)) {
            *m = get(it);
        }
        next(it);
    }
    remove_i(it);
    remove_i(e);
    return ret;
}

static int
Vector__end(Vectors *v, VectorIterator **i) {
    if (v->sz == 0) {
        *i = new_vector_iterator(0);
    } else {
        *i = new_vector_iterator(v->nums + v->sz);
    }
    return 0;
}

static int
Vector__begin(Vectors *v, VectorIterator **i) {
    *i = new_vector_iterator(v->nums);
    return 0;
}

static int
Vector__remove(Vectors *v) {
    free(v->nums);
    return 0;
}

static int
VectorS__push_back(Vectors *v, int n) {
    if (v->cap == v->sz) {
        if (v->cap == 0) {
            v->cap = 100;
        } else {
            return 2;
        }
        void *t = realloc(v->nums, v->cap * sizeof *v->nums);
        if (!t) {
            return 1;
        }
        v->nums = t;
    }
    v->nums[v->sz++] = n;
    return 0;
}
