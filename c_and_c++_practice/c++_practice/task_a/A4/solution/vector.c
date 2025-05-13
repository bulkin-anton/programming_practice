#include <stdlib.h>
#include "vector.h"
#include "vector_iterator.h"
#include "xabrt.h"

static int Vector__remove(Vector*);
static int Vector__begin(Vector*, VectorIterator**);
static int Vector__end(Vector*, VectorIterator**);
static int Vector__push_back(Vector*, int);


void
push_back_v(Vector *v, int n){
    xabrt(Vector__push_back(v, n));
}

VectorIterator*
begin_v(Vector *v){
    VectorIterator *i;
    xabrt(Vector__begin(v, &i));
    return i;
}

VectorIterator*
end_v(Vector *v){
    VectorIterator *i;
    xabrt(Vector__end(v, &i));
    return i;
}

void
remove_v(Vector *s){
    xabrt(Vector__remove(s));
}

int
max_v(Vector *s, int *m)
{
    int ret = 1;
    VectorIterator *it = begin_v(s);
    VectorIterator *e = end_v(s);
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
Vector__remove(Vector *v) {
    free(v->nums);
    return 0;
}

static int
Vector__push_back(Vector *v, int n) {
    if (v->cap == v->sz) {
        if (v->cap == 0) {
            v->cap = 100;
        } else {
            v->cap = 2 * v->cap;
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

static int
Vector__begin(Vector *v, VectorIterator **i) {
    *i = new_vector_iterator(v->nums);
    return 0;
}

static int
Vector__end(Vector *v, VectorIterator **i) {
    if (v->sz == 0) {
        *i = new_vector_iterator(0);
    } else {
        *i = new_vector_iterator(v->nums + v->sz);
    }
    return 0;
}
