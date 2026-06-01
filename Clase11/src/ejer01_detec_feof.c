#include <stdio.h>

void detectar_fin_correctamente() {
    FILE *f = fopen("datos.txt", "r");
    if (!f) return;
    
    char buffer[100];
    
    // MAL: feof antes de leer
    while (!feof(f)) {  // ¡Esto ejecuta una iteración extra!
        fgets(buffer, sizeof(buffer), f);
        printf("%s", buffer);
    }
    
    // BIEN: verificar el valor de retorno
    rewind(f);
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        printf("%s", buffer);
    }
    
    // Para fscanf:
    rewind(f);
    int valor;
    while (fscanf(f, "%d", &valor) == 1) {  // Verifica que leyó 1 elemento
        printf("Leído: %d\n", valor);
    }
    
    fclose(f);
}

int main()
{
    detectar_fin_correctamente();
    return 0;
}