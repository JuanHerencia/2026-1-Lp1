#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de Médico
typedef struct {
    int id;
    char nombre[50];
    char especialidad[50];
} Medico;

// Definición de Historia Médica
typedef struct {
    char fecha[11]; // Formato sugerido: YYYY-MM-DD
    char diagnostico[100];
    char tratamiento[200];
    int idMedico;
} HistoriaMedica;

// Definición del Nodo para la lista enlazada simple
typedef struct NodoHistoria {
    HistoriaMedica historia;
    struct NodoHistoria* siguiente;
} NodoHistoria;

// Definición de Paciente
typedef struct {
    int id;
    char nombre[50];
    int edad;
    NodoHistoria* listaHistorias; // Puntero al inicio de la lista enlazada
} Paciente;

// Prototipos
void agregarHistoria(Paciente* paciente, HistoriaMedica historia);
void buscarPorDiagnostico(Paciente* paciente, const char* diagnostico);
void listarHistorias(Paciente* paciente);
void liberarPaciente(Paciente* paciente);

// ---------------------------------------------------------
// Implementación: Agregar nueva historia (Inserción al final)
// ---------------------------------------------------------
void agregarHistoria(Paciente* paciente, HistoriaMedica historia) {
    // 1. Crear el nuevo nodo dinámicamente
    NodoHistoria* nuevoNodo = (NodoHistoria*)malloc(sizeof(NodoHistoria));
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria para la nueva historia.\n");
        return;
    }
    
    // 2. Asignar los datos
    nuevoNodo->historia = historia;
    nuevoNodo->siguiente = NULL; // Como irá al final, su siguiente es NULL
    
    // 3. Insertar en la lista del paciente
    if (paciente->listaHistorias == NULL) {
        // La lista está vacía, el nuevo nodo es el primero
        paciente->listaHistorias = nuevoNodo;
    } else {
        // Recorrer hasta el último nodo
        NodoHistoria* actual = paciente->listaHistorias;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        // Enlazar el nuevo nodo al final
        actual->siguiente = nuevoNodo;
    }
    printf("Historia agregada exitosamente.\n");
}

// ---------------------------------------------------------
// Implementación: Buscar historias por diagnóstico
// ---------------------------------------------------------
void buscarPorDiagnostico(Paciente* paciente, const char* diagnostico) {
    if (paciente->listaHistorias == NULL) {
        printf("El paciente no tiene historias medicas registradas.\n");
        return;
    }

    printf("\n--- Resultados de busqueda para '%s' ---\n", diagnostico);
    NodoHistoria* actual = paciente->listaHistorias;
    int encontrados = 0;
    
    while (actual != NULL) {
        // Usamos strstr para buscar coincidencias parciales ignorando mayúsculas/minúsculas idealmente,
        // pero strstr estándar busca coincidencias exactas de subcadenas.
        if (strstr(actual->historia.diagnostico, diagnostico) != NULL) {
            printf("Fecha: %s | Diagnostico: %s\n", actual->historia.fecha, actual->historia.diagnostico);
            printf("Tratamiento: %s\n", actual->historia.tratamiento);
            printf("ID Medico: %d\n\n", actual->historia.idMedico);
            encontrados++;
        }
        actual = actual->siguiente;
    }
    
    if (encontrados == 0) {
        printf("No se encontraron coincidencias.\n");
    }
}

// ---------------------------------------------------------
// Implementación: Listar todas las historias
// ---------------------------------------------------------
void listarHistorias(Paciente* paciente) {
    printf("\n--- Historial Medico de %s (ID: %d) ---\n", paciente->nombre, paciente->id);
    
    NodoHistoria* actual = paciente->listaHistorias;
    if (actual == NULL) {
        printf("No hay historias registradas.\n");
        return;
    }
    
    while (actual != NULL) {
        printf("[%s] Diagnostico: %s | Tratamiento: %s | Medico ID: %d\n", 
               actual->historia.fecha, 
               actual->historia.diagnostico, 
               actual->historia.tratamiento, 
               actual->historia.idMedico);
        actual = actual->siguiente;
    }
}

// ---------------------------------------------------------
// Implementación: Liberar memoria del paciente (Prevención de fugas)
// ---------------------------------------------------------
void liberarPaciente(Paciente* paciente) {
    NodoHistoria* actual = paciente->listaHistorias;
    NodoHistoria* temporal;
    
    // Recorremos la lista liberando cada nodo para evitar memory leaks
    while (actual != NULL) {
        temporal = actual->siguiente; // Guardar referencia al siguiente
        free(actual);                 // Liberar el nodo actual
        actual = temporal;            // Avanzar
    }
    
    paciente->listaHistorias = NULL; // Dejar el puntero limpio por seguridad
    printf("Memoria del historial del paciente liberada correctamente.\n");
}