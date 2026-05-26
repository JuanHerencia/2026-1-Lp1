// Apertura y cierre: modos completos
#include <stdio.h>

int main() {
    FILE *f;
    
    // Modos de apertura (texto)
    f = fopen("datos.txt", "r");   // Lectura (archivo debe existir)
    f = fopen("salida.txt", "w");  // Escritura (crea o trunca)
    f = fopen("log.txt", "a");     // Append (escribe al final)
    f = fopen("actualizar.txt", "r+");  // Lectura y escritura
    f = fopen("nuevo.txt", "w+");  // Lectura/escritura (crea o trunca)
    f = fopen("log.txt", "a+");    // Lectura/append (al final)
    
    // Modos binarios (agrega 'b')
    f = fopen("imagen.bmp", "rb");   // Lectura binaria
    f = fopen("datos.bin", "wb");    // Escritura binaria
    f = fopen("backup.bin", "ab");   // Append binario
    
    if (f == NULL) {
        printf("Error: no se pudo abrir el archivo\n");
        return 1;
    }
    
    // ¡Siempre cerrar!
    fclose(f);
    
    return 0;
}