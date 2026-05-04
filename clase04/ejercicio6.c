// Ejercicio 6
// Entradas con limpeza de buffer
#include <stdio.h>
#include <string.h>

int main() {
    char nombre[50];
    int edad;
    char buffer[100];

    printf("Nombre: ");
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = '\0';  // Quitar salto de línea

    printf("Edad: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &edad);

    printf("Nombre: %s, Edad: %d\n", nombre, edad);
    return 0;
}