// Ejercicio 8
// Personalización del printf
#include <stdio.h>
#include <stdarg.h>

void mi_printf(const char* formato, ...) {
    va_list args;
    va_start(args, formato);

    for (const char* p = formato; *p != '\0'; p++) {
        if (*p == '%' && *(p + 1) == 'd') {
            int val = va_arg(args, int);
            printf("%d", val);
            p++;
        } else if (*p == '%' && *(p + 1) == 's') {
            char* str = va_arg(args, char*);
            printf("%s", str);
            p++;
        } else {
            putchar(*p);
        }
    }
    va_end(args);
}

int main() {
    mi_printf("Entero: %d, Cadena: %s\n", 123, "Hola");
    return 0;
}