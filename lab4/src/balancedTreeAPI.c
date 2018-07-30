#include <stdio.h>
#include <stdlib.h>
#include "../include/balancedTreeAPI.h"

Tree *createBalancedBinTree(int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *toBeDeleted),void *(*copyFP)(void *toBeCopy))
{
  Tree *tree = malloc(sizeof(Tree)*1);
  tree->root = NULL;
  tree->destroyFP = destroyFP;
  tree->copyFP = copyFP;
  tree->compareFP = compareFP;
  return tree;
}

TreeNode *createBalancedBinNode(void *data)
{
  TreeNode *newNode = malloc(sizeof(TreeNode)*1);

  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->parent = NULL;
  newNode->height = 0;

  return newNode;
}

void treeInsertNode(Tree *theTree, void *toBeInserted)
{
  TreeNode *nodeToInsert = createBalancedBinNode(toBeInserted);
  if (theTree->root == NULL)
  {
    theTree->root = nodeToInsert;
    return;
  }
  TreeNode *placeHolder=theTree->root;
  TreeNode *parentHolder = NULL;
  while(placeHolder!=NULL)
  {
    if(theTree->compareFP(nodeToInsert->data,placeHolder->data)<=0)
    {
      parentHolder = placeHolder;
      placeHolder= placeHolder->left;
    }
    else
    {
      parentHolder = placeHolder;
      placeHolder = placeHolder->right;
    }

  }
  if(theTree->compareFP(nodeToInsert->data,parentHolder->data)<=0)
  {
    parentHolder->left = nodeToInsert;
    nodeToInsert->parent = parentHolder;
  }
  else
  {
    parentHolder->right = nodeToInsert;
    nodeToInsert->parent = parentHolder;
  }
  placeHolder= nodeToInsert;
  while(parentHolder!=NULL)
  {
    if(placeHolder->height==parentHolder->height)
    {
      parentHolder->height= parentHolder->height+1;
    }
    else
    {
      break;
    }
    placeHolder = parentHolder;
    parentHolder = parentHolder->parent;
  }


  //rebalance tree after insert
  placeHolder=nodeToInsert;
  //step 1:check all parents to find an unbalanced node
  int leftHeight=0;
  int rightHeight=0;
  TreeNode *NodeToBeBalanced=NULL;

  while(placeHolder->parent!=NULL)
  {
    if(placeHolder->parent->left!=NULL)
    {
      leftHeight=placeHolder->parent->left->height;
    }
    else
    {
      leftHeight = -1;
    }
    if(placeHolder->parent->right!=NULL)
    {
      rightHeight=placeHolder->parent->right->height;
    }
    else
    {
      rightHeight = -1;
    }
    if(abs(leftHeight-rightHeight)>1)
    {
      NodeToBeBalanced=placeHolder->parent;
      break;
    }
    placeHolder=placeHolder->parent;
  }
  //checking if tree needs to be balanced
  if(NodeToBeBalanced!=NULL)
  {
    printf("\nbalance = %d left=%d right=%d",*(int*)NodeToBeBalanced->data,leftHeight,rightHeight);
    if(leftHeight>rightHeight) //case left
    {
      if(NodeToBeBalanced->left->left!=NULL)
      {
        if(NodeToBeBalanced->left->right!=NULL)
        {
          if(NodeToBeBalanced->left->left->height > NodeToBeBalanced->left->right->height)  //case left left
          {
            rightRotate(theTree,NodeToBeBalanced);
          }
          else  // case left right
          {
            leftRotate(theTree,NodeToBeBalanced->left);
            rightRotate(theTree,NodeToBeBalanced);
          }
        }
        else //left left
        {
          rightRotate(theTree,NodeToBeBalanced);
        }
      }
      else //left right
      {
        leftRotate(theTree,NodeToBeBalanced->left);
        rightRotate(theTree,NodeToBeBalanced);
      }
    }
    else //case right
    {
      if(NodeToBeBalanced->right->right!=NULL)
      {
        if(NodeToBeBalanced->right->left!=NULL)
        {
          if(NodeToBeBalanced->right->right->height > NodeToBeBalanced->right->left->height)  //case right right
          {
            leftRotate(theTree,NodeToBeBalanced);
          }
          else  // case right left
          {
            rightRotate(theTree,NodeToBeBalanced->right);
            leftRotate(theTree,NodeToBeBalanced);
          }
        }
        else //right right
        {
          leftRotate(theTree,NodeToBeBalanced);
        }
      }
      else //right left
      {
        rightRotate(theTree,NodeToBeBalanced->right);
        leftRotate(theTree,NodeToBeBalanced);
      }
    }
    //recalculate heights after balance
    nodeHeightRecalculator(theTree->root);
  }
  return;
}

