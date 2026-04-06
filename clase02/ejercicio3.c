#include <stdio.h>

int main()
{
    int a = 10, b = 18, x = -5;
    
    printf("a > b resulta %d\n", a > b);
    printf("a + 10 > b resulta %d\n", a + 10 > b);
    printf("a > b && b > 15 resulta %d\n", a > b && b > 15);
    printf("a > b || b > 15 resulta %d\n", a > b || b > 15);
    printf("!(a > b) && b > 15 resulta %d\n", !(a > b) && b > 15);
    const char *sign = (x>=0) ? "+" : "-";  // "+"
    printf("x = %d, tiene el signo %s\n",x,sign);
}