#include <stdio.h>

void cambiar(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int u = 5, v = 10;
    cambiar(u, v);
    printf("%d %d\n", u, v);
    return 0;
}
