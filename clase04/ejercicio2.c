// Ejercicio 2
// Conversiones
/*
    La muestra de long double con printf dependerá del compilador y
    la arquitectura de la PC asociada
*/

#include <stdio.h>

int main() {
    int a = 5, b = 2;
    float div1 = a / b;           // Conversión implícita después de división entera
    float div2 = (float)a / b;    // Casting explícito

    printf("Sin casting: %f\n", div1);   // 2.000000
    printf("Con casting: %f\n", div2);   // 2.500000

    long double ld = 1.234567890123456789L;
    double d = ld;   // Pérdida de precisión implícita
    printf("long double: %0.20Lf y su tamaño es %d bytes\n", ld, sizeof(ld));
    printf("double: %0.20f y su tamaño es %d bytes\n", d, sizeof(d));
    return 0;
}