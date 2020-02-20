#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "linkedListStack.h"

struct node{
   TYPE value;
   struct node *left;
   struct node *right;
};

struct BSTree{
   struct node *root;
   int size;
};

/*
 * This is the structure you will use to create an in-order BST iterator.  It
 * is up to you how to define this structure.
 */

struct BSTreeIterator{

	struct node* current_node;

	struct BSTree* bst;

	struct LinkedList* stack;

	
};


struct BSTree*  initBSTree()
{
    struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
    assert(tree != 0);
    tree->size  = 0;
    tree->root = 0;
    return tree;
}


struct node *BSTnodeAdd(struct node *root, TYPE newValue)
{
 /* End condition */
   if (!root)
   {
       root = malloc(sizeof(struct node));
       assert(root);
       root -> value = newValue;
       root -> left = 0;
       root -> right = 0;
       return root;
   }
 /* 2: Recursion */
   if (root -> value > newValue)
   {
       /* Go left */
       root -> left = BSTnodeAdd(root->left, newValue);
       /* root -> left = root -> left; */
   }
   if (root -> value < newValue)
   {  /* Go right */
       root -> right = BSTnodeAdd(root->right, newValue);
   }

   if (root -> value == newValue)
   {
       root = root;
      /* Several options: 1) Throw error (extreme); 2) Keep the tree as-is; 3) Define to either go left or right in this case */
   }
/* 3: Return value */
   return root;
}

void BSTAdd(struct BSTree *tree, TYPE newValue) {
     tree->root = BSTnodeAdd(tree->root, newValue); 
     tree->size++; 
 }

TYPE _leftMostChild (struct node * current) { 
     assert(current); 
  /* 1: end condition */
     if (!current -> left)
         return current -> value;
  /* 2: recursion */
  /* 3: return value */
     return _leftMostChild(current -> left);
}

struct node * _removeLeftMostChild (struct node *current) { 
/* 1: end condition */
   if (! current -> left)
   {
       struct node *new_left;
       new_left = current -> right;
       free(current);
       return new_left;
   }

/* 2: recursion */
    current -> left = _removeLeftMostChild(current -> left);
/* 3: return value */
    return current;
}

struct node * _BSTNodeRemove (struct node * current, TYPE d) { 
    
/* 1: End condition:
   Suppose we are already at the node we want to remove */
   if ( current -> value == d)
   {
/* 1) If current has a right child */
/* Replace it with the leftmost child on right side */
       if (current -> right)
       {
           current -> value = _leftMostChild(current -> right);
           current -> right = _removeLeftMostChild(current -> right);
           return current;
       }
/* 2) If current does not have a right child */
       else
       {
           struct node *temp = current -> left;
           free(current);
           return temp;
       }
   }
/* 2: Recursion */
   if (current -> value > d)
       current -> left = _BSTNodeRemove(current -> left, d);
   if (current -> value < d)
       current -> right = _BSTNodeRemove(current -> right, d);
/* 3: return value */
   return current;
}

struct BSTree *buildBSTree() {
    struct BSTree *tree	= initBSTree();		
		
    /*Create value of the type of data that you want to store*/
	
    /*add the values to BST*/
	/* This tree can be found in Slide 24 of the BST slides */
    BSTAdd(tree, 50);
    BSTAdd(tree, 25);
    BSTAdd(tree, 75);
    BSTAdd(tree, 35);
    BSTAdd(tree, 20);
    BSTAdd(tree, 60);
    BSTAdd(tree, 65);
    BSTAdd(tree, 45);
    BSTAdd(tree, 30);
    BSTAdd(tree, 85);
    BSTAdd(tree, 80);
    
    return tree;
}






/***************************************** START OF HOMEWORK FUNCTIONS**************************************************************/






/*
  This function recursively frees all the nodes of a binary search tree
  param: node  the root node of the tree to be freed
  pre: none
  post: node and all descendants are deallocated
*/

void _freeBST(struct node *node)
{

	if(node){	//if node is not null delete its subtrees
	
		if(node->left){		//if there is a left subtree free it 
			_freeBST(node->left);

			node->left = 0;
		}
			
	
		if(node->right){		//if there is a right subtree free it
			_freeBST(node->right);

			node->right = 0;
		}

	}
		

	free(node);	//free current node
	node = 0;

	

}


void deleteBSTree(struct BSTree *bstree)
{
    _freeBST(bstree->root);
    bstree->root = 0;
    free(bstree);
}

/*
  This function recursively print all nodes in the tree by completing an in-order
  traversal. Please print the tree in this format:
  
  for every subtree, start it with a (, and end it with a ), in the middle, print the subtree values one-by-one.
  
  e.g.,a tree with just root = 50 should be (50)
  a tree with root = 50, root->left = 30 and root->right = 70 should be ((30) 50 (70))
  a tree with root = 50, root->left = 30, root->left->left = 20, root -> left->right = 40, root->right = 70 should be (((20) 30 (40)) 50 (70))

  param: node: the root node of the tree to be printed
  pre: none
  post: the tree is printed */

void _printNode(struct node *node) {

	if(node){	//if the node is not null we can print it

		printf("( ");	//start subtree
		
		_printNode(node->left);		//print the left subtree first
		printf(" %d ", node->value);	//print the cuurent node next
		_printNode(node->right);	//print it right subtree last

		printf(" )");		//end subtree
	}

}




void printBSTree(struct BSTree *tree) {
    if (tree == 0)
	return;	 
    _printNode(tree->root);	 
    printf("\n");
}



