#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de Producto (dada en el enunciado)
typedef struct {
    int codigo;
    char nombre[100];
    char categoria[50];
    float precio;
    int stock;
} Producto;

// Definición del Nodo del Árbol
typedef struct NodoArbol {
    Producto producto;
    struct NodoArbol* izquierdo;
    struct NodoArbol* derecho;
} NodoArbol;

// Estructura controladora del Árbol
typedef struct {
    NodoArbol* raiz;
} ArbolProductos;

// ---------------------------------------------------------
// Inicialización
// ---------------------------------------------------------
void inicializarArbol(ArbolProductos* arbol) {
    arbol->raiz = NULL;
}

// ---------------------------------------------------------
// Insertar Producto (Ordenado por Código)
// ---------------------------------------------------------
NodoArbol* insertarRec(NodoArbol* nodo, Producto p) {
    // Caso base: encontramos un lugar vacío
    if (nodo == NULL) {
        NodoArbol* nuevo = (NodoArbol*)malloc(sizeof(NodoArbol));
        nuevo->producto = p;
        nuevo->izquierdo = NULL;
        nuevo->derecho = NULL;
        return nuevo;
    }
    
    // Recursividad para ubicar el producto según su código
    if (p.codigo < nodo->producto.codigo) {
        nodo->izquierdo = insertarRec(nodo->izquierdo, p);
    } else if (p.codigo > nodo->producto.codigo) {
        nodo->derecho = insertarRec(nodo->derecho, p);
    } else {
        printf("Error: El producto con codigo %d ya existe.\n", p.codigo);
    }
    return nodo;
}

void insertarProducto(ArbolProductos* arbol, Producto producto) {
    arbol->raiz = insertarRec(arbol->raiz, producto);
}

// ---------------------------------------------------------
// Buscar por Código (Búsqueda Binaria Rápida)
// ---------------------------------------------------------
Producto* buscarCodigoRec(NodoArbol* nodo, int codigo) {
    if (nodo == NULL) return NULL; // No encontrado
    
    if (nodo->producto.codigo == codigo) {
        return &(nodo->producto); // Encontrado
    } else if (codigo < nodo->producto.codigo) {
        return buscarCodigoRec(nodo->izquierdo, codigo); // Buscar en la izquierda
    } else {
        return buscarCodigoRec(nodo->derecho, codigo); // Buscar en la derecha
    }
}

void buscarPorCodigo(ArbolProductos* arbol, int codigo) {
    Producto* p = buscarCodigoRec(arbol->raiz, codigo);
    if (p != NULL) {
        printf("Producto Encontrado: [%d] %s | Categoria: %s | Precio: %.2f | Stock: %d\n", 
               p->codigo, p->nombre, p->categoria, p->precio, p->stock);
    } else {
        printf("Producto con codigo %d no encontrado.\n", codigo);
    }
}

// ---------------------------------------------------------
// Buscar por Nombre (Recorrido Completo del Árbol)
// ---------------------------------------------------------
void buscarNombreRec(NodoArbol* nodo, const char* nombre, int* encontrados) {
    if (nodo != NULL) {
        // Usamos strstr para coincidencias parciales (ej: buscar "Leche" encuentra "Leche Evaporada")
        if (strstr(nodo->producto.nombre, nombre) != NULL) {
            printf("[%d] %s | Stock: %d\n", nodo->producto.codigo, nodo->producto.nombre, nodo->producto.stock);
            (*encontrados)++;
        }
        // Debemos recorrer TODO el árbol porque no está ordenado por nombre
        buscarNombreRec(nodo->izquierdo, nombre, encontrados);
        buscarNombreRec(nodo->derecho, nombre, encontrados);
    }
}

void buscarPorNombre(ArbolProductos* arbol, char* nombre) {
    int encontrados = 0;
    printf("Resultados para '%s':\n", nombre);
    buscarNombreRec(arbol->raiz, nombre, &encontrados);
    if (encontrados == 0) {
        printf("No se encontraron coincidencias.\n");
    }
}

// ---------------------------------------------------------
// Actualizar Stock
// ---------------------------------------------------------
void actualizarStock(ArbolProductos* arbol, int codigo, int nuevoStock) {
    // Reutilizamos la lógica de búsqueda por código por eficiencia
    Producto* p = buscarCodigoRec(arbol->raiz, codigo);
    if (p != NULL) {
        p->stock = nuevoStock;
        printf("Stock del producto %d actualizado a %d.\n", codigo, nuevoStock);
    } else {
        printf("No se pudo actualizar. Producto %d no encontrado.\n", codigo);
    }
}

// ---------------------------------------------------------
// Mostrar Inventario (Recorrido Inorden)
// ---------------------------------------------------------
void mostrarInordenRec(NodoArbol* nodo) {
    if (nodo != NULL) {
        mostrarInordenRec(nodo->izquierdo);
        printf("[%d] %s - %.2f USD (Stock: %d)\n", 
               nodo->producto.codigo, nodo->producto.nombre, nodo->producto.precio, nodo->producto.stock);
        mostrarInordenRec(nodo->derecho);
    }
}

void mostrarInventario(ArbolProductos* arbol) {
    printf("\n--- Inventario Completo (Ordenado por Codigo) ---\n");
    mostrarInordenRec(arbol->raiz);
}

// ---------------------------------------------------------
// Guardar Inventario en Archivo (CSV)
// ---------------------------------------------------------
void guardarArchivoRec(NodoArbol* nodo, FILE* archivo) {
    if (nodo != NULL) {
        guardarArchivoRec(nodo->izquierdo, archivo);
        // Formato CSV (Valores Separados por Comas)
        fprintf(archivo, "%d,%s,%s,%.2f,%d\n", 
                nodo->producto.codigo, nodo->producto.nombre, 
                nodo->producto.categoria, nodo->producto.precio, nodo->producto.stock);
        guardarArchivoRec(nodo->derecho, archivo);
    }
}

void guardarInventario(ArbolProductos* arbol, char* archivo) {
    FILE* f = fopen(archivo, "w");
    if (f == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }
    
    // Escribir cabecera del CSV
    fprintf(f, "Codigo,Nombre,Categoria,Precio,Stock\n");
    guardarArchivoRec(arbol->raiz, f);
    
    fclose(f);
    printf("Inventario guardado en '%s' exitosamente.\n", archivo);
}