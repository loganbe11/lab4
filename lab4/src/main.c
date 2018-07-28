#include <stdio.h>
#include <stdlib.h>
#include "../include/balancedTreeAPI.h"
#include "../include/main.h"
int main()
{
  int data1= 10;
  int data2= 9;
  int data3= 8;
  int data4 = 7;
  int data5= 6;
  int data6= 7;
  int data7= 8;
  int data8 = 9;
  int data9 = 10;
  int data10 = 13;

  Tree *tree = createBalancedBinTree(compareIntFunction,&free,NULL);
  printf("\ninserting %d",data1);
  treeInsertNode(tree,&data1);
    treePreOrderPrint(tree, &intPrint);
  printf("\ninserting %d",data2);
  treeInsertNode(tree,&data2);
    treePreOrderPrint(tree, &intPrint);

  printf("\ninserting %d",data3);
  treeInsertNode(tree,&data3);
    treePreOrderPrint(tree, &intPrint);

  printf("\ninserting %d",data4);
  treeInsertNode(tree,&data4);
    treePreOrderPrint(tree, &intPrint);

  printf("\ninserting %d",data5);
  treeInsertNode(tree,&data5);
    treePreOrderPrint(tree, &intPrint);

  printf("\ninserting %d",data6);
  treeInsertNode(tree,&data6);
    treePreOrderPrint(tree, &intPrint);

  printf("\ninserting %d",data7);
  treeInsertNode(tree,&data7);
    treePreOrderPrint(tree, &intPrint);

  treeInsertNode(tree,&data8);
  treeInsertNode(tree,&data9);
  treeInsertNode(tree,&data10);

  //print the tree in various orders
  treePreOrderPrint(tree, &intPrint);
  treeInOrderPrint(tree,&intPrint);
  treePostOrderPrint(tree,&intPrint);

  //delete a node from the tree
  treeDeleteNode(tree,&data2);

  //reprint the tree after deletion
  treePreOrderPrint(tree, &intPrint);
  treeInOrderPrint(tree,&intPrint);
  treePostOrderPrint(tree,&intPrint);

  printf("\nTreeMax:%d", *(int*)treeFindMax(tree));
  printf("\nTreeMin:%d", *(int*)treeFindMin(tree));
  return 0;
}


int compareIntFunction(void *first,void *second)
{
  //printf("\n Comparing %d and %d",*(int*)first, *(int*)second);
  if(*(int*)first==*(int*)second)
  {
    //printf("\n 0:equal");
    return 0;
  }
  else if(*(int*)first>*(int*)second)
  {
    //printf("\n 1:first greater");
    return 1;
  }
  //printf("\n -1:second greater");
  return -1;
}

void intPrint(void *data)
{
  int dataToPrint = *(int*)data;
  printf("%d->",dataToPrint);
  return;
}


