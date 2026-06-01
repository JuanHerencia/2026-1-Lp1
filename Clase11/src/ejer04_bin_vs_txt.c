#include <stdio.h>

// En Windows: "\n" (texto) se convierte a "\r\n" en escritura
// En modo binario: NO hay conversión

void demostracion_modos() {
    FILE *txt = fopen("test.txt", "w");
    FILE *bin = fopen("test.bin", "wb");
    
    // Escribir un solo byte 10 (LF en ASCII)
    fputc('\n', txt);  // En Windows escribe 13,10 (CR+LF)
    fputc('\n', bin);  // En todos los sistemas escribe 10
    
    fclose(txt);
    fclose(bin);
}

int main()
{
    demostracion_modos();
    return 0;
}