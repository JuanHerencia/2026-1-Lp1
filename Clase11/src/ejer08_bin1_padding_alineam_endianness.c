/*
Este código demuestra cómo manejar dos problemas críticos de bajo nivel en C: el alineamiento de memoria (Padding) y la compatibilidad al guardar datos en archivos (Endianness).
Aquí tienes la explicación detallada de cada concepto:
1. El Problema del Padding (Alineamiento de Memoria)
Los procesadores modernos leen la memoria en bloques (normalmente de 4 u 8 bytes) por eficiencia. Por eso, el compilador añade bytes "vacíos" invisibles (padding) para que cada variable empiece en una dirección de memoria óptima.
•	MalEmpaquetada: Aunque sumas sus componentes (1 + 4 + 1) y parece que mide 6 bytes, pesa 12 bytes. El compilador deja 3 bytes vacíos después del primer char y otros 3 después del último char para alinearlo todo a múltiplos de 4.
•	BienEmpaquetada: La directiva #pragma pack(push, 1) le ordena al compilador: "No dejes espacios en blanco, junta todo lo posible". Aquí la estructura sí mide 6 bytes. Esto ahorra espacio pero puede ralentizar milimétricamente el acceso al dato en ciertos procesadores.
2. El Problema del Endianness (Orden de los bytes)
Diferentes procesadores guardan los números de varios bytes en posiciones distintas:
•	Little-Endian (Intel/AMD): Guarda el byte menos significativo primero.
•	Big-Endian (Redes/Archivos antiguos): Guarda el byte más significativo primero.
Si usas fwrite(&numero, ...) directamente en una PC Intel y luego abres ese archivo en una arquitectura diferente, el número se leerá completamente al revés y corrupto.
•	escribir_portable(): El código soluciona esto usando desplazamiento de bits (>>). Descompone el número 0x12345678 en 4 bytes individuales y los fuerza a guardarse estrictamente en orden Big-Endian (12, luego 34, luego 56, luego 78), sin importar qué procesador ejecute el programa.
•	leer_portable(): Lee los 4 bytes del archivo uno por uno y los vuelve a armar de forma matemática usando el operador OR (|). Esto garantiza que el resultado final vuelva a ser 12345678 en cualquier computadora del mundo.
El flujo en main
El programa escribe el número de forma segura en numeros.bin, lo vuelve a leer reconstruyendo sus bytes de manera portátil y lo imprime en la consola en formato hexadecimal (%X), demostrando que el valor no sufrió alteraciones.
*/

#include <stdio.h>
#include <stdint.h>

// Problema 1: Padding (la estructura no tiene el tamaño que parece)
typedef struct {
    char c;     // 1 byte
    int i;      // 4 bytes (se alinea a múltiplo de 4)
    char d;     // 1 byte
} MalEmpaquetada;
// Tamaño real: 12 bytes (no 6)

// Solución: forzar empaquetado (dependiente del compilador)
#pragma pack(push, 1)
typedef struct {
    char c;
    int i;
    char d;
} BienEmpaquetada;
#pragma pack(pop)
// Tamaño real: 6 bytes

// Problema 2: Endianness (orden de bytes)
void escribir_portable() {
    FILE *f = fopen("numeros.bin", "wb");
    uint32_t numero = 0x12345678;
    
    printf("Se escribirá el número hexadecimal: %X\n", numero);
    // Escribir en orden big-endian (independiente de la máquina)
    uint8_t bytes[4];
    bytes[0] = (numero >> 24) & 0xFF;
    bytes[1] = (numero >> 16) & 0xFF;
    bytes[2] = (numero >> 8) & 0xFF;
    bytes[3] = numero & 0xFF;
    
    fwrite(bytes, 1, 4, f);
    fclose(f);
}

uint32_t leer_portable() {
    FILE *f = fopen("numeros.bin", "rb");
    uint8_t bytes[4];
    fread(bytes, 1, 4, f);
    fclose(f);
    
    // Reconstruir independientemente del endianness
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

int main()
{
    escribir_portable();
    printf("Salida: %X\n",leer_portable());

    /*
    •	El operador sizeof: No es una función, sino un operador en tiempo de compilación que devuelve el tamaño exacto en bytes de un tipo de datos o variable.
    •	El especificador %zu: Es el formato correcto y estándar en printf para imprimir valores del tipo size_t (que es el tipo de dato que devuelve siempre sizeof).
    Al compilar y ejecutar este programa, tu consola te mostrará visualmente la diferencia de 12 frente a 6 bytes.
    */

    /*
    // Comprobación de tamaños reales en memoria
    printf("=== COMPROBACIÓN DE PADDING ===\n");
    printf("Tamaño teórico sumado: 1 + 4 + 1 = 6 bytes\n\n");
    
    printf("Tamaño de 'MalEmpaquetada':  %zu bytes (Tiene padding)\n", sizeof(MalEmpaquetada));
    printf("Tamaño de 'BienEmpaquetada': %zu bytes (Forzada con pragma)\n", sizeof(BienEmpaquetada));
    printf("================================\n\n");

    // Ejecución del resto de tu código original
    escribir_portable();
    printf("Salida Endianness: %X\n", leer_portable());
    */
    
    return 0;
}