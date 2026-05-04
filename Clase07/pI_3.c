#include <stdio.h>

int misterio(int n) {
    if (n <= 1) return 1;
    return misterio(n - 1) + misterio(n - 2);
}

int main() {
    printf("%d\n", misterio(5));
    return 0;
}
