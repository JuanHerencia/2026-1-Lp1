// Construcción manual de JSON
#include <stdio.h>

typedef struct {
    int id;
    char nombre[50];
    float precio;
} Producto;

void producto_a_json(Producto *p, char *out, size_t tam) {
    snprintf(out, tam, "{\"id\":%d,\"nombre\":\"%s\",\"precio\":%.2f}", 
             p->id, p->nombre, p->precio);
}

int main() {
    Producto prod = {10, "Laptop", 799.99};
    char json_prod[200];
    producto_a_json(&prod, json_prod, sizeof(json_prod));
    printf("%s\n", json_prod);

    // Arreglo manual
    Producto lista[] = {{1, "Mouse", 15.5}, {2, "Teclado", 25.0}};
    printf("[\n");
    for (int i = 0; i < 2; i++) {
        producto_a_json(&lista[i], json_prod, sizeof(json_prod));
        printf("  %s%s\n", json_prod, (i < 1) ? "," : "");
    }
    printf("]\n");
    return 0;
}