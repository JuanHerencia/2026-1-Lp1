#include <stdio.h>

/* --- Prototipos de funciones --- */
int sumarDigitosRec(int n);
int raizDigital(int n);

/* --- Implementación de funciones recursivas --- */

/**
 * @brief Suma los dígitos de un número de forma puramente recursiva.
 * Sin el uso de bucles (while/for).
 */
int sumarDigitosRec(int n) {
    // Condición base: si el número se redujo a 0, la suma acumulada es 0.
    if (n == 0) {
        return 0;
    }
    // Paso recursivo: extraemos el último dígito (n % 10) y lo sumamos
    // a la llamada recursiva del número sin ese dígito (n / 10).
    return (n % 10) + sumarDigitosRec(n / 10);
}

/**
 * @brief Calcula la raíz digital de un número de forma recursiva.
 */
int raizDigital(int n) {
    // Condición base: si el número tiene un solo dígito (menor a 10), 
    // esa es su raíz digital.
    if (n < 10) {
        return n;
    }
    // Paso recursivo: si tiene 2 o más dígitos, calculamos la suma de 
    // sus dígitos usando nuestra función auxiliar, y a ese resultado 
    // le volvemos a aplicar la raíz digital.
    return raizDigital(sumarDigitosRec(n));
}

/* --- Programa Principal --- */
int main() {
    int numero;

    printf("--- CALCULADORA DE RAIZ DIGITAL ---\n\n");

    // Pregunta 4.2: Petición al usuario
    printf("Ingrese un numero entero positivo: ");
    scanf("%d", &numero);

    // Validación básica para asegurar que sea positivo
    if (numero < 0) {
        printf("Error: Por favor ingrese un numero positivo.\n");
        return 1; // Salida con código de error
    }

    // Cálculo y muestra de la raíz digital del número ingresado
    int raiz = raizDigital(numero);
    printf("La raiz digital de %d es: %d\n\n", numero, raiz);

    // Mostrar las raíces digitales del 1 al 100
    printf("Raices digitales de los numeros del 1 al 100:\n");
    for (int i = 1; i <= 100; i++) {
        // Imprimimos la coma para separar, excepto en el último elemento
        if (i < 100) {
            printf("%d, ", raizDigital(i));
        } else {
            printf("%d\n", raizDigital(i));
        }
    }

    return 0;
}