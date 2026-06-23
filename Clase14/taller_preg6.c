#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nombre[100];
    float precio;
} Producto;

typedef struct NodoLista {
    Producto producto;
    struct NodoLista* siguiente;
} NodoLista;

typedef struct NodoArbol {
    Producto producto;
    struct NodoArbol* izquierdo;
    struct NodoArbol* derecho;
} NodoArbol;

void insertarLista(
    NodoLista** cabeza,
    Producto p) {

    NodoLista* nuevo =
        (NodoLista*)malloc(sizeof(NodoLista));

    nuevo->producto = p;
    nuevo->siguiente = *cabeza;
    *cabeza = nuevo;
}

void insertarArbol(
    NodoArbol** raiz,
    Producto p) {

    if (*raiz == NULL) {

        *raiz =
        (NodoArbol*)malloc(sizeof(NodoArbol));

        (*raiz)->producto = p;
        (*raiz)->izquierdo = NULL;
        (*raiz)->derecho = NULL;

        return;
    }

    if (p.id < (*raiz)->producto.id)
        insertarArbol(
            &((*raiz)->izquierdo),
            p
        );
    else
        insertarArbol(
            &((*raiz)->derecho),
            p
        );
}

Producto* buscarProducto(
    NodoArbol* raiz,
    int id) {

    if (raiz == NULL)
        return NULL;

    if (id == raiz->producto.id)
        return &(raiz->producto);

    if (id < raiz->producto.id)
        return buscarProducto(
            raiz->izquierdo, id);

    return buscarProducto(
        raiz->derecho, id);
}

void guardarOrdenado(
    NodoArbol* raiz,
    FILE* archivo) {

    if (raiz == NULL)
        return;

    guardarOrdenado(
        raiz->izquierdo,
        archivo
    );

    fprintf(archivo,
            "%d,%s,%.2f\n",
            raiz->producto.id,
            raiz->producto.nombre,
            raiz->producto.precio);

    guardarOrdenado(
        raiz->derecho,
        archivo
    );
}

void mostrarOrdenado(
    NodoArbol* raiz) {

    if (raiz == NULL)
        return;

    mostrarOrdenado(
        raiz->izquierdo);

    printf("%d %s %.2f\n",
           raiz->producto.id,
           raiz->producto.nombre,
           raiz->producto.precio);

    mostrarOrdenado(
        raiz->derecho);
}

void liberarLista(NodoLista* cabeza) {
    NodoLista* temp;

    while (cabeza) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp);
    }
}

void liberarArbol(NodoArbol* raiz) {

    if (raiz == NULL)
        return;

    liberarArbol(raiz->izquierdo);
    liberarArbol(raiz->derecho);

    free(raiz);
}

int main() {

    FILE* archivo =
        fopen("catalogo.txt", "r");

    if (!archivo)
        return 1;

    NodoLista* lista = NULL;
    NodoArbol* arbol = NULL;

    Producto p;

    while (fscanf(archivo,
                  "%d,%99[^,],%f",
                  &p.id,
                  p.nombre,
                  &p.precio) == 3) {

        insertarLista(&lista, p);
        insertarArbol(&arbol, p);
    }

    fclose(archivo);

    int id;

    printf("ID a buscar: ");
    scanf("%d", &id);

    Producto* encontrado =
        buscarProducto(arbol, id);

    if (encontrado)
        printf("%d %s %.2f\n",
               encontrado->id,
               encontrado->nombre,
               encontrado->precio);
    else
        printf("No encontrado\n");

    printf("\nCatalogo ordenado:\n");
    mostrarOrdenado(arbol);

    FILE* salida =
        fopen("catalogo_ordenado.txt",
              "w");

    guardarOrdenado(arbol, salida);

    fclose(salida);

    liberarLista(lista);
    liberarArbol(arbol);

    return 0;
}
