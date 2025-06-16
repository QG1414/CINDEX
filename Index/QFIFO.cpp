#include "QFIFO.h"

FQueue* FQCreate()
{
  FQueue* q = (FQueue*)malloc( sizeof( FQueue ) ); // allocate memory for queue

  if( !q ) // if not sucessful return null
    return NULL;

  q->pHead = q->pTail = NULL; // set values for head and tail to null

  return q; // return pointer to queue
}

int FQEmpty( FQueue* q )
{
  return !q || !( q->pHead ); // check if q exists and if head is not Null
}

int FQEnqueue( FQueue* q, int p )
{
  if( !q ) // in case q or p is not existing return with 0 (False)
    return 0;

  FQItem* newItem = (FQItem*)malloc( sizeof( FQItem ) ); // allocate memory for new queue element

  if( !newItem ) // check if allocation was sucessful if not return 0 (False)
    return 0;

  newItem->pInfo = p; // set p added by user as pInfo value
  newItem->pNext = NULL; // set next item of created element to NULL

  if( !( q->pHead ) ) // if head is null then head is newItem
    q->pHead = newItem;
  else                // else set tail next value to new item
    q->pTail->pNext = newItem;

  q->pTail = newItem; // set tail value to new item

  return 1; // return that enqueue was sucessful
}

int FQDequeue( FQueue* q )
{
  if( FQEmpty( q ) ) // check if queue is not empty
    return NULL;

  int val = q->pHead->pInfo; // get value in current head
  FQDel( q ); // delete head element

  return val; // return value we got
}

void FQClear( FQueue* q )
{
  if( !q ) // check if queue exists
  {
    printf( "Queue does not exist or freeMem is null in FQClear\n" );
    return;
  }

  while( !FQEmpty( q ) )        // repeat until queue is empty
    FQDequeue( q );  // free memory from queue and delete queue elements
}

void FQRemove( FQueue** q )
{
  if( !q || !*q ) // check if queue adress exists and queue pointer exists
  {
    printf( "Queue Adress is null or Queue does not exist or freeMem is null in FQRemove\n" );
    return;
  }

  FQClear( *q );  // clear queue elements
  free( *q );     // remove queue from memory

  *q = NULL; // set queue to null
}

void FQDel( FQueue* q )
{
  if( FQEmpty( q ) ) // if queue is empty or does not exists return
  {
    printf( "Queue is empty or does not exist in FQDel\n" );
    return;
  }

  FQItem* ptr = q->pHead; // get head pointer element
  q->pHead = ptr->pNext; // set head to the next element

  if( !(q->pHead) ) // in case current head is NULL set tail to NULL that we return to base values
    q->pTail = NULL;

  free( ptr ); // free item from memory
}

void FQPrint( FQueue* q, FILE* wFile )
{
  if( !q || !wFile ) // check if queue exists and file exists
  {
    printf( "Queue does not exist or file is null in FQPrint\n" );
    return;
  }

  FQItem* head = q->pHead; // get pointer of head element

  while( head ) // while head is not NULL
  {
    fprintf( wFile, "%d ", head->pInfo ); // print into file
    printf( "%d ", head->pInfo );
    head = head->pNext;       // change head to next element
  }
}