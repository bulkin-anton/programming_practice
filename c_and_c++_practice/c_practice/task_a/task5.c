#include <stdio.h>
#include <limits.h>

int
main(void)
{
  long int a1, a2, a3, a4, a5, a6, a7, a8, a9, a10;
  a1=10 / (-3) * 2;
  a2=10 % (-3) * 2;
  printf("%d %d\n", a1, a2);
  // -6 2 -2 -2 -2 -2 -3 -1 1 17 -2 -2147483647 INCORRECT -2 -2
  int x = 20; unsigned y = -3; a3=((x = y+++x) > 2);
  printf("%d %d %d\n", a3, x, y);
  //a4 = (-1)*INT_MAX;
  //a5 = (-1)*INT_MIN;
  a6 = INT_MAX << 1;
  a7 = UINT_MAX << 1;
  printf("%d %d %d %d\n", a4, a5, a6, a7);
  a8 = a6 >> 1;
  a9 = a7 >> 1;
  a9=1; a8=-2;
  a9= a8+++a8;
  printf("%d %d %d %d\n", a6, a8, a7, a9);
}
