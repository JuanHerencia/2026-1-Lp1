#include <stdio.h>
#include <string.h>

union Dato {
    int entero;      // 4 bytes
    float flotante;  // 4 bytes
    char texto[20];  // 20 bytes
};  // El tamaño es 20 bytes (el campo más grande)

int main() {
    union Dato u;
    
    printf("Tamaño de union: %lu bytes\n", sizeof(u));
    printf("Dirección de u.entero: %p\n", &u.entero);
    printf("Dirección de u.flotante: %p\n", &u.flotante);
    printf("Dirección de u.texto: %p\n", &u.texto);
    // ¡Las tres direcciones son IDÉNTICAS!
    
    u.entero = 65;
    printf("Como entero: %d\n", u.entero);
    printf("Como float (basura): %f\n", u.flotante);  // Interpretación errónea
    printf("Como texto: %s\n", u.texto);  // Podría ser "A" si little-endian
    
    // Uso práctico: discriminador
    u.flotante = 3.1416;
    printf("Como float: %f\n", u.flotante);
    // u.entero ahora tiene basura
    
    return 0;
}