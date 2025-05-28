#include <stdio.h>

enum {GETVAL, SETVAL};


struct IdValue{
    int id, value;
};

union Argument{
    int int_par, *pntr_par;
};

static struct IdValue data[10000] = {};

int
command(int id, int cmd, union Argument oprtn){
    for (int i = 0; i < (sizeof(data) / sizeof(struct IdValue)); i++){
        if (data[i].id == id){
            switch(cmd){
                case SETVAL:
                    data[i].value = oprtn.int_par;
                    break;
                case GETVAL:
                    *oprtn.pntr_par = data[i].value;
                    break;
                default: return 2; break;
            }
            return 0;
        }
    }
    return 1;
}

int
main(void){
    int i, id, value, d, res, num;
    union Argument par;
    par.int_par = 0;
    par.pntr_par = &num;
    scanf("%d", &i);
    scanf("%d", &id);
    scanf("%d", &value);
    data[i].id = id;
    data[i].value = value;
    scanf("%d", &i);
    scanf("%d", &id);
    scanf("%d", &value);
    data[i].id = id;
    data[i].value = value;
    scanf("%d", &d);
    res = command(d, GETVAL, par);
    if (!res){
        par.int_par = *par.pntr_par + 1;
        command(d, SETVAL, par);
        printf("%d\n", par.int_par);
    }
    else{
        printf("NONE\n");
    }
    return 0;
}
