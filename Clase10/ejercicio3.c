#include<stdio.h>
#include<string.h>
#include <stdlib.h>
// Estructuras
// Definición/creación de una estructura
struct Alumno {
    int codigo;
    char nombre[20];
    /*
    struct Alumno *next;  // enlace simple
    struct Alumno *prev;  // enlace doble
    */
};

// Cabecera
void mostrar(struct Alumno *aa);

int main()
{
   // Crear un alumno
   struct Alumno a1;

   // Inicializar a1
   a1.codigo = 1234;
   strcpy(a1.nombre, "Ana");

   // La salida
   printf("Codigo    : %d\n", a1.codigo);
   printf("Nombre    : %s\n", a1.nombre);

   struct Alumno alumnos[2] = {{1111, "Abel"}, {2222, "Alex"}};
   printf("Lista de alumnos\n");
   for(int i = 0; i < 2; i++) {
      printf("Codigo    : %d\n", alumnos[i].codigo);
      printf("Nombre    : %s\n", alumnos[i].nombre);
   }
   
   struct Alumno *a;

   a = &alumnos[0];  // toma la dirección de una estructura
   printf("Contenido de *a:\n");
   printf("Codigo    : %d\n", a->codigo);
   printf("Nombre    : %s\n", a->nombre);

   // Crear información
   struct Alumno *b;  // aqui *b no tiene espacio de memoria
                      // no apunta a nada
   // Reservar memoria para un alumno       
   // Si no hay memoria malloc delvuelve NULL            
   b = (struct Alumno*)malloc(1*sizeof(struct Alumno)); 
   if(b != NULL) // verificar si hay memoria
   {
      b->codigo = 9999;
      strcpy(b->nombre, "Ulises");
   }

   mostrar(b);
}

// Mostrar un alumno
void mostrar(struct Alumno *aa) 
{
    printf("\nCodigo    : %d\n", aa->codigo);
   printf("Nombre    : %s\n", aa->nombre);
}