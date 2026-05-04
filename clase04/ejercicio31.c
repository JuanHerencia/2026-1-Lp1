// Ejercicio 3.1
// Conceptos: Duración estática, visibilidad, extern
#include <stdio.h>

extern void incrementar();  // Función definida en otro archivo
extern int contador_local;  // para usarlo aquí
int main() {
    for (int i = 0; i < 3; i++)
        incrementar();
    // Usa la variable global del archivo ejercicio3.c
    printf("Finalmente contador_local queda en %d\n", contador_local);
    return 0;
}