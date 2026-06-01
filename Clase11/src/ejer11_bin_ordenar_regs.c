#include <stdlib.h>

int comparar_clientes(const void *a, const void *b) {
    const Cliente *c1 = (const Cliente*)a;
    const Cliente *c2 = (const Cliente*)b;
    return c1->id - c2->id;
}

void ordenar_archivo(const char *nombre) {
    FILE *f = fopen(nombre, "rb+");
    if (!f) return;
    
    // Contar registros
    fseek(f, 0, SEEK_END);
    long num_registros = ftell(f) / sizeof(Cliente);
    rewind(f);
    
    // Leer todo a memoria
    Cliente *clientes = malloc(num_registros * sizeof(Cliente));
    fread(clientes, sizeof(Cliente), num_registros, f);
    
    // Ordenar
    qsort(clientes, num_registros, sizeof(Cliente), comparar_clientes);
    
    // Reescribir ordenado
    rewind(f);
    fwrite(clientes, sizeof(Cliente), num_registros, f);
    
    free(clientes);
    fclose(f);
    
    printf("Archivo ordenado por ID\n");
}