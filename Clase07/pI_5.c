#include <stdio.h>

void imprimir_divisores(int n) {
    if (n <= 0) {
        printf("Número inválido\n");
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) printf("%d ", i);
    }
    printf("\n");
}

int main() {
    imprimir_divisores(-5);
    imprimir_divisores(6);
    return 0;
}
