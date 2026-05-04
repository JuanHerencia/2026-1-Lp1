#include <stdio.h>
#include <string.h>

/* Prototipos de funciones */
int es_palindromo(char str[], int inicio, int fin);
int palindromo_completo(char str[]);

/*
 * Función: es_palindromo
 * ----------------------------------
 * Determina recursivamente si la subcadena
 * str[inicio ... fin] es un palíndromo.
 *
 * Parámetros:
 *   str    -> cadena de caracteres
 *   inicio -> índice inicial
 *   fin    -> índice final
 *
 * Retorna:
 *   1 si es palíndromo, 0 en caso contrario
 */
int es_palindromo(char str[], int inicio, int fin) {
    /* Caso base: uno o ningún carácter */
    if (inicio >= fin) {
        return 1;
    }

    /* Si los caracteres no coinciden, no es palíndromo */
    if (str[inicio] != str[fin]) {
        return 0;
    }

    /* Llamada recursiva avanzando hacia el centro */
    return es_palindromo(str, inicio + 1, fin - 1);
}

/*
 * Función: palindromo_completo
 * ----------------------------------
 * Calcula si toda la cadena es palíndromo,
 * determinando los índices correctos.
 *
 * Parámetros:
 *   str -> cadena de caracteres
 *
 * Retorna:
 *   1 si es palíndromo, 0 en caso contrario
 */
int palindromo_completo(char str[]) {
    int longitud = strlen(str);

    if (longitud == 0) {
        return 1; /* Cadena vacía se considera palíndromo */
    }

    return es_palindromo(str, 0, longitud - 1);
}

/*
 * Función principal
 * ----------------------------------
 * Lee una palabra (máx 100 caracteres)
 * e indica si es palíndromo.
 */
int main(void) {
    char palabra[101];

    printf("Ingrese una palabra (max 100 caracteres, sin espacios): ");
    scanf("%100s", palabra);

    if (palindromo_completo(palabra)) {
        printf("Es palindromo\n");
    } else {
        printf("No es palindromo\n");
    }

    return 0;
}