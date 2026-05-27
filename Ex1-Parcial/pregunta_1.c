#include <stdio.h>
#include <string.h>

int main()
{
    printf("------------Pregunta 1.1-------------\n");
    char msj[20];
    int x = 5, y = 10;
    if (x = y)
        strcpy(msj, "Iguales");
    else
        strcpy(msj, "Diferentes");
    printf(msj);
    printf("\n");
    if (!strcmp(msj, "Iguales")) // strcmp devuelve 0 si son iguales!!!
        printf("V, hay asinacion x <- y, entonces x > 0, entonces cualquier valor diferente de cero es Verdadero\n");
    else
        printf("F\n");

    printf("\n------------Pregunta 1.2-------------\n");
    int i = 0;
    while (i < 5)
        i++;
    printf("%d ", i);
    printf("\nF, while solo afecta a i++, i llega a 5 y solo se muestra 5\n");

    printf("\n------------Pregunta 1.3-------------\n");
    int a = 5, b = 5;
    if (a == b)
    {
        int c = 10;
    }
    printf("F, Error!, c no esta definido\n");
    // printf("%d\n", c); // error c no está definido

    printf("\n------------Pregunta 1.4-------------\n");
    int cont = 0;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < i; j++)
            cont++;
    printf("cont es %d\n", cont);
    printf("V\n");
    printf("\n------------Pregunta 1.5-------------\n");
    int n = 5;
    int resultado = (n > 0) ? (n % 2 == 0 ? n / 2 : n * 2) : -1;
    printf("resultado es %d\n", resultado);
    printf("V, Porque n es mayor que cero y n es impar\n");
}
