// Ejercicio 3
// Conceptos: Duración estática, visibilidad, extern
#include <stdio.h>

// con static, contador_local se convierte en global
// para el uso solamente de este archivo
// persistirá en toda la ejecución del programa
// Sin static, pero usando extern desde otros archivos
// se accede a esta variable como global
/*static*/ int contador_local = 0;  // Solo visible en este archivo

void incrementar() {
    // se crea una memoria persistente
    // Para uso solo dentro de la función
    static int veces = 0;   // Persiste entre llamadas
    veces++;
    contador_local++; // esta función manipula a la var global
    printf("veces (estática local): %d, contador_local (estática global): %d\n", veces, contador_local);
}