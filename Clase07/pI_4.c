// compilar los archivos
//   matematicas.h
//   matematicas.c
//   main.c
// gcc p04.c matematica.c -o p04.exe
#include <stdio.h>
#include "matematica.h"

int main() {
    
    printf("El cuadrado de 2 es %d\n", cuadrado(2));
    printf("El cuadrado de 3 es %d\n", cubo(3));
    return 0;
}
