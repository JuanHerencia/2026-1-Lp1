#include<stdio.h>

int main()  {

  //int n[5]; // declac de un arreglo de 5 elementos

  int n[5] = {25,36,4,89,7}; // con valor inicial
  /*
  // inicializar el arreglo
  for(size_t i = 0; i < 5; i++) {
    n[i] = 0;
  }
    */
  // Viendo el contenido del arreglo
  for(size_t i = 0; i < 8; i++) {
    printf("%d\n", n[i]);
  }
}