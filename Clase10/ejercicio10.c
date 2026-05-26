// Pila (Stack) con lista enlazada
#include <stdio.h>
#include <stdlib.h>


typedef struct PilaNodo {
    int dato;
    struct PilaNodo *abajo;
} PilaNodo;

typedef struct {
    PilaNodo *tope;
    int tamanio;
} Pila;

void push(Pila *p, int valor) {
    PilaNodo *nuevo = (PilaNodo*)malloc(sizeof(PilaNodo));
    nuevo->dato = valor;
    nuevo->abajo = p->tope;
    p->tope = nuevo;
    p->tamanio++;
}

int pop(Pila *p) {
    if (p->tope == NULL) {
        printf("Pila vacía\n");
        return -1;
    }
    PilaNodo *temp = p->tope;
    int valor = temp->dato;
    p->tope = temp->abajo;
    free(temp);
    p->tamanio--;
    return valor;
}

int peek(Pila *p) {
    return p->tope ? p->tope->dato : -1;
}