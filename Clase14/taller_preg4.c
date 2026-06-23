#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Proceso {
    int id;
    char nombre[50];
    int tiempo;
    struct Proceso* siguiente;
} Proceso;

typedef struct {
    Proceso* frente;
    Proceso* final;
} Cola;

void encolar(Cola* cola, int id,
             const char* nombre, int tiempo) {

    Proceso* nuevo =
        (Proceso*)malloc(sizeof(Proceso));

    nuevo->id = id;
    strcpy(nuevo->nombre, nombre);
    nuevo->tiempo = tiempo;
    nuevo->siguiente = NULL;

    if (cola->final == NULL) {
        cola->frente = cola->final = nuevo;
        return;
    }

    cola->final->siguiente = nuevo;
    cola->final = nuevo;
}

void desencolar(Cola* cola) {
    if (cola->frente == NULL)
        return;

    Proceso* temp = cola->frente;

    cola->frente = cola->frente->siguiente;

    if (cola->frente == NULL)
        cola->final = NULL;

    free(temp);
}

Proceso* frente(Cola* cola) {
    return cola->frente;
}

int estaVacia(Cola* cola) {
    return cola->frente == NULL;
}

void simular(const char* archivo,
             int tiempoTotal) {

    FILE* f = fopen(archivo, "r");

    if (!f)
        return;

    Cola cola = {NULL, NULL};

    int id, tiempo;
    char nombre[50];

    while (fscanf(f, "%d,%49[^,],%d",
           &id, nombre, &tiempo) == 3)
        encolar(&cola, id, nombre, tiempo);

    fclose(f);

    for (int t = 0;
         t < tiempoTotal && !estaVacia(&cola);
         t++) {

        Proceso* p = frente(&cola);

        printf("Ejecutando %s (%d)\n",
               p->nombre, p->tiempo);

        p->tiempo--;

        if (p->tiempo <= 0) {
            printf("Proceso finalizado\n");
            desencolar(&cola);
        }
    }

    while (!estaVacia(&cola))
        desencolar(&cola);
}

int main() {
    simular("procesos.txt", 50);
    return 0;
}