void treeDeleteNode(Tree *theTree, void *toBeDeleted)
{
  TreeNode *placeholder = treeFindNode(theTree,toBeDeleted);
  TreeNode *findLeft = NULL;
  TreeNode *findLeftParent = NULL;
  TreeNode *parentOfDeleted = NULL;
  theTree->destroyFP(placeholder->data);
  //checking for no children
  if (placeholder->left==NULL && placeholder->right==NULL)
  {
    if (placeholder->parent!=NULL)
    {
      if (placeholder == placeholder->parent->left)
      {
        placeholder->parent->left = NULL;
      }
      else
      {
        placeholder->parent->right = NULL;
      }
    }
    else
    {
      theTree->root = NULL; //setting root to null if no parent of node to be deleted
    }

    parentOfDeleted = placeholder->parent;
    free(placeholder);
  }
  //check for right root only
  else if(placeholder->left==NULL)
  {
    if (placeholder->parent!=NULL)
    {
      if (placeholder == placeholder->parent->left)
      {
        placeholder->parent->left = placeholder->right;
        placeholder->right->parent = placeholder->parent;
        parentOfDeleted=placeholder->parent;
        free(placeholder);
      }
      else
      {
        placeholder->parent->right = placeholder->right;
        placeholder->right->parent = placeholder->parent;
        parentOfDeleted=placeholder->parent;
        free(placeholder);
      }
    }
    else
    {
      theTree->root = placeholder->right; //setting root to right child if no parent of node to be deleted
      parentOfDeleted = NULL;
      free(placeholder);
    }
  }
  //check for left root only
  else if(placeholder->right==NULL)
  {
    if (placeholder->parent!=NULL)
    {
      if (placeholder == placeholder->parent->left)
      {
        placeholder->parent->left = placeholder->left;
        placeholder->left->parent = placeholder->parent;
        parentOfDeleted=placeholder->parent;
        free(placeholder);
      }
      else
      {
        placeholder->parent->right = placeholder->left;
        placeholder->left->parent = placeholder->parent;
        parentOfDeleted=placeholder->parent;
        free(placeholder);
      }
    }
    else
    {
      theTree->root = placeholder->left; //setting root to left child if no parent of node to be deleted
      parentOfDeleted = NULL;
      free(placeholder);
    }
  }
  //two children
  else
  {
    //find the smallest value on the right branch of the node to be deleted to be used to replace the node to be deleted data
    findLeftParent= placeholder->right;
    findLeft = placeholder->right;
    while(findLeft!=NULL)
    {
      findLeftParent=findLeft;
      findLeft= findLeft->left;
    }
    placeholder->data=findLeftParent->data;
    parentOfDeleted=findLeftParent->parent;
    if(findLeftParent->right!=NULL)
    {
      findLeftParent->parent->left=findLeftParent->right;
      findLeftParent->right->parent=findLeftParent->parent;
    }
    else
    {
      findLeftParent->parent->left=NULL;
    }
    theTree->destroyFP(findLeftParent->data);

    free(findLeftParent);
  }
  nodeHeightRecalculator(theTree->root);

  //rebalance after delete
  //parentofdeleted is where we start walking up to find unbalanced nodes

  //step 1:check all parents to find an unbalanced node
  int leftHeight=0;
  int rightHeight=0;
  TreeNode *NodeToBeBalanced=NULL;

  while(parentOfDeleted->parent!=NULL)
  {
    if(parentOfDeleted->parent->left!=NULL)
    {
      leftHeight=parentOfDeleted->parent->left->height;
    }
    else
    {
      leftHeight = -1;
    }
    if(parentOfDeleted->parent->right!=NULL)
    {
      rightHeight=parentOfDeleted->parent->right->height;
    }
    else
    {
      rightHeight = -1;
    }
    if(abs(leftHeight-rightHeight)>1)
    {
      NodeToBeBalanced=parentOfDeleted->parent;
      break;
    }
    parentOfDeleted=parentOfDeleted->parent;
  }
  //checking if tree needs to be balanced
  if(NodeToBeBalanced!=NULL)
  {
    printf("\nbalance = %d left=%d right=%d",*(int*)NodeToBeBalanced->data,leftHeight,rightHeight);
    if(leftHeight>rightHeight) //case left
    {
      if(NodeToBeBalanced->left->left!=NULL)
      {
        if(NodeToBeBalanced->left->right!=NULL)
        {
          if(NodeToBeBalanced->left->left->height > NodeToBeBalanced->left->right->height)  //case left left
          {
            rightRotate(theTree,NodeToBeBalanced);
          }
          else  // case left right
          {
            leftRotate(theTree,NodeToBeBalanced->left);
            rightRotate(theTree,NodeToBeBalanced);
          }
        }
        else //left left
        {
          rightRotate(theTree,NodeToBeBalanced);
        }
      }
      else //left right
      {
        leftRotate(theTree,NodeToBeBalanced->left);
        rightRotate(theTree,NodeToBeBalanced);
      }
    }
    else //case right
    {
      if(NodeToBeBalanced->right->right!=NULL)
      {
        if(NodeToBeBalanced->right->left!=NULL)
        {
          if(NodeToBeBalanced->right->right->height > NodeToBeBalanced->right->left->height)  //case right right
          {
            leftRotate(theTree,NodeToBeBalanced);
          }
          else  // case right left
          {
            rightRotate(theTree,NodeToBeBalanced->right);
            leftRotate(theTree,NodeToBeBalanced);
          }
        }
        else //right right
        {
          leftRotate(theTree,NodeToBeBalanced);
        }
      }
      else //right left
      {
        rightRotate(theTree,NodeToBeBalanced->right);
        leftRotate(theTree,NodeToBeBalanced);
      }
    }
    //recalculate heights after balance
    nodeHeightRecalculator(theTree->root);
  }


  return;
}

