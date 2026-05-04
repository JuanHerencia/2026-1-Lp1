#include <stdio.h>

/* Prototipos */
int fibonacci_recursivo(int n);
int fibonacci_iterativo(int n);

/*
 * Función: fibonacci_recursivo
 * ----------------------------------
 * Implementación recursiva ingenua:
 * F(n) = F(n-1) + F(n-2)
 *
 * Complejidad:
 *   Tiempo: O(2^n) (exponencial)
 *   Espacio: O(n) por la profundidad de la pila
 */
int fibonacci_recursivo(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
}

/*
 * Función: fibonacci_iterativo
 * ----------------------------------
 * Implementación iterativa eficiente.
 *
 * Complejidad:
 *   Tiempo: O(n)
 *   Espacio: O(1)
 */
int fibonacci_iterativo(int n) {
    if (n <= 1) {
        return n;
    }

    int anterior = 0;
    int actual = 1;
    int siguiente;
    int i;

    for (i = 2; i <= n; i++) {
        siguiente = anterior + actual;
        anterior = actual;
        actual = siguiente;
    }

    return actual;
}

/*
 * Función principal
 * ----------------------------------
 * Prueba ambas versiones y muestra resultados.
 * Incluye explicación conceptual sobre rendimiento
 * y consumo de pila.
 */
int main(void) {
    int n;

    printf("Ingrese un valor de n: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Error: n debe ser >= 0\n");
        return 1;
    }

    printf("\nFibonacci recursivo(%d) = %d\n", n, fibonacci_recursivo(n));
    printf("Fibonacci iterativo(%d) = %d\n", n, fibonacci_iterativo(n));

    /*
     * ============================================
     * EXPLICACIÓN TEÓRICA (IMPORTANTE)
     * ============================================
     *
     * 1. ¿Para n = 45 cuál versión es más rápida?
     *
     *    La versión ITERATIVA es muchísimo más rápida.
     *
     *    ¿Por qué?
     *    - La versión recursiva ingenua recalcula los mismos valores
     *      muchas veces (ej: F(40) se calcula repetidamente).
     *    - Su complejidad es exponencial: O(2^n).
     *
     *    En cambio:
     *    - La versión iterativa calcula cada valor UNA sola vez.
     *    - Complejidad lineal: O(n).
     *
     *    Para n = 45:
     *    - Recursiva: puede tardar varios segundos (o más).
     *    - Iterativa: prácticamente instantánea.
     *
     * --------------------------------------------
     *
     * 2. ¿Cuál puede causar desbordamiento de pila?
     *
     *    La versión RECURSIVA.
     *
     *    ¿Por qué?
     *    - Cada llamada recursiva ocupa espacio en la pila.
     *    - La profundidad de llamadas es aproximadamente n.
     *
     *    Entonces:
     *    - Para valores grandes de n (ej: miles o decenas de miles),
     *      se puede agotar la pila → STACK OVERFLOW.
     *
     *    La versión iterativa:
     *    - NO usa llamadas recursivas.
     *    - Usa memoria constante → NO desborda la pila.
     *
     * --------------------------------------------
     *
     * 3. Nota adicional:
     *
     *    Aunque la recursiva falla por tiempo mucho antes que por pila,
     *    ambas limitaciones existen:
     *
     *    - Tiempo (recursiva): falla primero (muy lenta).
     *    - Pila (recursiva): falla para n muy grandes.
     *
     * ============================================
     */

    return 0;
}