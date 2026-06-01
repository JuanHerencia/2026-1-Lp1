#include <stdio.h>
#include <errno.h>
#include <string.h>

void manejar_errores() {
    FILE *f = fopen("/archivo/que/no/existe.txt", "r");
    
    if (f == NULL) {
        // perror: imprime mensaje de error del sistema
        perror("Error abriendo archivo");
        
        // strerror: convierte errno a string
        printf("Detalle: %s\n", strerror(errno));
        return;
    }
    
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), f) == NULL) {
        if (ferror(f)) {  // ¿Hubo error (no fin de archivo)?
            printf("Error de lectura: %s\n", strerror(errno));
            clearerr(f);  // Limpiar indicador de error
        } else if (feof(f)) {
            printf("Fin de archivo normal\n");
        }
    }
    
    fclose(f);
}

int main()
{
    manejar_errores();
    return 0;
}