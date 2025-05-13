#include <stdio.h>

struct IntNumber{
    short svalue;
    int ivalue;
    long lvalue;
    int type;
};

struct IntNumber
bconj(struct IntNumber a, struct IntNumber b){
    if ((a.type < 2) && (b.type < 2)){
        if (a.type == 0){
            a.ivalue = (int)a.svalue;
        }
        if (b.type == 0){
            a.ivalue &= (int)b.svalue;
        }
        else{
            a.ivalue &= b.ivalue;
        }
        a.type = 1;
    }
    else{
        a.type = 2;
        switch(a.type){
            case 0: a.lvalue = (long)a.svalue; break;
            case 1: a.lvalue = (long)a.ivalue; break;
            default: break;
        }
        switch (b.type){
            case 0: a.lvalue &= (long)b.svalue; break;
            case 1: a.lvalue &= (long)b.ivalue; break;
            default: a.lvalue &= (long)b.lvalue; break;
        }
    }
    return a;
}

int
main(void){
    ///your checks
    return 0;
}
