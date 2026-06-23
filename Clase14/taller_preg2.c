#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Nodo {
    char dato;
    struct Nodo* siguiente;
} Nodo;

typedef struct {
    Nodo* tope;
} Pila;

void push(Pila* pila, char valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));

    nuevo->dato = valor;
    nuevo->siguiente = pila->tope;
    pila->tope = nuevo;
}

char pop(Pila* pila) {
    if (pila->tope == NULL)
        return '\0';

    Nodo* temp = pila->tope;
    char valor = temp->dato;

    pila->tope = temp->siguiente;
    free(temp);

    return valor;
}

char peek(Pila* pila) {
    if (pila->tope == NULL)
        return '\0';

    return pila->tope->dato;
}

bool isEmpty(Pila* pila) {
    return pila->tope == NULL;
}

bool coincide(char apertura, char cierre) {
    return (apertura == '(' && cierre == ')') ||
           (apertura == '[' && cierre == ']') ||
           (apertura == '{' && cierre == '}');
}

bool balancear(const char* archivo) {
    FILE* f = fopen(archivo, "r");

    if (!f)
        return false;

    Pila pila;
    pila.tope = NULL;

    char c;

    while ((c = fgetc(f)) != EOF) {

        if (c == '(' || c == '[' || c == '{')
            push(&pila, c);

        if (c == ')' || c == ']' || c == '}') {

            if (isEmpty(&pila)) {
                fclose(f);
                return false;
            }

            char apertura = pop(&pila);

            if (!coincide(apertura, c)) {
                fclose(f);
                return false;
            }
        }
    }

    fclose(f);

    bool resultado = isEmpty(&pila);

    while (!isEmpty(&pila))
        pop(&pila);

    return resultado;
}

int main() {
    if (balancear("expresion.txt"))
        printf("Expresion balanceada\n");
    else
        printf("Expresion NO balanceada\n");

    return 0;
}
