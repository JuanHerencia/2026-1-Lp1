/* Gestión dinámica de la memoria */
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Declare a pointer to a pointer. It will serve as our 2D array.
    int **arr;

    // Allocate memory for 3 pointers (3 rows).
    // Each of these pointers will point to an array (a row).
    arr = malloc(3 * sizeof(int *)); // malloc es reservar memoria
    if (arr == NULL) {
        return 1;  // falla la reserva de memoria 
    }

    // Por cada fila se reserva memoria
    for (int i = 0; i < 3; ++i) {
        // Reserva memoria para 2 enteros por cada fila.
        arr[i] = malloc(2 * sizeof(int));
        if (arr[i] == NULL) {
            return 1;  // Si falla se termina
        }

        // Initialize the elements. arr[i][j] = i * j;
        arr[i][0] = i + 1;
        arr[i][1] = (i+1) * 10;
    }

    // Accessing elements: arr[row][column]
    // Nested loop to iterate through the dynamically allocated 2D array
    printf("La matriz de 3 filas x 2 columnas generada es:\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            printf("%d ", arr[i][j]);  // Print each element
        }
        printf("\n");
    }

    /* Importante: liberar la memoria de cada arreglo */
    // Free each dynamically-allocated row
    for (int i = 0; i < 3; ++i) {
        free(arr[i]);
    }

    // Libera el acceso a todas las filas
    free(arr);

    printf("Se ha liberado la memoria correctamente\n");
    return 0;
}
