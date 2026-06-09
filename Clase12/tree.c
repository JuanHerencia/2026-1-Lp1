#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/**************** global variables ****************/

const int TREE_KEY_NOT_FOUND = -1; // used by tree_find()

/**************** types ****************/
struct treenode {
  int key;		      // search key for this item
  int data;		      // data for this item
  struct treenode *left, *right; // children
};

/**************** functions ****************/

/**************** tree_new() ****************/
/* Create a new tree for the given key and data;
 * return NULL if error.
 */
struct treenode * tree_new(const int key, const int data)
{
  struct treenode *node = malloc(sizeof(struct treenode));

  if (node == NULL) { // si no hay memoria se devuelve nulo
    return NULL;
  } else {
    node->key = key;
    node->data = data;
    node->left = NULL;  // Punteros sin asignación SON NULOS!!!!
    node->right = NULL; // Punteros sin asignación SON NULOS!!!!
    return node;
  }
}

/**************** tree_insert() ****************/
/* Insert into the given tree, or NULL to start a new tree;
 * wherein the item is described by a key and some data,
 * and the tree is provided as a pointer to its root;
 * providing a NULL root creates a new tree and returns it.
 * If the key is already in the tree, its datum is update with new data;
 * the key should not be TREE_KEY_NOT_FOUND.
 */
struct treenode * tree_insert(struct treenode *node, const int key, const int data)
{
  if (node == NULL) { // Tiene memoria dicho nodo?
    // tree is empty; create and return a new node
    return tree_new(key, data);
  } else if (key == node->key) {
    // Si la clave ya existe, entonces actualizar la data
    node->data = data;
    return node;
  } else {
    // recursively insert either left or right,
    // and update our child pointers if needed
    if (key < node->key) {
      node->left = tree_insert(node->left, key, data);
    } else {
      node->right = tree_insert(node->right, key, data);
    }
    return node;
  }
}

/**************** tree_find() ****************/
/* Return the data associated with the given key;
 * return TREE_KEY_NOT_FOUND if key is not in tree.
 */
int 
tree_find(struct treenode *node, const int key)
{
  if (node == NULL) {
    return TREE_KEY_NOT_FOUND;
  } else if (key == node->key) {
    return node->data;
  } else {
    if (key < node->key) {
      return tree_find(node->left, key);
    } else {
      return tree_find(node->right, key);
    }
  }
}
