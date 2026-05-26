#include <stdio.h>

struct Grande {
    char datos[1000];
    int valor;
};

// Paso por valor (copia - ineficiente)
void modificar_valor(struct Grande g) {
    g.valor = 999;  // Solo modifica la copia
    // El original no cambia
}

// Paso por puntero (eficiente + puede modificar)
void modificar_puntero(struct Grande *g) {
    g->valor = 999;  // Modifica el original
}

// Const pointer (eficiente + solo lectura)
void solo_leer(const struct Grande *g) {
    printf("Valor: %d\n", g->valor);
    // g->valor = 999;  // Error de compilación
}

int main() {
    struct Grande g = {.valor = 100};
    
    modificar_valor(g);
    printf("Después de valor: %d\n", g.valor);  // 100
    
    modificar_puntero(&g);
    printf("Después de puntero: %d\n", g.valor);  // 999
    
    return 0;
}