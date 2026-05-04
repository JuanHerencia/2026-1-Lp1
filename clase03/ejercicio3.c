#include <stdio.h> 
#include <stdlib.h> 

int main(void) { 
    int celsius; 
    double fahrenheit; 
    double kelvin; 

    /* Paso 1: leer entrada */ 
    printf("Ingresa temperatura en Celsius: "); 
    int x = scanf("%lf", &celsius);
    printf("x es %d\n", x);
    if ( x != 1) { 
        fprintf(stderr, "Error: entrada no valida.\n"); 
        return EXIT_FAILURE; 
    } 

    /* Paso 2: convertir a Fahrenheit (depende de celsius) */ 
    fahrenheit = celsius * 9 / 5 + 32.0; 

    /* Paso 3: convertir a Kelvin (depende de celsius) */ 
    kelvin = celsius + 273.15; 

    /* Paso 4: mostrar resultados — el orden importa */ 
    printf("\n--- Resultados ---\n"); 
    printf("Celsius    : %8.2f C\n", celsius); 
    printf("Fahrenheit : %8.2f F\n", fahrenheit); 
    printf("Kelvin     : %8.2f K\n", kelvin); 

    /* Paso 5: efecto secundario del orden — advertencia física */ 
    if (kelvin < 0.0) { 
        /* Solo posible si celsius < -273.15: físicamente imposible */ 
        fprintf(stderr, "Advertencia: temperatura por debajo del cero absoluto.\n"); 
    } 
    return EXIT_SUCCESS; 

} 