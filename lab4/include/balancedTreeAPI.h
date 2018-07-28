/**
 * @file balancedTreeAPI.h
 * @author Michael Ellis
 * @date April 2017
 * @brief File containing the functions that communicate with a self-balancing binary tree.
 */

#ifndef BAL_TREE_API_
#define BAL_TREE_API_

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
#include "tree.h"

/*-----------------------------
CHANGE NOTHING IN THIS FILE!!!!
-------------------------------*/




/**This function returns a pointer to a binary tree.  You must send pointers to the compare and destroy functions when you create the tree.
 *@param compareFP function pointer to allow for comparison between two generic data types
 *@param destroyFP function pointer to allow for pointer deletion. 
 *@param copyFP function pointer to a function that copies pointer data to a new pointer.
 *@return If successful, returns a pointer to a binary tree. Returns null if the memory allocation fails.
 **/
Tree *createBalancedBinTree(int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *toBeDeleted),void *(*copyFP)(void *toBeCopy));

/**This function creates a tree node for a self-balancing binary tree.
 *@param data pointer to data that is to be added to a self-balancing binary tree.
 **/
TreeNode *createBalancedBinNode(void *data);

/**This function destroys a binary tree and all data that is in the tree
 *when destroy is called.
 *@param toBeDeleted pointer to binary tree created via createBalancedBinTree
 **/
void destroyBalancedBinTree(Tree *toBeDeleted);

/**Function to insert a node into a self-balancing binary tree.
 *@param theTree pointer to a self-balancing binary tree
 *@param toBeInserted pointer to generic data that is to be inserted into the self-balancing binary tree
 **/
void treeInsertNode(Tree *theTree, void *toBeInserted);

/**Function to delete a node from a self-balancing binary tree.
 *@param theTree pointer to a self-balancing binary tree
 *@param toBeDeleted pointer to generic data that is to be deleted from the self-balancing binary tree
 **/
void treeDeleteNode(Tree *theTree, void *toBeDeleted);

/**Function to determine if a binary tree is empty.
 *@param theTree pointer to a self-balancing binary tree
 *@return If tree is empty, return 1. Otherwise, return 0.
 **/
int treeIsEmpty(Tree *theTree);

/**Function to determine if a binary tree node has two children.
 *@param root pointer to a self-balancing binary tree's root
 *@return If tree is empty, or does not exist, return 1. Otherwise, return 0.
 **/
int treeHasTwoChildren(TreeNode *root);

/**Function to return a given value in the tree, dependant on the compare function pointer parameters.
 *Compares nodes, until compare function returns zero, or the tree is exhausted.
 *@param theTree pointer to a self-balancing binary tree's root
 *@return pointer to the data found. If tree is empty or data is not found, return NULL.
 **/
void *treeFindNode(Tree *theTree, void *data);

/**Function to return the smallest value of a tree, dependant on the compare function pointer parameters.
 *@param theTree pointer to a self-balancing binary tree's root
 *@return pointer to the min found. If tree is empty, return NULL.
 **/
void *treeFindMin(Tree *theTree);

/**Function to return the largest value of a tree, dependant on the compare function pointer parameters.
 *@param theTree pointer to a self-balancing binary tree's root
 *@return pointer to the maximum value  found. If tree is empty, return NULL.
 **/
void *treeFindMax(Tree *theTree);

/**function to print a tree in-order. EG 
 *              A
 *            /    \
 *          B       C
 *         / \     / \
 *        D   F   G   E
 *would print nodes thusly: D->B->F->A->G->C->E
 *@param theTree pointer to a self-balancing binary tree
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data));

/**Function to print a tree pre-order. EG 
 *              A
 *            /   \
 *          B       C
 *         / \     / \
 *        D   F   G   E
 *would print nodes thusly: A->B->D->F->C->G->E
 *@param theTree pointer to a self-balancing binary tree
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data));

/**Function to print a tree in post-order. EG 
 *              A
 *            /   \
 *          B       C
 *         / \     / \
 *        D   F   G   E
 *would print nodes thusly: D->F->B->G->C->E->A
 *@param theTree pointer to a self-balancing binary tree's root
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data));

#endif
