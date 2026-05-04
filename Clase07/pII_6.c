#include <stdio.h>

/* Prototipos de funciones */
int mcd(int a, int b);
int mcm(int a, int b);

/*
 * Función: mcd
 * ------------------------
 * Calcula el Máximo Común Divisor (MCD)
 * usando el algoritmo de Euclides de forma recursiva.
 *
 * Parámetros:
 *   a, b -> números enteros positivos
 *
 * Retorna:
 *   MCD de a y b
 */
int mcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return mcd(b, a % b);
}

/*
 * Función: mcm
 * ------------------------
 * Calcula el Mínimo Común Múltiplo (MCM)
 * usando la relación: MCM(a, b) = (a * b) / MCD(a, b)
 *
 * Parámetros:
 *   a, b -> números enteros positivos
 *
 * Retorna:
 *   MCM de a y b
 */
int mcm(int a, int b) {
    return (a * b) / mcd(a, b);
}

/*
 * Función principal
 * ------------------------
 * Lee dos enteros positivos desde stdin,
 * valida los datos y muestra el MCD y MCM.
 */
int main() {
    int num1, num2;

    /* Entrada de datos */
    printf("Ingrese el primer numero entero positivo: ");
    scanf("%d", &num1);

    printf("Ingrese el segundo numero entero positivo: ");
    scanf("%d", &num2);

    /* Validación básica */
    if (num1 <= 0 || num2 <= 0) {
        printf("Error: Ambos numeros deben ser enteros positivos.\n");
        return 1;
    }

    /* Cálculo y salida */
    printf("MCD(%d, %d) = %d\n", num1, num2, mcd(num1, num2));
    printf("MCM(%d, %d) = %d\n", num1, num2, mcm(num1, num2));

    return 0;
}