void *treeFindMin(Tree *theTree)
{
  if (treeIsEmpty(theTree)==1)
  {
    return NULL;
  }
  TreeNode *parentholder = NULL;
  TreeNode *currentNode = theTree->root;
  while(currentNode!=NULL)
  {
    parentholder = currentNode;
    currentNode = currentNode->left;
  }
  return parentholder->data;

}

void *treeFindMax(Tree *theTree)
{
  if (treeIsEmpty(theTree)==1)
  {
    return NULL;
  }
  TreeNode *parentholder = NULL;
  TreeNode *currentNode = theTree->root;
  while(currentNode!=NULL)
  {
    parentholder = currentNode;
    currentNode = currentNode->right;
  }
  return parentholder->data;

}
void *treeFindNode(Tree *theTree, void *data)
{
  TreeNode *placeHolder = theTree->root;
  while(placeHolder!=NULL)
  {
    if(theTree->compareFP(data,placeHolder->data)<0)
    {
      placeHolder= placeHolder->left;
    }
    else if(theTree->compareFP(data,placeHolder->data)>0)
    {
      placeHolder = placeHolder->right;
    }
    else
    {
      return placeHolder;
    }

  }
  return NULL;
}

int treeHasTwoChildren(TreeNode *root)
{
  if(root->left!=NULL && root->right!=NULL)
  {
    return 0;
  }
  return 1;
}

void destroyBalancedBinTree(Tree *toBeDeleted)
{
  nodeDeleteAll(toBeDeleted->root,toBeDeleted);
  free(toBeDeleted);
  return;
}



void rightRotate(Tree *theTree,TreeNode* theNode)
{
  TreeNode *placeholder = NULL;

  if (theNode->left !=NULL)
  {

    if (theNode->parent==NULL)//if this is the root node
    {
      placeholder=theNode->left; //saving left so its not overwritten
      theNode->left=theNode->left->right;
      if(theNode->left!=NULL)
      {
        theNode->left->parent=theNode;
      }
      theNode->parent = placeholder;
      placeholder->right= theNode;
      theTree->root = placeholder;
      placeholder->parent = NULL;
    }
    else
    {
      placeholder=theNode->left; //saving left so its not overwritten
      theNode->left=theNode->left->right;
      if(theNode->left!=NULL)
      {
        theNode->left->parent=theNode;
      }
      placeholder->parent =theNode->parent;
      placeholder->right=theNode;
      theNode->parent = placeholder;
      if(theTree->compareFP(placeholder->data,placeholder->parent->data)>0)
      {
        placeholder->parent->right=placeholder;
      }
      else
      {
        placeholder->parent->left=placeholder;
      }
    }
  }
  return;
}

