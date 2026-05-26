// Archivos
// Intro
#include <stdio.h>  // Todo lo de archivos está aquí

int main() {
    // FILE* es la "llave" para operar el archivo
    FILE *archivo = NULL;
    
    // Un FILE* tiene: posición actual, buffer, estado de error, fin-de-archivo
    printf("Tamaño de FILE: %lu bytes (depende del sistema)\n", sizeof(FILE));
    
    return 0;
}