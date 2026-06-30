#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de Tipos de Cliente (0 es la mayor prioridad)
typedef enum { 
    VIP,        // 0
    PREMIUM,    // 1
    NORMAL,     // 2
    BASICO      // 3
} TipoCliente;

// Definición de Cliente
typedef struct {
    int id;
    char nombre[50];
    TipoCliente tipo;
    char motivo[100];
    int tiempoAtencion; // en minutos
} Cliente;

// Nodo para la cola (Lista enlazada)
typedef struct NodoCliente {
    Cliente cliente;
    struct NodoCliente* siguiente;
} NodoCliente;

// Estructura controladora de la Cola
typedef struct {
    NodoCliente* frente;
    NodoCliente* final;
} ColaClientes;

// Prototipos
void inicializarCola(ColaClientes* cola);
void encolarCliente(ColaClientes* cola, Cliente cliente);
Cliente desencolarCliente(ColaClientes* cola);
int calcularTiempoEspera(ColaClientes* cola);
void atenderClientes(ColaClientes* cola, int tiempoDisponible);
void guardarReporte(ColaClientes* cola, const char* archivo);

// ---------------------------------------------------------
// Inicialización
// ---------------------------------------------------------
void inicializarCola(ColaClientes* cola) {
    cola->frente = NULL;
    cola->final = NULL;
}

// ---------------------------------------------------------
// Encolar con Prioridad
// ---------------------------------------------------------
void encolarCliente(ColaClientes* cola, Cliente cliente) {
    NodoCliente* nuevoNodo = (NodoCliente*)malloc(sizeof(NodoCliente));
    if (nuevoNodo == NULL) {
        printf("Error de memoria al encolar.\n");
        return;
    }
    nuevoNodo->cliente = cliente;
    nuevoNodo->siguiente = NULL;

    // Caso 1: Cola vacía
    if (cola->frente == NULL) {
        cola->frente = nuevoNodo;
        cola->final = nuevoNodo;
        return;
    }

    // Caso 2: El nuevo cliente tiene mayor prioridad que el frente actual
    // Nota: Menor valor numérico del enum = mayor prioridad (VIP=0 < PREMIUM=1)
    if (cliente.tipo < cola->frente->cliente.tipo) {
        nuevoNodo->siguiente = cola->frente;
        cola->frente = nuevoNodo;
        return;
    }

    // Caso 3: Buscar la posición correcta (después de sus iguales o mayores)
    NodoCliente* actual = cola->frente;
    while (actual->siguiente != NULL && actual->siguiente->cliente.tipo <= cliente.tipo) {
        actual = actual->siguiente;
    }

    // Insertar el nuevo nodo
    nuevoNodo->siguiente = actual->siguiente;
    actual->siguiente = nuevoNodo;

    // Si se insertó al final, actualizar el puntero final de la cola
    if (nuevoNodo->siguiente == NULL) {
        cola->final = nuevoNodo;
    }
}

// ---------------------------------------------------------
// Desencolar (Extraer del frente)
// ---------------------------------------------------------
Cliente desencolarCliente(ColaClientes* cola) {
    Cliente clienteVacio = {0, "", BASICO, "", 0}; // Para casos de error
    
    if (cola->frente == NULL) {
        printf("La cola esta vacia.\n");
        return clienteVacio;
    }

    NodoCliente* nodoAtendido = cola->frente;
    Cliente cliente = nodoAtendido->cliente;

    cola->frente = cola->frente->siguiente;
    
    // Si la cola quedó vacía, actualizamos también el final
    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    free(nodoAtendido); // Liberar memoria
    return cliente;
}

// ---------------------------------------------------------
// Calcular Tiempo Total de Espera
// ---------------------------------------------------------
int calcularTiempoEspera(ColaClientes* cola) {
    int tiempoTotal = 0;
    NodoCliente* actual = cola->frente;
    
    while (actual != NULL) {
        tiempoTotal += actual->cliente.tiempoAtencion;
        actual = actual->siguiente;
    }
    
    return tiempoTotal;
}

// ---------------------------------------------------------
// Atender Clientes por Tiempo Disponible
// ---------------------------------------------------------
void atenderClientes(ColaClientes* cola, int tiempoDisponible) {
    printf("\n--- Iniciando Atencion (Tiempo Disponible: %d min) ---\n", tiempoDisponible);
    
    while (cola->frente != NULL && tiempoDisponible >= cola->frente->cliente.tiempoAtencion) {
        Cliente atendido = desencolarCliente(cola);
        tiempoDisponible -= atendido.tiempoAtencion;
        printf("Atendiendo a: %s (ID: %d) | Tiempo restado: %d min | Restante: %d min\n", 
               atendido.nombre, atendido.id, atendido.tiempoAtencion, tiempoDisponible);
    }
    
    if (cola->frente != NULL) {
        printf("El tiempo disponible acabo. Clientes restantes en cola.\n");
    } else {
        printf("Todos los clientes fueron atendidos.\n");
    }
}

// ---------------------------------------------------------
// Guardar Reporte en Archivo de Texto
// ---------------------------------------------------------
void guardarReporte(ColaClientes* cola, const char* archivo) {
    FILE* file = fopen(archivo, "w");
    if (file == NULL) {
        printf("Error al abrir el archivo %s para escritura.\n", archivo);
        return;
    }

    fprintf(file, "--- REPORTE DE COLA DE CLIENTES ---\n");
    NodoCliente* actual = cola->frente;
    int posicion = 1;
    
    while (actual != NULL) {
        // Convertimos el enum a texto para el archivo
        const char* tipos[] = {"VIP", "PREMIUM", "NORMAL", "BASICO"};
        
        fprintf(file, "%d. ID: %d | Nombre: %s | Tipo: %s | Motivo: %s | Tiempo: %d min\n",
                posicion,
                actual->cliente.id,
                actual->cliente.nombre,
                tipos[actual->cliente.tipo],
                actual->cliente.motivo,
                actual->cliente.tiempoAtencion);
                
        actual = actual->siguiente;
        posicion++;
    }

    fclose(file);
    printf("Reporte guardado exitosamente en '%s'.\n", archivo);
}