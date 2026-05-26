#include <stdio.h>

struct Fecha {
    int dia, mes, anio;
};

struct Empleado {
    char nombre[50];
    float salario;
    struct Fecha contratacion;  // Anidamiento
};

int main() {
    struct Empleado emp = {"Juan Perez", 2500.0, {15, 3, 2020}};
    
    printf("Empleado: %s\n", emp.nombre);
    printf("Contratado: %d/%d/%d\n", 
           emp.contratacion.dia, 
           emp.contratacion.mes, 
           emp.contratacion.anio);
    
    return 0;
}