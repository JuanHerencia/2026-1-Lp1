#include<stdio.h>
#define NULO 0

int main()  {
  int a = 10; // variable fija
  // &nombre_var_fija  es dirección de memoria de variable fija
  printf("a = %d y su direccion es %p\n",a,&a);

  int *ptr; // variable puntero
  // nombre_var_ptr es direccion de memoria de variable puntero
  // *nombre_var_ptr es valor o contenido de variable puntero
  printf("Puntero NO inicializado:\n");
  printf("*ptr = %d y su direccion es %p\n",*ptr,ptr);
  ptr = 0; // inicialización de un puntero
  printf("Puntero inicializado:\n");
  if(ptr != NULO) {
    printf("*ptr = %d y su direccion es %p\n",*ptr,ptr);
  } else {
    printf("Puntero nulo, no se puede mostrar\n");
  }  

  // Apuntar a la variable a
  ptr = &a;  // se opera entre direcciones de memoria
  if(ptr != NULO) {
    printf("*ptr = %d y su direccion es %p\n",*ptr,ptr);
  } else {
    printf("Puntero nulo, no se puede mostrar");
  }

  // Cambiar el valor de a a través del puntero
  *ptr = 999; // modificar el valor de la memoria del puntero
  // la variable a ha sido modificada
  printf("a = %d y su direccion es %p\n",a,&a); 
}