// Escribir CSV
#include <stdio.h>

typedef struct {
    int id;
    char nombre[50];
    float calif;
} Estudiante;

void escribir_csv(const char *archivo, Estudiante *lista, int n) {
    FILE *f = fopen(archivo, "w");
    if (!f) return;

    fprintf(f, "ID,Nombre,Calificacion\n");  // cabecera
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d,%s,%.2f\n", lista[i].id, lista[i].nombre, lista[i].calif);
    }
    fclose(f);
}

int main() {
    Estudiante alumnos[] = {
        {101, "Luis", 8.7},
        {102, "Marta", 9.2}
    };
    escribir_csv("estudiantes.csv", alumnos, 2);
    printf("CSV generado.\n");
    return 0;
}