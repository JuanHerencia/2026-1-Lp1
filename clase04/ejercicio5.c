// Ejercicio 5
// Uso de goto
#include <stdio.h>
#include <stdbool.h>

int main() {
    int matriz[5][5];
    bool encontrado = false;
    int valor_buscar = 42;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matriz[i][j] = i * j;  // Relleno de ejemplo
            if (matriz[i][j] == valor_buscar) {
                printf("Encontrado en [%d][%d]\n", i, j);
                goto salir;
            }
        }
    }
    printf("No encontrado\n");
salir:
    return 0;
}
