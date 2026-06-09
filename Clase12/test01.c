#include <stdio.h>
#include <stdlib.h>


// Definición de la estructura (nodo de árbol)
struct treenode {
  int key;		      // search key for this item
  int data;		      // data for this item
  struct treenode *left, *right; // children
  // Arbol de n-ramas
  //struct treenode **ramas; // 1ro crear cant de ramas, 2do dar direccion de treenodo a cada rama
};

// Donde se encuentran (en la pila o en el heap dentro de la memoria del programa)
struct treenode minodo; // como una variable no dinámica
struct treenode rama_izq, rama_der; // variables estáticas (tienen direccion de memoria)

int main()  
{
   minodo.key = 10;
   minodo.data = 100;
   // --- Izq
   rama_izq.key = -1;
   rama_izq.data = -10;
   // --- Der
   rama_der.key = 1010;
   rama_der.data = 2500;
   // Armado del árbol, partiendo del nodo minodo
   minodo.left = &rama_izq;
   minodo.right = &rama_der;


   printf("La direccion de memoria de minodo es %p\n", &minodo);
   printf("Valor de key es %d\n", minodo.key);
   printf("Valor de data es %d\n", minodo.data);
   printf("Acceso a las ramas del nodo 'minodo'\n");
   printf("Datos de la rama izquierda:\n");
   printf("Valor de key es %d\n", minodo.left->key);
   printf("Valor de data es %d\n", minodo.left->data);
   printf("Datos de la rama derecha:\n");
   printf("Valor de key es %d\n", minodo.right->key);
   printf("Valor de data es %d\n", minodo.right->data);

}