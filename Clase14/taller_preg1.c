#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
} Nodo;

void insertar(Nodo** cabeza, int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->dato = valor;
    nuevo->siguiente = NULL;

    if (*cabeza == NULL) {
        *cabeza = nuevo;
        return;
    }

    Nodo* temp = *cabeza;
    while (temp->siguiente != NULL)
        temp = temp->siguiente;

    temp->siguiente = nuevo;
}

void leerArchivo(const char* nombre, Nodo** cabeza) {
    FILE* archivo = fopen(nombre, "r");

    if (!archivo) {
        printf("No se pudo abrir %s\n", nombre);
        return;
    }

    int numero;

    while (fscanf(archivo, "%d", &numero) == 1)
        insertar(cabeza, numero);

    fclose(archivo);
}

void escribirArchivo(const char* nombre, Nodo* cabeza, int tipo) {
    FILE* archivo = fopen(nombre, "w");

    if (!archivo)
        return;

    while (cabeza != NULL) {
        if ((tipo == 0 && cabeza->dato % 2 == 0) ||
            (tipo == 1 && cabeza->dato % 2 != 0))
            fprintf(archivo, "%d\n", cabeza->dato);

        cabeza = cabeza->siguiente;
    }

    fclose(archivo);
}

void liberarLista(Nodo* cabeza) {
    Nodo* temp;

    while (cabeza != NULL) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp);
    }
}

int main() {
    Nodo* lista = NULL;

    leerArchivo("datos.txt", &lista);

    escribirArchivo("pares.txt", lista, 0);
    escribirArchivo("impares.txt", lista, 1);

    liberarLista(lista);

    return 0;
}
