#include <stdio.h>
#include <stdlib.h>

typedef struct NodoArbol {
    int valor;
    struct NodoArbol* izquierdo;
    struct NodoArbol* derecho;
} NodoArbol;

void insertar(NodoArbol** raiz, int valor) {

    if (*raiz == NULL) {

        *raiz =
        (NodoArbol*)malloc(sizeof(NodoArbol));

        (*raiz)->valor = valor;
        (*raiz)->izquierdo = NULL;
        (*raiz)->derecho = NULL;

        return;
    }

    if (valor < (*raiz)->valor)
        insertar(&((*raiz)->izquierdo), valor);
    else
        insertar(&((*raiz)->derecho), valor);
}

int buscarNivel(NodoArbol* raiz,
                int valor,
                int nivel) {

    if (raiz == NULL)
        return -1;

    if (raiz->valor == valor)
        return nivel;

    if (valor < raiz->valor)
        return buscarNivel(
            raiz->izquierdo,
            valor,
            nivel + 1
        );

    return buscarNivel(
        raiz->derecho,
        valor,
        nivel + 1
    );
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
        fopen("numeros_arbol.txt", "r");

    if (!archivo)
        return 1;

    NodoArbol* raiz = NULL;

    int numero;

    while (fscanf(archivo, "%d", &numero) == 1)
        insertar(&raiz, numero);

    fclose(archivo);

    int buscar;

    printf("Numero a buscar: ");
    scanf("%d", &buscar);

    printf("Nivel: %d\n",
           buscarNivel(raiz,
                       buscar,
                       0));

    liberarArbol(raiz);

    return 0;
}