/*
 * This function should allocate and initialize a new in-order BST iterator
 * given a specific BST over which to iterate.
 *
 * Params:
 *   bst - the BST over which to perform in-order iteration.  May not be NULL.
 *
 * Return:
 *   Should return a pointer to a new in-order BST iterator, initialized so
 *   that the first value returned by bst_iterator_next() is the first in-order
 *   value in bst (i.e. the leftmost value in the tree).
 */
struct BSTreeIterator* BSTIteratorCreate(struct BSTree* tree) {

	
	assert(tree);	//make sure tree is not NULL

	struct BSTreeIterator* iter = malloc(sizeof(struct BSTreeIterator));

	iter->bst = tree;



	iter->stack = createLinkedList();	//create stack	

	iter->current_node = tree->root;	//start at root

	pushLinkedList(iter->stack,iter->current_node);		//add root at the bottom of the stack, iter->current node should always be the same node as the top of the stack

	if(iter->current_node){		//if the root is not NULL we can go on to find leftmost node

		while(iter->current_node->left){	//while there is still a left node

			iter->current_node = iter->current_node->left;		//move current node to its left node
			pushLinkedList(iter->stack,iter->current_node);		//add this node to stack
		}

		iter->current_node = iter->current_node->left;		//in order for bst_it_next to return the left most value first the current node must be the NULL left pointer

		pushLinkedList(iter->stack,iter->current_node);		//add the NULL left pointer of the leftmost node to the stack



	}

	return iter;


	//after the iterator is initilized the stack will have all leftmost subtree roots stacked, with the root on the bottom and the leftmost node on top
	//in the euler walk around the tree this is the first time each of the nodes have been visited
}

/*
 * This function should free all memory allocated to a BST iterator.
 *
 * Params:
 *   iter - the iterator whose memory is to be freed.  May not be NULL.
 */
void BSTIteratorFree(struct BSTreeIterator* iter) {

	assert(iter);

	deleteLinkedList(iter->stack);		//free stack memory

	free(iter);
}


/*
 * This function should return 1 if there is at least one more node to visit
 * in the in-order iteration of the BST represented by a given iterator.  If
 * there are no more nodes to visit, it should return 0.
 *
 * Params:
 *   iter - the iterator to be checked for more values.  May not be NULL.
 */
int BSTIteratorHasNext(struct BSTreeIterator* iter) {

	assert(iter);

	popLinkedList(iter->stack);

	int check = !isEmptyLinkedList(iter->stack);		//if the stack is empty after its top has been poped then there are no more nodes to visit

	pushLinkedList(iter->stack,iter->current_node);		//re add the pushed top to the stack

	return check;


}


/*
 * This function should return the next value in the in-order iteration of the
 * BST represented by a given iterator.
 *
 * Params:
 *   iter - the iterator whose next value is to be returned.  May not be NULL
 *     and must have at least one more value to be returned.
 */
int BSTIteratorNext(struct BSTreeIterator* iter) {


	assert(iter);

	

	popLinkedList(iter->stack);	//pop the current node from stack, if this is not the null left pointer of the leftmost node then 	
					//this will be the third time this node has been the tree has been visited in the euler walk

	iter->current_node = topLinkedList(iter->stack);	//move current node to the top of the stack
								//this will be the second time that a node in the stack has been viseted in the euler 
								//walk, so we can return its value, for an in-order traversal

	int val = iter->current_node->value;		//return the value stored at the top of the stack




	if( iter->current_node->right ){	//if the current node has values to the right they will get added to stack next

	
	
	
		popLinkedList(iter->stack);	//pop the top of the stack, this is the third time this node has been visited in the euler walk

	
		iter->current_node = iter->current_node->right;	//move the current node to the right subtree, this is the first time this node is touched in the E.W.

		pushLinkedList( iter->stack , iter->current_node);	//add the current node to top of stack

		
		
		
		
		while(iter->current_node->left){	//this loop puts the left node of the right subtree on top of the stack, until the leftmost node of the subtree is on top
							//this will be these nodes first visit in the euler walk

			iter->current_node = iter->current_node->left;

			pushLinkedList(iter->stack, iter->current_node);

		

		}

		iter->current_node = iter->current_node->left;		//to return the leftmost subtree when this funct is called next , the current node must be the NULL left node

		pushLinkedList(iter->stack,iter->current_node);




	}

	return val;



}




/**************************************************************** END OF HOMEWORK PROBLEMS    *************************************/




void testIterator(int tree_num) {
    struct BSTree *tree;
    if (tree_num == 1)
        tree = buildBSTree();
	if (tree_num == 2)
		tree = initBSTree();
	if (tree_num == 3)
	{
		tree = initBSTree();
		BSTAdd(tree, 10);
	}
	if (tree_num == 4)
	{
		tree = initBSTree();
		BSTAdd(tree, 10);
		BSTAdd(tree, 5);
	}

	
    struct BSTreeIterator* iter = BSTIteratorCreate(tree);
    printf("\n== BST contents (in order):");
    while (BSTIteratorHasNext(iter)) {
       int val = BSTIteratorNext(iter);
      printf(" %4d", val);
    }
    printf("\n");
   
	/* Result from not using the iterator */
    printf("Baseline comparison:\n");
	printBSTree(tree);
	   BSTIteratorFree(iter);
	deleteBSTree(tree);
}

/*

  Main function for testing different functions of the Assignment #3.

*/

int main(int argc, char *argv[]){	
	
	/* Simple cases are usually likely to be corner cases, hence besides a normal tree, we should also test with simple cases */
	
	/* Test #1: a normal tree */
    testIterator(1);
	/* Test #2: an empty tree */
 testIterator(2);
	/* Test #3: a tree with only root */
	testIterator(3);
	/* Test #4: a tree with root and a left child */
	testIterator(4);
	
    return 0;
}

