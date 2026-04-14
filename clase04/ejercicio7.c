// Ejercicio 7
// Uso de aserciones
#include <stdio.h>
#include <assert.h>

int busqueda_binaria(int arr[], int izq, int der, int target) {
    assert(izq <= der);  // Invariante de entrada
    if (izq > der) return -1;

    int medio = izq + (der - izq) / 2;
    if (arr[medio] == target)
        return medio;
    else if (arr[medio] > target)
        return busqueda_binaria(arr, izq, medio - 1, target);
    else
        return busqueda_binaria(arr, medio + 1, der, target);
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int idx = busqueda_binaria(arr, 0, 5, 7);
    printf("Índice de 7: %d\n", idx);
    return 0;
}