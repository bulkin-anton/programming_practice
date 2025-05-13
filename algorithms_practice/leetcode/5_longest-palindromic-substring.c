#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
is_palindrom(char *str, int len){
    for (int i = 0; i < len / 2; i++){
        if (str[i] != str[len - i - 1]){
            return 0;
        }
    }
    return 1;
}

char* longestPalindrome(char* s) {
    if (s == NULL){
        return NULL;
    }
    char *ans = NULL;
    int ans_len = 0;
    int len = strlen(s);
    for (int i = 0; i < len; i++){
        for (int j = len - 1; j >= i; j--){
            if ((j - i + 1) > ans_len){
                if (is_palindrom(&s[i], j - i + 1)){
                    ans_len = j - i + 1;
                    free(ans);
                    ans = malloc(sizeof(char) * (ans_len + 1));
                    strncpy(ans, &s[i], ans_len);
                    ans[ans_len] = 0;
                }
            }
        }
    }
    return ans;
}

int main(void)
{
    char str[] = "a";
    char *ans = longestPalindrome(str);
    if (ans == NULL){
        return 0;
    }
    printf("%s\n", ans);
    free(ans);
    return 0;
}
