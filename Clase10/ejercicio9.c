// Lista enlazada simple

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo *sig;
} Nodo;

// Crear nuevo nodo
Nodo* crear_nodo(int valor) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo) return NULL;
    nuevo->dato = valor;
    nuevo->sig = NULL;
    return nuevo;
}

// Insertar al inicio
void insertar_inicio(Nodo **cabeza, int valor) {
    Nodo *nuevo = crear_nodo(valor);
    nuevo->sig = *cabeza;
    *cabeza = nuevo;
}

// Insertar al final
void insertar_final(Nodo **cabeza, int valor) {
    Nodo *nuevo = crear_nodo(valor);
    if (*cabeza == NULL) {
        *cabeza = nuevo;
        return;
    }
    
    Nodo *actual = *cabeza;
    while (actual->sig != NULL)
        actual = actual->sig;
    actual->sig = nuevo;
}

// Eliminar por valor
void eliminar(Nodo **cabeza, int valor) {
    Nodo *actual = *cabeza;
    Nodo *anterior = NULL;
    
    while (actual != NULL && actual->dato != valor) {
        anterior = actual;
        actual = actual->sig;
    }
    
    if (actual == NULL) return;  // No encontrado
    
    if (anterior == NULL) {
        // Eliminar el primer nodo
        *cabeza = actual->sig;
    } else {
        anterior->sig = actual->sig;
    }
    
    free(actual);
}

// Recorrer e imprimir
void imprimir(Nodo *cabeza) {
    printf("Lista: ");
    while (cabeza != NULL) {
        printf("%d -> ", cabeza->dato);
        cabeza = cabeza->sig;
    }
    printf("NULL\n");
}

// Liberar toda la lista
void liberar_lista(Nodo *cabeza) {
    while (cabeza != NULL) {
        Nodo *temp = cabeza;
        cabeza = cabeza->sig;
        free(temp);
    }
}

int main() {
    Nodo *lista = NULL;
    
    insertar_final(&lista, 10);
    insertar_final(&lista, 20);
    insertar_inicio(&lista, 5);
    insertar_final(&lista, 30);
    
    imprimir(lista);  // 5 -> 10 -> 20 -> 30 -> NULL
    
    eliminar(&lista, 20);
    imprimir(lista);  // 5 -> 10 -> 30 -> NULL
    
    liberar_lista(lista);
    return 0;
}