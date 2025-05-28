#include <stdio.h>
#include <limits.h>

int
main(void)
{
    printf("-6\n2\nUB\nUB\n-3 -1\n");
    printf("1 17 -2\n%d\nUB\n%d\n%dn", (-1)*INT_MAX, INT_MAX << 1,  
    UINT_MAX << 1);
    ///int x=20; unsigned y = -3;
    ///printf("%d %d %d\n", (x=y+++x)>2, x, y);
}
