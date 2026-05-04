#include <stdio.h>

/* Prototipo de función */
int siguiente_valor(void);

/*
 * Función: siguiente_valor
 * ----------------------------------
 * Devuelve un valor incremental en cada llamada:
 * 1, 2, 3, 4, ...
 *
 * Utiliza una variable estática local para
 * conservar el estado entre llamadas.
 */
int siguiente_valor(void) {
    static int contador = 0;  // Se inicializa solo una vez
    contador++;
    return contador;
}

/*
 * Función principal
 * ----------------------------------
 * Llama a la función 7 veces e imprime
 * los resultados en una sola línea.
 */
int main(void) {
    int i;

    printf("Secuencia generada: ");

    for (i = 0; i < 7; i++) {
        printf("%d ", siguiente_valor());
    }

    printf("\n");

    return 0;
}