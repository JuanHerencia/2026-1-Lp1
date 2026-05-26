/*
  Lectura: fscanf() vs fgets()
  Diferencia: fscanf() lee campos formateados pero deja \n en el buffer; fgets() lee líneas completas incluyendo espacios.
*/
#include <stdio.h>
#include <string.h>

// EJEMPLO 1: fscanf (útil para datos estructurados)
void leer_estructurado() {
    FILE *f = fopen("alumnos.txt", "r");
    if (!f) return;
    
    char nombre[50];
    int edad;
    float promedio;
    
    // Lee hasta encontrar espacios o saltos de línea
    while (fscanf(f, "%s %d %f", nombre, &edad, &promedio) == 3) {
        printf("Nombre: %s, Edad: %d, Prom: %.2f\n", nombre, edad, promedio);
    }
    
    fclose(f);
}

// EJEMPLO 2: fgets (útil para líneas completas)
void leer_lineas() {
    FILE *f = fopen("texto.txt", "r");
    if (!f) return;
    
    char linea[256];
    int num_linea = 1;
    
    while (fgets(linea, sizeof(linea), f) != NULL) {
        // fgets incluye el '\n' al final
        linea[strcspn(linea, "\n")] = '\0';  // Quitar el salto de línea
        printf("Línea %d: %s\n", num_linea++, linea);
    }
    
    fclose(f);
}

// EJEMPLO 3: Problema clásico (mezclar fscanf y fgets)
void problema_mezcla() {
    FILE *f = fopen("datos.txt", "w+");
    fprintf(f, "25\nJuan Perez\n");
    rewind(f);  // Volver al inicio
    
    int edad;
    char nombre[50];
    
    fscanf(f, "%d", &edad);  // Lee "25", deja '\n' en el buffer
    fgets(nombre, sizeof(nombre), f);  // ¡Lee el '\n' nada más!
    
    printf("Edad: %d\n", edad);
    printf("Nombre: '%s'\n", nombre);  // Será una cadena vacía
    
    // Solución: limpiar el buffer entre lecturas
    rewind(f);
    fscanf(f, "%d", &edad);
    fgetc(f);  // Consumir el '\n'
    fgets(nombre, sizeof(nombre), f);
    printf("Corregido - Nombre: '%s'\n", nombre);
    
    fclose(f);
}

int main()
{
    leer_estructurado();
    leer_lineas();
    problema_mezcla();
    return 0;
}