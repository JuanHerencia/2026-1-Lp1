#include <stdio.h>
int misterio(int n)
{
    int suma = 0;
    int signo = 1;
    for (int i = 1; i <= n; i++)
    {
        int termino = i;
        printf("termino = i = %d\n", i);
        for (int j = 1; j <= i; j++)
        {
            termino = termino * j;
            printf("\ttermino = termino * j\n\ttermino = %d * %d\n", termino, j);
        }
        suma = suma + signo * termino;
        printf("suma = suma + signo * termino\n");
        printf("suma = %d + %d * %d\n", suma, signo, termino);
        signo = -signo;
    }
    return suma;
}

int main()
{
    int x = 4;
    int resultado = misterio(x);
    printf("Resultado: %d\n", resultado);

    // Segunda parte
    int y = 0;
    do
    {
        y++;
        if (y % 2 == 0)
            continue;
        printf("%d ", y);
    } while (y < 6);

    return 0;
}