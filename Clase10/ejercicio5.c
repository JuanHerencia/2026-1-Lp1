#include <stdio.h>

// Sin enum (malo)
#define LUNES 0
#define MARTES 1
// ...

// Con enum (bueno)
enum Dias { LUN, MAR, MIE, JUE, VIE, SAB, DOM };

// Especificando valores
enum Colores { ROJO = 1, VERDE = 2, AZUL = 4 };

// Uso típico con switch
int main() {
    enum Dias hoy = MIE;
    
    if (hoy == MIE) {
        printf("Mitad de semana\n");
    }
    
    // Los enums son enteros
    printf("LUN=%d, MAR=%d\n", LUN, MAR);  // 0,1
    
    return 0;
}