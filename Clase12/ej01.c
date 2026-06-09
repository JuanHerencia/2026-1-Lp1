#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/* Use a global variable to hold the root of tree;
 * it does not need to be global, in this simple example,
 * but here it serves an example of a global variable.
 * We normally try hard to avoid using globals.
 */
struct treenode *root; // puntero a un treenode

int main() 
{
  // some simple test code
  root = tree_insert(root, 3, 300);
  root = tree_insert(root, 4, 400);
  root = tree_insert(root, 1, 100);
  root = tree_insert(root, 5, 500);
  root = tree_insert(root, 6, 600);
  root = tree_insert(root, 2, 200);
  root = tree_insert(root, 8, 800);
  root = tree_insert(root, 7, 700);
  root = tree_insert(root, 0, -1);

  printf("Buscando la clave %d se retorna %d\n", 4, tree_find(root, 4));
  printf("Buscando la clave %d se retorna %d\n", 7, tree_find(root, 7));

  printf("Actualizar nodo %d con el valor 678\n", 6);
  root = tree_insert(root, 6, 678);
  printf("Buscar el nodo %d que retorna el valor %d\n", 6, tree_find(root, 6));

}