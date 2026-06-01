#include <stdio.h>
#include <stdlib.h>

void escribir_binario() {
    FILE *f = fopen("numeros.bin", "wb");
    if (!f) return;
    
    int numeros[] = {10, 20, 30, 40, 50};
    int cantidad = 5;
    
    // fwrite(ptr, tamaño_elemento, cantidad, archivo)
    size_t escritos = fwrite(numeros, sizeof(int), cantidad, f);
    
    printf("Se escribieron %zu de %d elementos\n", escritos, cantidad);
    
    fclose(f);
}

void leer_binario() {
    FILE *f = fopen("numeros.bin", "rb");
    if (!f) return;
    
    int buffer[10];
    
    // fread(ptr, tamaño_elemento, cantidad, archivo)
    size_t leidos = fread(buffer, sizeof(int), 10, f);
    
    printf("Se leyeron %zu enteros:\n", leidos);
    for (int i = 0; i < leidos; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
    
    fclose(f);
}

int main()
{
    escribir_binario();
    leer_binario();

    return 0;
}