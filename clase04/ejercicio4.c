// Ejercicio 4
// switch y enum
#include <stdio.h>

// DiaSemana es un tipo de variable enum
// Por defecto LUNES es 0, MARTES es 1, ...
typedef enum { LUNES, MARTES, MIERCOLES, JUEVES, VIERNES, SABADO, DOMINGO } DiaSemana;
typedef enum { MASCULINO, FEMENINO } Sexo; // MASCULINO es 0, FEMENINO es 1
typedef enum { ARRIBA, ABAJO, DERECHA, IZQUIERDA} Tecla_flecha;

// función que devuelve un puntero a una cadena
// devuelve la dirección de meoria de un texto
const char* tipo_dia(DiaSemana d) {
    // d es un valor constante
    switch (d) { // selector se ejecuta por vez uno o mas casos y sale de switch
        case SABADO:  // caso 5
        case DOMINGO: // caso 6
            return "Fin de semana"; // de cada opción se sale (termina) con return
        case LUNES:   // caso 0
            return "Inicio laboral"; // normalmente se usa break para salir de un switch
        default:      // Cuando no se cumpla ninguna de las anteriores, considerar esta opción
            return "Dia laboral";
    }
}

int main() {
    for (int i = LUNES; i <= DOMINGO; i++)
        printf("valor constante %d: %s\n", i, tipo_dia((DiaSemana)i));
    return 0;
}