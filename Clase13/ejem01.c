// Serialización y Deserialización
#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char nombre[50];
    float promedio;
} Alumno;

// Serializa un Alumno a una cadena con formato "id|nombre|promedio"
void serializar(Alumno *a, char *buffer, size_t tam) {
    snprintf(buffer, tam, "%d|%s|%.2f", a->id, a->nombre, a->promedio);
}

// Deserializa desde una cadena con ese formato
void deserializar(const char *buffer, Alumno *a) {
    sscanf(buffer, "%d|%s|%f", &a->id, a->nombre, &a->promedio);
}

int main() {
    Alumno a1 = {1, "Ana", 9.5};
    char buffer[100];

    serializar(&a1, buffer, sizeof(buffer));
    printf("Serializado: %s\n", buffer);  // "1|Ana|9.50"

    Alumno a2;
    deserializar(buffer, &a2);
    printf("Deserializado: %d, %s, %.2f\n", a2.id, a2.nombre, a2.promedio);
    return 0;
}