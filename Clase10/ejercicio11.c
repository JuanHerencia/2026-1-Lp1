// Cola (Queue) con lista enlazada
#include <stdio.h>
#include <stdlib.h>

typedef struct ColaNodo {
    int dato;
    struct ColaNodo *sig;
} ColaNodo;

typedef struct {
    ColaNodo *frente;
    ColaNodo *final;
    int tamanio;
} Cola;

void enqueue(Cola *c, int valor) {
    ColaNodo *nuevo = (ColaNodo*)malloc(sizeof(ColaNodo));
    nuevo->dato = valor;
    nuevo->sig = NULL;
    
    if (c->final == NULL) {
        c->frente = c->final = nuevo;
    } else {
        c->final->sig = nuevo;
        c->final = nuevo;
    }
    c->tamanio++;
}

int dequeue(Cola *c) {
    if (c->frente == NULL) return -1;
    
    ColaNodo *temp = c->frente;
    int valor = temp->dato;
    c->frente = c->frente->sig;
    
    if (c->frente == NULL)
        c->final = NULL;
    
    free(temp);
    c->tamanio--;
    return valor;
}