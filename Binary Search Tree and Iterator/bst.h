#ifndef __BST_H
#define __BST_H

#define TYPE int

struct BSTree;
struct BSTreeIterator;

/* BST Interface */
struct BSTree *initBSTree();
void BSTadd(struct BSTree *tree, TYPE newValue);
int  BSTcontains(struct BSTree *tree, TYPE value);
void BSTremove(struct BSTree *tree, TYPE value);
void printBSTree(struct BSTree *tree);
void deleteBSTree(struct BSTree *tree);

/* BST Iterator Interface -- To be Implemented */
struct BSTreeIterator* BSTIteratorCreate(struct BSTree* bst);
void BSTIteratorFree(struct BSTreeIterator* iter);
int BSTIteratorHasNext(struct BSTreeIterator* iter);
int BSTIteratorNext(struct BSTreeIterator* iter);


#endif
