#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodoDoble {
    char nombre[100];
    struct NodoDoble* siguiente;
    struct NodoDoble* anterior;
} NodoDoble;

void insertarAlFinal(NodoDoble** cabeza, const char* nombre) {
    NodoDoble* nuevo = (NodoDoble*)malloc(sizeof(NodoDoble));

    strcpy(nuevo->nombre, nombre);
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;

    if (*cabeza == NULL) {
        *cabeza = nuevo;
        return;
    }

    NodoDoble* temp = *cabeza;

    while (temp->siguiente != NULL)
        temp = temp->siguiente;

    temp->siguiente = nuevo;
    nuevo->anterior = temp;
}

void ordenarBurbuja(NodoDoble** cabeza) {
    if (*cabeza == NULL)
        return;

    int intercambio;

    do {
        intercambio = 0;

        NodoDoble* actual = *cabeza;

        while (actual->siguiente != NULL) {

            if (strcmp(actual->nombre,
                       actual->siguiente->nombre) > 0) {

                char temp[100];

                strcpy(temp, actual->nombre);
                strcpy(actual->nombre,
                       actual->siguiente->nombre);
                strcpy(actual->siguiente->nombre,
                       temp);

                intercambio = 1;
            }

            actual = actual->siguiente;
        }

    } while (intercambio);
}

void guardarArchivo(NodoDoble* cabeza, const char* nombre) {
    FILE* archivo = fopen(nombre, "w");

    if (!archivo)
        return;

    while (cabeza != NULL) {
        fprintf(archivo, "%s\n", cabeza->nombre);
        cabeza = cabeza->siguiente;
    }

    fclose(archivo);
}

void liberarLista(NodoDoble* cabeza) {
    NodoDoble* temp;

    while (cabeza != NULL) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp);
    }
}

int main() {
    FILE* archivo = fopen("estudiantes.txt", "r");

    if (!archivo)
        return 1;

    NodoDoble* lista = NULL;
    char nombre[100];

    while (fgets(nombre, sizeof(nombre), archivo)) {
        nombre[strcspn(nombre, "\n")] = '\0';
        insertarAlFinal(&lista, nombre);
    }

    fclose(archivo);

    ordenarBurbuja(&lista);

    guardarArchivo(lista,
                   "estudiantes_ordenados.txt");

    liberarLista(lista);

    return 0;
}