void leftRotate(Tree *theTree,TreeNode* theNode)
{
  TreeNode *placeholder = NULL;

  if (theNode->right !=NULL)
  {

    if (theNode->parent==NULL)//if this is the root node
    {
      placeholder=theNode->right; //saving right so its not overwritten
      theNode->right=theNode->right->left;
      if(theNode->right!=NULL)
      {
        theNode->right->parent=theNode;
      }
      theNode->parent = placeholder;
      placeholder->left= theNode;
      theTree->root = placeholder;
      placeholder->parent = NULL;
    }
    else
    {
      placeholder=theNode->right; //saving right so its not overwritten
      theNode->right=theNode->right->left;
      if(theNode->right!=NULL)
      {
        theNode->right->parent=theNode;
      }
      placeholder->parent =theNode->parent;
      placeholder->left=theNode;
      theNode->parent = placeholder;
      if(theTree->compareFP(placeholder->data,placeholder->parent->data)>0)
      {
        placeholder->parent->right=placeholder;
      }
      else
      {
        placeholder->parent->left=placeholder;
      }
    }
  }
  return;
}



void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
  printf("\nPreOrderPrint:\t");
  if (theTree->root==NULL)
  {
    return;
  }
  nodePreOrderPrint(theTree->root,printNodeFP);
  return;

}

void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
  printf("\nPostOrderPrint:\t");
  if (theTree->root==NULL)
  {
    return;
  }
  nodePostOrderPrint(theTree->root,printNodeFP);
  return;

}

void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
  printf("\nInOrderPrint:\t");
  if (theTree->root==NULL)
  {
    return;
  }
  nodeInOrderPrint(theTree->root,printNodeFP);
  return;

}

void nodeInOrderPrint(TreeNode *theNode, void (*printNodeFP) (void *data))
{
  if (theNode == NULL)
  {
    return;
  }

  nodeInOrderPrint(theNode->left, printNodeFP);
  printNodeFP(theNode->data);
  nodeInOrderPrint(theNode->right, printNodeFP);

  return;
}

int treeIsEmpty(Tree *theTree)
{
  if (theTree->root==NULL)
  {
    return 1;
  }
  return 0;
}


void nodePreOrderPrint(TreeNode *theNode, void (*printNodeFP) (void *data))
{
  if (theNode == NULL)
  {
    return;
  }
  printNodeFP(theNode->data);

  nodePreOrderPrint(theNode->left, printNodeFP);
  nodePreOrderPrint(theNode->right, printNodeFP);
  return;
}

void nodePostOrderPrint(TreeNode *theNode, void (*printNodeFP) (void *data))
{
  if (theNode == NULL)
  {
    return;
  }

  nodePostOrderPrint(theNode->left, printNodeFP);
  nodePostOrderPrint(theNode->right, printNodeFP);
  printNodeFP(theNode->data);

  return;
}

void nodeDeleteAll(TreeNode *theNode, Tree *theTree)
{
  if (theNode == NULL)
  {
    return;
  }

  nodeDeleteAll(theNode->left, theTree);
  nodeDeleteAll(theNode->right, theTree);
  theTree->destroyFP(theNode->data);
  free(theNode);
  return;
}

void nodeHeightRecalculator(TreeNode *theNode)
{
  if (theNode == NULL)
  {
    return;
  }
  nodeHeightRecalculator(theNode->left);
  nodeHeightRecalculator(theNode->right);
  if (theNode->left==NULL && theNode->right==NULL)
  {
    theNode->height = 0;
  }
  else if(theNode->left==NULL)
  {
    theNode->height= theNode->right->height+1;
  }
  else if(theNode->right==NULL)
  {
    theNode->height= theNode->left->height+1;
  }
  else
  {
    if(theNode->left->height>theNode->right->height)
    {
      theNode->height= theNode->left->height+1;
    }
    else
    {
      theNode->height= theNode->right->height+1;
    }
  }

  return;
}






