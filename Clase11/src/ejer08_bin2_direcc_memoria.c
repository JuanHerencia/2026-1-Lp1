#include <stdio.h>
#include <stdint.h>

typedef struct {
    char c;     // 1 byte
    int i;      // 4 bytes
    char d;     // 1 byte
} MalEmpaquetada;

#pragma pack(push, 1)
typedef struct {
    char c;
    int i;
    char d;
} BienEmpaquetada;
#pragma pack(pop)

void analizar_mal_empaquetada() {
    MalEmpaquetada ejemplo;
    uintptr_t base = (uintptr_t)&ejemplo;

    printf("=== MAPA DE MEMORIA: MalEmpaquetada (Total: %zu bytes) ===\n", sizeof(MalEmpaquetada));
    printf("Dirección Base de la estructura: %p\n\n", (void*)&ejemplo);
    
    // Offset (distancia desde el inicio) = Dirección del miembro - Dirección base
    printf("Miembro 'c' (char): Direcc: %p | Desplazamiento: %ld bytes\n", 
           (void*)&ejemplo.c, (uintptr_t)&ejemplo.c - base);
    printf("  [!] Aquí el compilador mete 3 bytes vacíos de padding para alinear el entero...\n");
    
    printf("Miembro 'i' (int) : Direcc: %p | Desplazamiento: %ld bytes\n", 
           (void*)&ejemplo.i, (uintptr_t)&ejemplo.i - base);
           
    printf("Miembro 'd' (char): Direcc: %p | Desplazamiento: %ld bytes\n", 
           (void*)&ejemplo.d, (uintptr_t)&ejemplo.d - base);
    printf("  [!] Aquí mete otros 3 bytes al final para que toda la estructura sea múltiplo de 4.\n\n");
}

void analizar_bien_empaquetada() {
    BienEmpaquetada ejemplo;
    uintptr_t base = (uintptr_t)&ejemplo;

    printf("=== MAPA DE MEMORIA: BienEmpaquetada (Total: %zu bytes) ===\n", sizeof(BienEmpaquetada));
    printf("Dirección Base de la estructura: %p\n\n", (void*)&ejemplo);
    
    printf("Miembro 'c' (char): Direcc: %p | Desplazamiento: %ld bytes\n", 
           (void*)&ejemplo.c, (uintptr_t)&ejemplo.c - base);
    printf("Miembro 'i' (int) : Direcc: %p | Desplazamiento: %ld bytes\n", 
           (void*)&ejemplo.i, (uintptr_t)&ejemplo.i - base);
    printf("Miembro 'd' (char): Direcc: %p | Desplazamiento: %ld bytes\n\n", 
           (void*)&ejemplo.d, (uintptr_t)&ejemplo.d - base);
}


/*
Cuando se ejecute este programa, fíjarse en la columna de Desplazamiento:
1.	En MalEmpaquetada:
  'c' empieza en el byte 0.
  'i' no empieza en el byte 1, sino en el byte 4. Esos bytes 1, 2 y 3 son el padding oculto.
  'd' empieza en el byte 8. Ocupa el byte 8 y el tamaño total salta a 12 porque los bytes 9, 10 y 11 son padding final.
2.	En BienEmpaquetada:
  'c' empieza en 0.
  'i' empieza exactamente en 1 (justo después del char).
  'd' empieza exactamente en 5 (justo después del int de 4 bytes). El tamaño total es estrictamente 6.
*/
int main() {
    analizar_mal_empaquetada();
    analizar_bien_empaquetada();
    return 0;
}
