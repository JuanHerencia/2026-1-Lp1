// Ejercicio 1
#include <stdio.h> // Estandar de entradas y salidas
#include <stdint.h> // sirve para definir tipos de datos enteros con ancho fijo y garantizado en bits

typedef uint8_t byte;  // Definir tipo byte como tipo de 8 bits sin signo

// Función que extrae los n bits desde la posición p de un número
byte extraer_bits(byte num, int p, int n) {
    return (num >> (p - n + 1)) & ((1 << n) - 1);
    // num es 1 1 0 1 1 0 1 0
    // p = 4, n = 4: num >> 1 & ((1 << 4) - 1)
    // num >> 1 : 0 1 1 0 1 1 0 1
    // 00000001 << 4 : 00010000
    // 00010000 - 1 : 00001111
    // 0 1 1 0 1 1 0 1  &
    // 0 0 0 0 1 1 1 1
    // ---------------
    // 0 0 0 0 1 1 0 1
}

// printf no tiene formato para mostrar binario
// por lo tanto se usará una función que lo construya
void printBinary(int n) {
    // Calcular el número de bits en un int
    int i;
    for (i = sizeof(int) * 8 - 1; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
            printf("1");
        else
            printf("0");
    }
}


int main() {
    byte dato = 0b11011010;  // 218 decimal
    printf("Tamaño de byte: %zu bytes\n", sizeof(byte)); // sizeof operador que devuelve el tamaño de memoria de una variable o tipo
    printf("Bits 1-4 (0-indexado desde derecha): ");
    printBinary(extraer_bits(dato, 4, 4));
    return 0;
}