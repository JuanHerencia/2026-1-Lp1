#include <stdio.h>
#include <string.h>

int main() {
    char s1[] = "Hola";  // Arreglo de 5 chars: 'H','o','l','a','\0'
    char *s2 = "Mundo";  // Puntero a literal (solo lectura)
    
    printf("Tamanio real s1 con \\0: %lu\n", sizeof(s1));     // 5
    printf("Longitud s1 sin \\0: %lu\n", strlen(s1));        // 4

    printf("Tamanio s2 real con \\0: %lu\n", sizeof(s2));     // 5
    printf("Longitud s2 in \\0: %lu\n", strlen(s2));        // 4

    //s2[0] = 'X'; // Modificación de la memoria
    //*s2 = 'X'; // un caracter es entre apóstrofes // tampoco

    // recorriendo cada caracter de *s2
    for(int i = 1; i <= sizeof(s2); i++) {
        printf("Caracter %d es %c\n", i, *s2);
        s2++;
    }
    
    // Cuidado: s2[0] = 'X'; // CRASH (segmentation fault)
    // Los literales son read-only, a diferencia de Python
    return 0;
}