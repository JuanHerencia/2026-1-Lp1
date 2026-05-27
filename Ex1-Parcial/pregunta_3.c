#include <stdio.h>

/* --- Prototipos de funciones --- */
int esPrimo(int num);
int sumarDigitos(int num);
int esNumeroEspecial(int num);

/* --- Implementación de funciones --- */

/**
 * @brief Determina si un número es primo.
 * Restricción: Un solo punto de salida y sin usar break.
 */
int esPrimo(int num) {
    int primo = 1; // Bandera: asumimos que es primo (1)
    
    if (num < 1) {
        primo = 0; // Consideraremos a no primo, pero 1 si es primo
    } else {
        // La condición 'primo == 1' actúa como parada temprana para evitar usar 'break'
        for (int i = 2; i * i <= num && primo == 1; i++) {
            if (num % i == 0) {
                primo = 0; // Si es divisible, cambiamos la bandera y el bucle termina
            }
        }
    }
    
    return primo; // Único punto de salida
}

/**
 * @brief Calcula la suma de los dígitos de un número mediante divisiones sucesivas.
 */
int sumarDigitos(int num) {
    int suma = 0;
    int temp = num;
    
    while (temp > 0) {
        suma += temp % 10; // Extrae el último dígito
        temp /= 10;        // Elimina el último dígito
    }
    
    return suma; // Único punto de salida
}

/**
 * @brief Evalúa si un número cumple las condiciones para ser "especial".
 */
int esNumeroEspecial(int num) {
    int es_especial = 0; // Bandera de resultado
    
    // Condición 1: es primo O la suma de sus dígitos es múltiplo de 3
    int condicion1 = (esPrimo(num) == 1) || (sumarDigitos(num) % 3 == 0);
    
    // Condición 2: NO es múltiplo de 5
    int condicion2 = (num % 5 != 0);
    
    if (condicion1 && condicion2) {
        es_especial = 1;
    }
    
    return es_especial; // Único punto de salida
}

/* --- Programa Principal --- */
int main() {
    int n;
    
    // Pregunta 3.1: Validación de entrada (se permite continue/break o do-while)
    // El do-while es la estructura natural para esto.
    do {
        printf("Ingrese un numero entero positivo n (n > 0): ");
        scanf("%d", &n);
        if (n <= 0) {
            printf("Error. El numero debe ser positivo.\n");
        }
    } while (n <= 0);
    
    // Pregunta 3.3: Impresión de números especiales
    printf("\nNumeros especiales hasta %d:\n", n);
    for (int i = 1; i <= n; i++) {
        if (esNumeroEspecial(i) == 1) {
            // Nota: El enunciado pide "uno por línea", aunque el ejemplo
            // visual los muestra separados por espacios. 
            // Usamos salto de línea para ser fieles a la instrucción de texto.
            printf("%d\n", i); 
        }
    }
    
    return 0;
}