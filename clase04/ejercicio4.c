// Ejercicio 4
// switch y enum
#include <stdio.h>

typedef enum { LUNES, MARTES, MIERCOLES, JUEVES, VIERNES, SABADO, DOMINGO } DiaSemana;

const char* tipo_dia(DiaSemana d) {
    switch (d) {
        case SABADO:
        case DOMINGO:
            return "Fin de semana";
        case LUNES:
            return "Inicio laboral";
        default:
            return "Día laboral";
    }
}

int main() {
    for (int i = LUNES; i <= DOMINGO; i++)
        printf("%d: %s\n", i, tipo_dia((DiaSemana)i));
    return 0;
}