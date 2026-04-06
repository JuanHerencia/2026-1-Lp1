#include <stdio.h>
static int llamadas = 0; // estática local: persiste entre llamadas

int main()
{
     llamadas++;
    printf("llamada #%d\n", llamadas);
}