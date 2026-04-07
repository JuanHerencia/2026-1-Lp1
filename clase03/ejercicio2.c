#include <stdio.h>

#define LIMITE 5 /* constante simbólica (preprocesador) */

const double IVA = 0.20; /* constante tipada (compilador)       */
int total_llamadas = 0; /* variable global */

/* Función que usa una variable static local */
void contar(void)
{
    static int veces = 0; /* persiste entre llamadas */
    int var_local = 0;
    veces++;
    var_local++;
    //total_llamadas++;
    printf("Variacion de veces : %d, de var_local : %d\n",veces, var_local);
    /*printf("  contar() llamada #%d (static veces=%d, global total=%d)\n",
           veces, veces, total_llamadas); */
}

int main(void)
{
    //IVA = 0.21; // da errorrr
    /* Variable local automática */
    double precio = 100.0;
    double precio_final = precio * (1.0 + IVA);
    printf("Precio sin IVA : %.2f\n", precio);
    printf("IVA (%.0f%%)    : %.2f\n", IVA * 100, precio * IVA);
    printf("Precio con IVA : %.2f\n", precio_final);
    printf("\nLlamadas a contar():\n");
    for (int i = 0; i < LIMITE; i++)
    {
        contar();
    }

    /* Bloque anidado: shadow de variable */
    int x = 10;
    int b = x;
    printf("\nFuera del bloque: x = %d\n", x);
    {
        int x = 99 + b; /* oculta la x exterior */
        printf("Dentro del bloque: x = %d\n", x);
    }
    printf("Fuera del bloque: x = %d\n", x); /* recupera la original */
    return 0;
}