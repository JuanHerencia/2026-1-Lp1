#include<stdio.h>

int main()  {

  // nombre_arr[ind_fila][ind_column]
  int n[3][2] = {{12,3},{10,56},{44,1}}; // con valor inicial
  /*
  // inicializar el arreglo
  for(size_t i = 0; i < 5; i++) {
    n[i] = 0;
  }
    */
  // Viendo el contenido del arreglo
  for(size_t f = 0; f < 3; f++) {
    for(size_t c = 0; c < 2; c++) {
      printf("%d\t", n[f][c]);
    }
    printf("\n");
  }
}