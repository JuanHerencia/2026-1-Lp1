#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char nombre[50];
    float salario;
} Empleado;

void escribir_empleado() {
    FILE *f = fopen("empleados.bin", "wb");
    if (!f) return;
    
    Empleado emp = {101, "Ana García", 2500.50};
    
    // Escribir estructura completa (¡cuidado con padding!)
    size_t escritos = fwrite(&emp, sizeof(Empleado), 1, f);
    
    if (escritos != 1) {
        printf("Error escribiendo empleado\n");
    }
    
    fclose(f);
}

void leer_empleado() {
    FILE *f = fopen("empleados.bin", "rb");
    if (!f) return;
    
    Empleado emp;
    
    if (fread(&emp, sizeof(Empleado), 1, f) == 1) {
        printf("ID: %d\n", emp.id);
        printf("Nombre: %s\n", emp.nombre);
        printf("Salario: %.2f\n", emp.salario);
    }
    
    fclose(f);
}

// Escritura de múltiples estructuras
void escribir_empleados(Empleado *lista, int n) {
    FILE *f = fopen("empleados.bin", "wb");
    if (!f) return;
    
    size_t escritos = fwrite(lista, sizeof(Empleado), n, f);
    printf("Escritos %zu de %d empleados\n", escritos, n);
    
    fclose(f);
}

int main()
{
    escribir_empleado();
    leer_empleado();
    /* 
    Empleado emps[] = {{125, "Abel Flores", 1990.00},{130, "Marco Marca", 127.50}};
    escribir_empleados(emps,2);
    */
    return 0;
}