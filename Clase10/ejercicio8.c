#include <stdio.h>
#include <stdlib.h>
// Un nodo que apunta a otro del mismo tipo
struct Nodo {
    int dato;
    struct Nodo *siguiente;  // ¡Se referencia a sí mismo!
};

// Ejemplo: crear un nodo que apunte a otro
int main() {
    struct Nodo primero = {10, NULL};
    struct Nodo segundo = {20, NULL};
    
    primero.siguiente = &segundo;  // primero -> segundo
    
    printf("Primero: %d\n", primero.dato);
    printf("Segundo vía primero: %d\n", primero.siguiente->dato);
    
    // Crear un solo nodo dinámicamente
    struct Nodo *nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    
    if (nuevo == NULL) {
        printf("Error: memoria insuficiente\n");
        return 1;
    }
    
    nuevo->dato = 42;
    nuevo->siguiente = NULL;
    
    printf("Nodo creado: %d en dirección %p\n", nuevo->dato, (void*)nuevo);
    
    // ¡LIBERAR cuando ya no se necesite!
    free(nuevo);
    nuevo = NULL;  // Buena práctica para evitar dangling pointer
    
    return 0;
}