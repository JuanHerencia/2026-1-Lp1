// Ejercicio 1
#include <stdio.h>
#include <stdint.h>

typedef uint8_t byte;  // Definir un tipo byte de 8 bits sin signo

// Función que extrae los n bits desde la posición p de un número
byte extraer_bits(byte num, int p, int n) {
    return (num >> (p - n + 1)) & ((1 << n) - 1);
}

int main() {
    byte dato = 0b11011010;  // 218 decimal
    printf("Tamaño de byte: %zu bytes\n", sizeof(byte));
    printf("Bits 2-4 (0-indexado desde derecha): %d\n", extraer_bits(dato, 4, 3));
    return 0;
}