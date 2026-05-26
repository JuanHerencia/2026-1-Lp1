// Cada vez que se llama se agrega datos al log
#include <stdio.h>
#include <time.h>

int main() 
{
    FILE *log = fopen("aplicacion.log", "a");
    if (!log) return 1;
    
    // fprintf: escritura formateada (similar a printf)
    time_t ahora = time(NULL);
    fprintf(log, "[%s] Usuario: %s, Acción: %s\n", 
            ctime(&ahora), "admin", "inició sesión");
    
    // fputs: escribe cadena cruda (sin formato, sin \n automático)
    fputs("=== FIN DE OPERACIÓN ===\n", log);
    
    fclose(log);
}