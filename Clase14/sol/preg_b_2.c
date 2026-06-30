#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Definición de la página (dada en el enunciado)
typedef struct {
    char url[200];
    char titulo[100];
    int tiempoVisita; // en segundos
} PaginaWeb;

// Nodo genérico para las pilas dinámicas
typedef struct NodoPila {
    PaginaWeb pagina;
    struct NodoPila* siguiente;
} NodoPila;

// Estructura controladora de una Pila (LIFO)
typedef struct {
    NodoPila* tope;
} Pila;

// Estructura del Historial de Navegación
// Mantenemos la página actual separada de las pilas para mayor claridad lógica
typedef struct {
    Pila pilaBack;
    Pila pilaForward;
    PaginaWeb paginaActual;
    bool tienePaginaActiva; // Bandera para saber si hay una página en pantalla
} HistorialNavegacion;


// ---------------------------------------------------------
// Funciones Auxiliares de Pila (TDA Pila)
// ---------------------------------------------------------
void inicializarPila(Pila* p) {
    p->tope = NULL;
}

bool estaVacia(Pila* p) {
    return p->tope == NULL;
}

void push(Pila* p, PaginaWeb pagina) {
    NodoPila* nuevo = (NodoPila*)malloc(sizeof(NodoPila));
    if (nuevo == NULL) return;
    nuevo->pagina = pagina;
    nuevo->siguiente = p->tope;
    p->tope = nuevo; // El nuevo nodo es el nuevo tope
}

PaginaWeb pop(Pila* p) {
    PaginaWeb paginaVacia = {"", "", 0}; // Para retornos seguros si está vacía
    if (estaVacia(p)) return paginaVacia;

    NodoPila* nodoRemovido = p->tope;
    PaginaWeb paginaDevuelta = nodoRemovido->pagina;
    
    p->tope = p->tope->siguiente; // El tope retrocede
    free(nodoRemovido);           // Liberar memoria
    
    return paginaDevuelta;
}

void vaciarPila(Pila* p) {
    while (!estaVacia(p)) {
        pop(p); // pop ya incluye el free()
    }
}

// ---------------------------------------------------------
// Funciones de Navegación Web (Requeridas)
// ---------------------------------------------------------

void inicializarHistorial(HistorialNavegacion* historial) {
    inicializarPila(&historial->pilaBack);
    inicializarPila(&historial->pilaForward);
    historial->tienePaginaActiva = false;
}

void visitarPagina(HistorialNavegacion* historial, const char* url) {
    // 1. Si ya estamos viendo una página, pasa al historial 'Back'
    if (historial->tienePaginaActiva) {
        push(&historial->pilaBack, historial->paginaActual);
    }

    // 2. Al visitar una URL nueva manualmente, se borra el futuro ('Forward')
    vaciarPila(&historial->pilaForward);

    // 3. Cargamos la nueva página
    strcpy(historial->paginaActual.url, url);
    sprintf(historial->paginaActual.titulo, "Titulo de %s", url); // Título simulado
    historial->paginaActual.tiempoVisita = 0;
    historial->tienePaginaActiva = true;

    printf("Visitando: %s\n", url);
}

void paginaAnterior(HistorialNavegacion* historial) {
    if (estaVacia(&historial->pilaBack)) {
        printf("No hay paginas anteriores.\n");
        return;
    }

    // 1. La página actual se guarda en 'Forward' para poder recuperarla luego
    if (historial->tienePaginaActiva) {
        push(&historial->pilaForward, historial->paginaActual);
    }

    // 2. Extraemos el tope de 'Back' y lo hacemos la página actual
    historial->paginaActual = pop(&historial->pilaBack);
    printf("<- Back: Volviendo a %s\n", historial->paginaActual.url);
}

void paginaSiguiente(HistorialNavegacion* historial) {
    if (estaVacia(&historial->pilaForward)) {
        printf("No hay paginas siguientes.\n");
        return;
    }

    // 1. La página actual se guarda en 'Back'
    if (historial->tienePaginaActiva) {
        push(&historial->pilaBack, historial->paginaActual);
    }

    // 2. Extraemos el tope de 'Forward' y lo hacemos la página actual
    historial->paginaActual = pop(&historial->pilaForward);
    printf("-> Forward: Avanzando a %s\n", historial->paginaActual.url);
}

void mostrarHistorial(HistorialNavegacion* historial) {
    printf("\n=== Estado del Navegador ===\n");
    
    if (historial->tienePaginaActiva) {
        printf("Pagina Actual : %s\n", historial->paginaActual.url);
    } else {
        printf("Pagina Actual : [Ninguna]\n");
    }

    // Recorrido visual (sin desapilar) para PilaBack
    printf("Historial Back:\n");
    NodoPila* actual = historial->pilaBack.tope;
    while (actual != NULL) {
        printf("  - %s\n", actual->pagina.url);
        actual = actual->siguiente;
    }

    // Recorrido visual (sin desapilar) para PilaForward
    printf("Historial Forward:\n");
    actual = historial->pilaForward.tope;
    while (actual != NULL) {
        printf("  - %s\n", actual->pagina.url);
        actual = actual->siguiente;
    }
    printf("============================\n\n");
}

void guardarHistorial(HistorialNavegacion* historial, const char* archivo) {
    FILE* file = fopen(archivo, "w");
    if (file == NULL) {
        printf("Error abriendo archivo %s\n", archivo);
        return;
    }

    fprintf(file, "--- REGISTRO DE NAVEGACIÓN ---\n");
    if (historial->tienePaginaActiva) {
        fprintf(file, "ACTUAL: %s | %s\n", historial->paginaActual.titulo, historial->paginaActual.url);
    }

    fprintf(file, "\nPILABAck (Mas reciente a mas antiguo):\n");
    NodoPila* actual = historial->pilaBack.tope;
    while (actual != NULL) {
        fprintf(file, "%s | URL: %s\n", actual->pagina.titulo, actual->pagina.url);
        actual = actual->siguiente;
    }

    fclose(file);
    printf("Historial guardado en %s\n", archivo);
}