#ifndef STUDENT_TREE_API_
#define STUDENT_TREE_API_
#include "balancedTreeAPI.h"

/*You may add anything to this .h file that you need to add to your tree ADT*/

//YOU MUST LEAVE THESE TYPEDEFS AS IS.
/**typedef for struct name*/
typedef struct BalancedBinTreeNode TreeNode;

/**typedef for struct name*/
typedef struct BalancedBinTree Tree;




/*complete the struct definitions.  You can change the existing parts if you wish.
*/
struct BalancedBinTree {
  //define your tree here.  You can change these if you need to but your tree must be abstract.
    TreeNode *root; ///< pointer to generic data that is to be stored in the tree
    int (*compareFP) (void *data1, void *data2); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
    void (*destroyFP) (void *data); ///< function pointer to a function to free a single pointer that is deleted from the tree
    void *(*copyFP)(void *toBeCopy); ///< function pointer to a function that copies pointer data

  };



struct BalancedBinTreeNode{
    void *data; ///< pointer to generic data that is to be stored in the heap
    TreeNode *left; ///< pointer to left tree node of current node. Null if empty.
    TreeNode *right; ///< pointer to right tree node of current node. Null if empty.

    //Add additional structure elements here
    // added parent
    int marked;
    TreeNode *parent;
    int height;
};

//add function prototypes as necessary
/**Function to recursively print a node from a self-balancing binary tree in preOrder
 *@param pointer to a TreeNode
 *@param printNodeFP pointer to a function that prints the data of theNode
 **/
void nodePreOrderPrint(TreeNode *theNode, void (*printNodeFP) (void *data));
/**Function to recursively print a node from a self-balancing binary tree in InOrder
 *@param pointer to a TreeNode
 *@param printNodeFP pointer to a function that prints the data of theNode
 **/
void nodeInOrderPrint(TreeNode *theNode, void (*printNodeFP) (void *data));
/**Function to recursively print a node from a self-balancing binary tree in postOrder
 *@param pointer to a TreeNode
 *@param printNodeFP pointer to a function that prints the data of theNode
 **/
void nodePostOrderPrint(TreeNode *theNode, void (*printNodeFP) (void *data));

void nodeDeleteAll(TreeNode *theNode, Tree *theTree);
void nodeHeightRecalculator(TreeNode *theNode);
void leftRotate(Tree *theTree,TreeNode* theNode);
void rightRotate(Tree *theTree,TreeNode* theNode);











#endif
