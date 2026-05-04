#include <stdio.h>
#include "stats.h"

#define TAM 5

/*
 * Función principal
 * ----------------------------------
 * Solicita 5 números al usuario,
 * calcula promedio y varianza,
 * e imprime los resultados.
 */
int main(void) {
    double datos[TAM];
    int i;

    /* Entrada de datos */
    printf("Ingrese %d numeros:\n", TAM);
    for (i = 0; i < TAM; i++) {
        printf("Numero %d: ", i + 1);
        scanf("%lf", &datos[i]);
    }

    /* Cálculos */
    double prom = promedio(datos, TAM);
    double var = varianza(datos, TAM);

    /* Salida */
    printf("\nPromedio: %.2f\n", prom);
    printf("Varianza: %.2f\n", var);

    return 0;
}