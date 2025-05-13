#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isMatch(char* s, char* p) {
    if (s == NULL){
        return 0;
    }
    if (p == NULL){
        return 0;
    }
    int i = 0;
    int k = 0;
    while ((p[i] != 0) && (s[k] != 0)){
        switch(p[i]){
            case '.': i++; k++; break;
            case '*':
                if (i != 0){
                    if ((p[i - 1] != s[k]) && (p[i - 1] != '.')){
                        i++;
                    } else{
                        k++;
                    }
                } else{
                    return 0;
                }
                break;
            default: if (p[i] != s[k]){
                return 0;
            } else{
                i++;
                k++;
            }
        }
    }
    if (s[k] != 0){
        if ((p[i] == '*')){
            return 1;
        }
        else{
            return 0;
        }
    }
    if (p[i] != 0){
        return 0;
    }
    return 1;
}

int main(void)
{
    char s[] = "aa",
    p[] = ".*";
    int ans = isMatch(s, p);
    printf("%d\n", ans);
    return 0;
}
