#include <stdio.h>
#include <unistd.h> // dup

void redireccion_ejemplo() {
    // Redirigir stdout a un archivo
    FILE *original_stdout = stdout;
    FILE *log_file = fopen("redireccion.txt", "w");
    /* 
    Redirección básica de stdout (Salida)
    El programa guarda la salida estándar original y redirige los mensajes hacia un archivo de texto.
    •Redirección: Abre redireccion.txt y asigna el flujo de stdout a este archivo. Por lo tanto, el primer printf no se ve en la consola.
    •Restauración: Vuelve a asignar stdout al valor original para que el siguiente printf vuelva a salir por la pantalla.
    */
    
    stdout = log_file;  // Cambiar el puntero global (¡cuidado!)
    printf("Este texto va al archivo, no a la consola\n");
    
    fflush(stdout);
    stdout = original_stdout;  // Restaurar
    printf("Este texto vuelve a la consola\n");
    
    fclose(log_file);
    /*
    Uso de freopen (El método seguro)
    •Se utiliza para cambiar un flujo estándar directamente.
    •La primera llamada redirige stdout a output.txt (todo lo que se imprima después va al archivo).
    •La segunda llamada redirige stdout de vuelta a la consola utilizando la ruta /dev/tty (válido en sistemas Unix/Linux)
    */
    
    // Mejor: usar freopen (más seguro)
    freopen("output.txt", "w", stdout);
    printf("Todo esto va al archivo\n");
    freopen("/dev/tty", "w", stdout);  // Restaurar en Unix/Linux
    
    /*
    Redirección de stdin (Entrada)
    Aquí se lee información desde un archivo en lugar de esperar la escritura manual del usuario.
    •Abre entrada.txt y utiliza la función dup() de Unix para crear un duplicado de la entrada original.
    •Cambia stdin para que apunte al archivo. Al ejecutar fgets, el programa lee la primera línea de entrada.txt.
    •Restaura la entrada original asociando de nuevo stdin con el duplicado guardado.
    */
    // Redirección de stdin
    FILE *input = fopen("entrada.txt", "r");
    if (input) {
        int original_stdin = dup(fileno(stdin));  // Guardar (Unix)
        stdin = input;
        
        char linea[100];
        fgets(linea, sizeof(linea), stdin);  // Lee del archivo
        
        stdin = fdopen(original_stdin, "r");  // Restaurar 
        fclose(input);
    }
}

int main()
{
    redireccion_ejemplo();
    return 0;
}