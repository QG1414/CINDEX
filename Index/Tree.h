#ifndef TREE_H
#define TREE_H

#include "QFIFO.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct tagTreeItem
{
  char* identifier;         // create identifier that will be a word
  int counter;              // count how many times this word was present in text
  FQueue* pFifo;            // create queue for storing lines number of word
  tagTreeItem* pLeft;       // left part of tree
  tagTreeItem* pRight;      // right part of tree
} TreeItem, *LP_TreeItem;   // create additional pointer to tree LP_TreeItem (LP - long pointer)

void inOrder( LP_TreeItem pRoot, FILE* wFile ); // goes through tree inorder and saves result to file

void FindInsert( LP_TreeItem* pRoot, char* str, int lineNo ); // tries to find element with passed identifier if not then creates new

LP_TreeItem FreeTree( LP_TreeItem pRoot ); // frees tree from memory

#endif
