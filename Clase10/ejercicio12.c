// Árbol Binario
#include <stdio.h>
#include <stdlib.h>

typedef struct ArbolNodo {
    int dato;
    struct ArbolNodo *izq;
    struct ArbolNodo *der;
} ArbolNodo;

ArbolNodo* crear_arbol_nodo(int valor) {
    ArbolNodo *nuevo = (ArbolNodo*)malloc(sizeof(ArbolNodo));
    nuevo->dato = valor;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

// Insertar en BST
ArbolNodo* insertar_bst(ArbolNodo *raiz, int valor) {
    if (raiz == NULL)
        return crear_arbol_nodo(valor);
    
    if (valor < raiz->dato)
        raiz->izq = insertar_bst(raiz->izq, valor);
    else if (valor > raiz->dato)
        raiz->der = insertar_bst(raiz->der, valor);
    
    return raiz;
}

// Recorridos
void inorder(ArbolNodo *raiz) {
    if (raiz == NULL) return;
    inorder(raiz->izq);
    printf("%d ", raiz->dato);
    inorder(raiz->der);
}

void preorder(ArbolNodo *raiz) {
    if (raiz == NULL) return;
    printf("%d ", raiz->dato);
    preorder(raiz->izq);
    preorder(raiz->der);
}

// Buscar
ArbolNodo* buscar(ArbolNodo *raiz, int valor) {
    if (raiz == NULL || raiz->dato == valor)
        return raiz;
    
    if (valor < raiz->dato)
        return buscar(raiz->izq, valor);
    return buscar(raiz->der, valor);
}