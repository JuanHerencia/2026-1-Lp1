#include<stdio.h>
#define NULO 0

/*
   Esta función espera argumentos:de tipo direccion de memoria
   (punteros)

   Los resultados de la operaciones dentro de la función se 
   devuelven las direcciones de los punteros a y b
*/
void intercambiar(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int main()  {
   int m = 10, n = 5;
   printf("Antes del intercambio: m = %d, n = %d\n", m,n);
   intercambiar(&m, &n); // intercambiar los valores
   printf("Despues del intercambio: m = %d, n = %d\n", m,n);
}