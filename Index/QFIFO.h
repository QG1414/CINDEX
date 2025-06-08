#ifndef QFIFO_H
#define QFIFO_H

#include <stdlib.h>
#include <stdio.h>

typedef struct tagFQItem // one queue element
{ 
  int pInfo;     // info got from global.h
  tagFQItem* pNext; // pointer to the next element in array
} FQItem;

typedef struct // Queue type
{
  FQItem* pHead;  // pointer to the first queue item
  FQItem* pTail;  // pointer to the last queue item
} FQueue;

FQueue* FQCreate();                         // creating queue pointer (initialization)
int     FQEmpty( FQueue* q );               // checks if queue is empty or if it does not exist
int     FQEnqueue( FQueue* q, int p );      // insert new item into queue and return if its sucessful
int     FQDequeue( FQueue* q );             // take first element from queue
void    FQClear( FQueue* q );               // clears whole queue and frees memory
void    FQRemove( FQueue** q );             // clears queue and then removes queue
void    FQDel( FQueue* q );                 // removes one queue element and frees memory for it
void    FQPrint( FQueue* q, FILE* wFile );  // prints whole into file queue without changing head or tail
#endif