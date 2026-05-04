#include <stdio.h>

void contador() {
    static int x = 0;
    int y = 0;
    x++;
    y++;
    printf("%d %d\n", x, y);
}

int main() {
    contador();
    contador();
    contador();
    return 0;
}
