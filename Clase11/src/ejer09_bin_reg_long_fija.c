#include <stdio.h>
#include <string.h>

#define MAX_NOMBRE 50
#define MAX_REGISTROS 100

typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    float saldo;
    int activo;  // 1 = activo, 0 = eliminado lógico
} Cliente;

// Operación CREATE
void crear_cliente(FILE *f, Cliente *c) {
    fseek(f, 0, SEEK_END);  // Ir al final
    fwrite(c, sizeof(Cliente), 1, f);
}

// Operación READ por ID (acceso directo)
int leer_cliente(FILE *f, int id, Cliente *destino) {
    // Asumiendo que los IDs están en orden
    fseek(f, id * sizeof(Cliente), SEEK_SET);
    
    if (fread(destino, sizeof(Cliente), 1, f) != 1)
        return 0;
    
    return destino->activo;  // Solo devolver si no está eliminado
}

// Operación UPDATE
void actualizar_cliente(FILE *f, int id, Cliente *nuevo) {
    fseek(f, id * sizeof(Cliente), SEEK_SET);
    fwrite(nuevo, sizeof(Cliente), 1, f);
}

// Operación DELETE (eliminación lógica)
void eliminar_cliente_logico(FILE *f, int id) {
    Cliente c;
    fseek(f, id * sizeof(Cliente), SEEK_SET);
    
    if (fread(&c, sizeof(Cliente), 1, f) == 1) {
        c.activo = 0;
        fseek(f, -sizeof(Cliente), SEEK_CUR);
        fwrite(&c, sizeof(Cliente), 1, f);
    }
}

// Función auxiliar para limpiar el búfer de entrada
void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    // Abrir archivo en modo lectura/escritura binaria ("rb+")
    // Si no existe, se crea primero con "wb+"
    FILE *f = fopen("clientes.dat", "rb+");
    if (f == NULL) {
        f = fopen("clientes.dat", "wb+");
        if (f == NULL) {
            printf("Error al abrir o crear el archivo de datos.\n");
            return 1;
        }
    }

    int opcion, id_buscar;
    Cliente temp;

    do {
        printf("\n=== MENÚ GESTIÓN DE CLIENTES ===\n");
        printf("1. Crear Cliente (CREATE)\n");
        printf("2. Consultar Cliente por ID (READ)\n");
        printf("3. Actualizar Cliente (UPDATE)\n");
        printf("4. Eliminar Cliente (DELETE LOGIC)\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        
        if (scanf("%d", &opcion) != 1) {
            printf("Opción no válida.\n");
            limpiar_buffer();
            continue;
        }
        limpiar_buffer(); // Limpiar el salto de línea sobrante

        switch (opcion) {
            case 1:
                printf("\n--- Crear Nuevo Cliente ---\n");
                printf("Ingrese ID (entero): ");
                scanf("%d", &temp.id);
                limpiar_buffer();
                
                printf("Ingrese Nombre: ");
                fgets(temp.nombre, MAX_NOMBRE, stdin);
                temp.nombre[strcspn(temp.nombre, "\n")] = 0; // Quitar salto de línea
                
                printf("Ingrese Saldo: ");
                scanf("%f", &temp.saldo);
                temp.activo = 1; // Registro activo por defecto
                
                crear_cliente(f, &temp);
                printf("¡Cliente guardado con éxito!\n");
                break;

            case 2:
                printf("\n--- Consultar Cliente ---\n");
                printf("Ingrese el ID a buscar: ");
                scanf("%d", &id_buscar);
                
                if (leer_cliente(f, id_buscar, &temp)) {
                    printf("\n[Cliente Encontrado]\n");
                    printf("ID: %d\n", temp.id);
                    printf("Nombre: %s\n", temp.nombre);
                    printf("Saldo: %.2f\n", temp.saldo);
                } else {
                    printf("Cliente no encontrado o eliminado.\n");
                }
                break;

            case 3:
                printf("\n--- Actualizar Cliente ---\n");
                printf("Ingrese el ID del cliente a modificar: ");
                scanf("%d", &id_buscar);
                
                if (leer_cliente(f, id_buscar, &temp)) {
                    printf("Modificando los datos del ID %d...\n", id_buscar);
                    temp.id = id_buscar; // Mantiene el mismo ID
                    limpiar_buffer();
                    
                    printf("Nuevo Nombre: ");
                    fgets(temp.nombre, MAX_NOMBRE, stdin);
                    temp.nombre[strcspn(temp.nombre, "\n")] = 0;
                    
                    printf("Nuevo Saldo: ");
                    scanf("%f", &temp.saldo);
                    temp.activo = 1; 
                    
                    actualizar_cliente(f, id_buscar, &temp);
                    printf("¡Cliente actualizado con éxito!\n");
                } else {
                    printf("El cliente no existe o está inactivo. No se puede actualizar.\n");
                }
                break;

            case 4:
                printf("\n--- Eliminar Cliente (Lógico) ---\n");
                printf("Ingrese el ID del cliente a eliminar: ");
                scanf("%d", &id_buscar);
                
                if (leer_cliente(f, id_buscar, &temp)) {
                    eliminar_cliente_logico(f, id_buscar);
                    printf("¡Cliente marcado como eliminado con éxito!\n");
                } else {
                    printf("El cliente no existe o ya se encuentra eliminado.\n");
                }
                break;

            case 5:
                printf("Saliendo del sistema...\n");
                break;

            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 5);

    fclose(f);
    return 0;
}