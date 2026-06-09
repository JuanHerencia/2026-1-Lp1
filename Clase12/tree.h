#ifndef __TREE_H
#define __TREE_H

/**************** global types ****************/
struct treenode;  // opaque to users of the module

/**************** functions ****************/

/* create a new tree for the given key and data;
 * return NULL if error.
 */
struct treenode *tree_new(const int key, int data);

/* insert into the given tree, or NULL to start a new tree;
 * wherein the item is described by a key and some data,
 * and the tree is provided as a pointer to its root;
 * providing a NULL root creates a new tree and returns it.
 * the key should not be TREE_KEY_NOT_FOUND.
 */
struct treenode *tree_insert(struct treenode *root, const int key, const int data);

/* return the data associated with the given key;
 * return TREE_KEY_NOT_FOUND if key is not in tree.
 */
int tree_find(struct treenode *root, const int key);
extern const int TREE_KEY_NOT_FOUND;

#endif // __TREE_H