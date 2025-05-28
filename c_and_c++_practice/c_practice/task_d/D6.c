#include <stdio.h>
#include <string.h>

enum {STR_SIZE = 82};

const char*
my_strstr(const char* src, const char* srch){
    size_t len = strlen(srch), cnt;
    if (strlen(src) >= len){
        while (*(src + len - 1) != 0){
            cnt = 0;
            while ((cnt < len) &&
            (*(src + cnt) == *srch)){
                cnt++;
                srch++;
            }
            if (cnt == len){
                return src;
            }
            srch -= cnt;
            src++;
        }
    }
    else{
        return NULL;
    }
    return NULL;
}

int
main(void){
    char str_exmpl[STR_SIZE];
    const char *str_res, *str_chck;
    fgets(str_exmpl, STR_SIZE, stdin);
    if (strlen(str_exmpl)){
        str_exmpl[strlen(str_exmpl) - 1] = 0;
    }
    str_res = str_exmpl;
    str_chck = my_strstr(str_res, "end");
    while(str_chck != NULL){
        str_res = str_chck + strlen("end");
        str_chck = my_strstr(str_res, "end");
    }
    printf("%s", str_res);
    return 0;
}
