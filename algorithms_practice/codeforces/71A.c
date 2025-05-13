#include <stdio.h>
#include <string.h>

int
main(void){
    int n, len;
    char buf[102];
    scanf("%d\n", &n);
    for (int i = 0; i < n; i++){
        fgets(buf, sizeof(buf), stdin);
        if ((len = strlen(buf)) > 11){
                printf("%c%d%c\n", buf[0], len - 3, buf[len - 2]);
        } else printf("%s", buf);
    }
    return 0;
}
