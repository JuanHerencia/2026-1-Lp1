/* ejercicio1.c 
 * Estructura básica de un programa en C. 
 * Lee nombre y edad, calcula el año de nacimiento aproximado. 
 */ 

#include <stdio.h> 
#include <stdlib.h> 

#define ANIO_ACTUAL 2025 


/* Prototipo */ 
int calcular_nacimiento(int edad); 
 
int main(void) { 
    char nombre[50]; 
    int  edad; 

    printf("Ingresa tu nombre: "); 
    scanf("%", nombre); 

    printf("Ingresa tu edad: "); 
    scanf("%", &edad); 

    printf("\nHola, %s!\n", nombre); 
    printf("Naciste aproximadamente en: %d\n",    
    calcular_nacimiento(edad)); 

     return EXIT_SUCCESS; 
} 

int calcular_nacimiento(int edad) { 
    return ANIO_ACTUAL - edad; 
} 
