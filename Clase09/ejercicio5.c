#include <stdio.h>

int main() {
    int arr[5] = {12, 2, 44, 13, 8}; 
    // variables fijas no arreglos usar &nom_var
    // variables fijas arreglos usar su nom_var directamente
    int *ptr = arr; // ptr apunta al inicio del arreglo

    // ptr points to the first element of arr, which is 1
    printf("Primer elemento: %d\n", *ptr);  // Output: First element: 1

    // Usando aritmética de punteros para moverse a la siguiente dirección
    ptr += 1; // Avanza a la sgte dirección
    printf("Segundo elemento: %d\n", *ptr);  // Output: Second element: 2

    return 0;
}
