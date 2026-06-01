#include <stdio.h>

void navegacion_archivo() {
    FILE *f = fopen("datos.bin", "wb+");
    
    // Escribir datos
    int datos[] = {100, 200, 300, 400, 500};
    fwrite(datos, sizeof(int), 5, f);
    
    // ftell: obtener posición actual (en bytes desde el inicio)
    long pos = ftell(f);
    printf("Posición después de escribir: %ld\n", pos);  // 20 (5*4 bytes)
    
    // fseek(archivo, desplazamiento, origen)
    // Orígenes: SEEK_SET (inicio), SEEK_CUR (actual), SEEK_END (final)
    
    // Ir al tercer elemento (índice 2)
    fseek(f, 2 * sizeof(int), SEEK_SET);
    
    int valor;
    fread(&valor, sizeof(int), 1, f);
    printf("Tercer elemento: %d\n", valor);  // 300
    
    // Ir al último elemento
    fseek(f, -sizeof(int), SEEK_END);
    fread(&valor, sizeof(int), 1, f);
    printf("Último elemento: %d\n", valor);  // 500
    
    // Ir al inicio (rewind es más claro que fseek(f, 0, SEEK_SET))
    rewind(f);
    fread(&valor, sizeof(int), 1, f);
    printf("Primer elemento: %d\n", valor);  // 100
    
    fclose(f);
}

int main()
{
    navegacion_archivo();

    return 0;
}