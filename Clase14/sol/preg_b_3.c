#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de Estados
typedef enum {
    PENDIENTE,
    EN_PROGRESO,
    COMPLETADA,
    BLOQUEADA
} EstadoTarea;

// Estructura proporcionada
typedef struct {
    int id;
    char titulo[100];
    char descripcion[200];
    EstadoTarea estado;
    int prioridad; // 1-5 (Asumiremos que 5 es la más alta)
    char fechaLimite[11]; // DD/MM/AAAA
} Tarea;

// Nodo para Lista Doblemente Enlazada
typedef struct NodoTarea {
    Tarea tarea;
    struct NodoTarea* sig;
    struct NodoTarea* ant;
} NodoTarea;

// Estructura controladora de la Lista
typedef struct {
    NodoTarea* cabeza;
    NodoTarea* cola; // Facilita la inserción al final
    int tamano;      // Facilita la validación de posiciones
} ListaTareas;


// ---------------------------------------------------------
// Inicialización
// ---------------------------------------------------------
void inicializarLista(ListaTareas* lista) {
    lista->cabeza = NULL;
    lista->cola = NULL;
    lista->tamano = 0;
}

// ---------------------------------------------------------
// Insertar Tarea en Posición Específica
// ---------------------------------------------------------
void insertarTarea(ListaTareas* lista, Tarea tarea, int posicion) {
    NodoTarea* nuevo = (NodoTarea*)malloc(sizeof(NodoTarea));
    if (nuevo == NULL) return;
    nuevo->tarea = tarea;
    nuevo->sig = NULL;
    nuevo->ant = NULL;

    // Caso 1: Lista vacía
    if (lista->cabeza == NULL) {
        lista->cabeza = nuevo;
        lista->cola = nuevo;
    } 
    // Caso 2: Insertar al inicio (posicion <= 0)
    else if (posicion <= 0) {
        nuevo->sig = lista->cabeza;
        lista->cabeza->ant = nuevo;
        lista->cabeza = nuevo;
    } 
    // Caso 3: Insertar al final (posicion >= tamano)
    else if (posicion >= lista->tamano) {
        nuevo->ant = lista->cola;
        lista->cola->sig = nuevo;
        lista->cola = nuevo;
    } 
    // Caso 4: Insertar en el medio
    else {
        NodoTarea* actual = lista->cabeza;
        for (int i = 0; i < posicion; i++) {
            actual = actual->sig;
        }
        // Conectar el nuevo nodo
        nuevo->sig = actual;
        nuevo->ant = actual->ant;
        
        // Actualizar los nodos adyacentes
        actual->ant->sig = nuevo;
        actual->ant = nuevo;
    }
    lista->tamano++;
}

// ---------------------------------------------------------
// Mover Tarea (Desenlazar y Re-insertar)
// ---------------------------------------------------------
void moverTarea(ListaTareas* lista, int id, int nuevaPosicion) {
    if (lista->cabeza == NULL) return;

    // 1. Buscar el nodo a mover
    NodoTarea* actual = lista->cabeza;
    while (actual != NULL && actual->tarea.id != id) {
        actual = actual->sig;
    }

    if (actual == NULL) {
        printf("Tarea con ID %d no encontrada.\n", id);
        return; 
    }

    // 2. Desenlazar el nodo de su posición actual
    if (actual->ant != NULL) {
        actual->ant->sig = actual->sig;
    } else {
        lista->cabeza = actual->sig; // Era la cabeza
    }

    if (actual->sig != NULL) {
        actual->sig->ant = actual->ant;
    } else {
        lista->cola = actual->ant; // Era la cola
    }
    
    lista->tamano--; // Reducimos temporalmente para usar insertarTarea

    // 3. Re-insertar usando la función ya creada (reutilización de código)
    // Extraemos la tarea y liberamos el nodo viejo para insertarlo de forma limpia.
    // (Otra opción es hacer el enlazado manual del mismo nodo, pero esto es más seguro para estudiantes).
    Tarea tareaMovida = actual->tarea;
    free(actual);
    
    insertarTarea(lista, tareaMovida, nuevaPosicion);
    printf("Tarea %d movida exitosamente.\n", id);
}

// ---------------------------------------------------------
// Cambiar Estado
// ---------------------------------------------------------
void cambiarEstado(ListaTareas* lista, int id, EstadoTarea nuevoEstado) {
    NodoTarea* actual = lista->cabeza;
    while (actual != NULL) {
        if (actual->tarea.id == id) {
            actual->tarea.estado = nuevoEstado;
            printf("Estado de la tarea %d actualizado.\n", id);
            return;
        }
        actual = actual->sig;
    }
    printf("Tarea con ID %d no encontrada.\n", id);
}

// ---------------------------------------------------------
// Filtrar por Estado
// ---------------------------------------------------------
void filtrarPorEstado(ListaTareas* lista, EstadoTarea estado) {
    const char* nombresEstados[] = {"PENDIENTE", "EN PROGRESO", "COMPLETADA", "BLOQUEADA"};
    printf("\n--- Tareas en estado: %s ---\n", nombresEstados[estado]);
    
    NodoTarea* actual = lista->cabeza;
    int encontradas = 0;
    while (actual != NULL) {
        if (actual->tarea.estado == estado) {
            printf("[%d] %s (Prioridad: %d) - Limite: %s\n", 
                   actual->tarea.id, actual->tarea.titulo, 
                   actual->tarea.prioridad, actual->tarea.fechaLimite);
            encontradas++;
        }
        actual = actual->sig;
    }
    if (encontradas == 0) printf("No se encontraron tareas en este estado.\n");
}

// ---------------------------------------------------------
// Ordenar por Prioridad (Burbuja intercambiando datos)
// ---------------------------------------------------------
void ordenarPorPrioridad(ListaTareas* lista) {
    if (lista->cabeza == NULL || lista->cabeza->sig == NULL) return; // 0 o 1 elemento

    int intercambiado;
    NodoTarea* actual;
    NodoTarea* ultimo = NULL; // Optimización de la burbuja

    do {
        intercambiado = 0;
        actual = lista->cabeza;

        while (actual->sig != ultimo) {
            // Orden descendente (5 es mayor prioridad que 1)
            if (actual->tarea.prioridad < actual->sig->tarea.prioridad) {
                // Intercambiar SOLO los datos (structs), no los punteros
                Tarea temp = actual->tarea;
                actual->tarea = actual->sig->tarea;
                actual->sig->tarea = temp;
                intercambiado = 1;
            }
            actual = actual->sig;
        }
        ultimo = actual; // El elemento más pequeño ya burbujeó al final
    } while (intercambiado);
    
    printf("Lista ordenada por prioridad (Mayor a menor).\n");
}