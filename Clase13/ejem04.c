// Leer CSV
#include <stdio.h>
#include <string.h>

int main() {
    FILE *f = fopen("estudiantes.csv", "r");
    if (!f) return 1;

    char linea[200];
    fgets(linea, sizeof(linea), f);  // saltar cabecera

    while (fgets(linea, sizeof(linea), f)) {
        int id;
        char nombre[50];
        float calif;

        // sscanf con formato "%d,%[^,],%f" lee hasta coma o fin
        if (sscanf(linea, "%d,%49[^,],%f", &id, nombre, &calif) == 3) {
            printf("Leído: %d | %s | %.2f\n", id, nombre, calif);
        }
    }
    fclose(f);
    return 0;
}