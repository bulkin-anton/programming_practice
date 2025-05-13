#include "xabrt.h"
#include <stdlib.h>
#include <stdio.h>

void
xabrt(int e){
    if (e) {
        fprintf(stderr, "Failed function\n");
        abort();
    }
}
