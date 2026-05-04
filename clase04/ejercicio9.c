// Ejercicio 9
// Analizador sintático simple
#include <stdio.h>
#include <ctype.h>

int main() {
    char c;
    int palabras = 0, en_palabra = 0;

    printf("Ingrese texto (Ctrl+D para terminar):\n");

    do {
        c = getchar();
        if (c == EOF) break;

        if (isspace(c)) {
            if (en_palabra) {
                en_palabra = 0;
            }
            continue;  // Saltar a siguiente caracter
        }

        if (!en_palabra) {
            en_palabra = 1;
            palabras++;
        }
    } while (1);

    printf("Cantidad de palabras: %d\n", palabras);
    return 0;
}