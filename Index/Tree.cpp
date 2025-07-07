#include "Tree.h"
#include <string.h>

void Visit( LP_TreeItem pRoot, int lineNo ); // helper function to visit current tree element and do operations
int compStr( char* s1, char* s2 ); // helper function to compare two char arrays (strings) with eachother


void FindInsert( LP_TreeItem* pRoot, char* str, int lineNo )
{
  if( !str ) // checking if str pointer is present
  {
    printf( "ERROR cannot pass null str\n" );
    return;
  }

  if( !*pRoot ) // checking if tree element exists
  {
    *pRoot = (LP_TreeItem)calloc( 1, sizeof( TreeItem ) ); // creating new tree element

    if( !*pRoot ) // if creation was not sucessful then exit
    {
      printf( "ERROR while allocating memory for treeElement\n" );
      return;
    }

    // assign starting values for new node
    (*pRoot)->identifier = str;
    (*pRoot)->counter = 1;
    (*pRoot)->pFifo = FQCreate();

    if( !( (*pRoot)->pFifo ) ) // if creation of FIFO was not sucessful then return
    {
      printf( "ERROR Fifo was not created\n" );
      return;
    }

    if( !FQEnqueue( (*pRoot)->pFifo, lineNo ) ) // if enqueue was not sucessful then return
    {
      printf( "ERROR enqueu was not sucessful\n" );
      return;
    }

    // (*pRoot)->pLeft = (*pRoot)->pRight = NULL; this would be used if we use malloc instead of calloc
  }
  else // if node exists
  {
    int compValue = compStr( (*pRoot)->identifier, str ); // compare current node identifier with passed identifier

    if( compValue == INT_MIN ) // if there was an error while comparing return
      return;

    if( compValue < 0 )
      FindInsert( &( (*pRoot)->pRight ), str, lineNo ); // if passed word is larger then check right node
    else if( compValue > 0 )
      FindInsert( &( (*pRoot)->pLeft ), str, lineNo ); // if passed word is smaller then check right node
    else
      Visit( *pRoot, lineNo ); // if words are the same then visit current node
  }
}


void inOrder( LP_TreeItem pRoot, FILE* wFile )
{
  if( !wFile ) // check if file was passed
  {
    printf( "ERROR write file is null\n" );
    return;
  }

  if( !pRoot ) return; // recursion stop condition

  inOrder( pRoot->pLeft, wFile ); // check left node

  fprintf( wFile, "ident: %s | count: %d | encounter lines: ", pRoot->identifier, pRoot->counter ); // save basic data to file
  printf( "ident: %s | count: %d | encounter lines: ", pRoot->identifier, pRoot->counter );

  FQPrint( pRoot->pFifo, wFile );

  fprintf( wFile, "\n\n" );
  printf("\n\n");

  inOrder( pRoot->pRight, wFile ); // check right node
}

LP_TreeItem FreeTree( LP_TreeItem pRoot )
{
  if( pRoot ) // if node exists
  {
    FreeTree( pRoot -> pLeft );   // check left node
    FreeTree( pRoot -> pRight );  // check right node
    free( pRoot -> identifier );  // free identifier from memory
    FQRemove( &(pRoot->pFifo) );  // remove queue from memory
    free( pRoot );                // remove whole tree from memory
  }

  return NULL;
}

void Visit( LP_TreeItem pRoot, int lineNo )
{
  if( !pRoot ) // check if node is not null
  {
    printf( "ERROR passed treeItem was null\n" );
    return;
  }

  if( pRoot->pFifo->pTail->pInfo != lineNo ) // if its new element then enqueue it
    FQEnqueue( pRoot->pFifo, lineNo );

  pRoot->counter++; // increase number of word encountering
}

int compStr( char* s1, char* s2 )
{
  char* str1 = (char*)calloc( strlen(s1) + 1, sizeof( char ) ); // create temporary new words
  char* str2 = (char*)calloc( strlen(s2) + 1, sizeof( char ) );

  if( !str1 || !str2 ) // check if creation was sucessful
  {
    printf( "ERROR Copy strs were not created sucessfully\n" );
    return INT_MIN;
  }

  strcpy( str1, s1 ); // copy elements from s1 to new pointer
  strcpy( str2, s2 ); // copy elements from s2 to new pointer

  str1 = _strlwr( str1 ); // change all leters to lower
  str2 = _strlwr( str2 );

  int val = strcmp( str1, str2 ); // compare two str elements

  free( str1 ); // clear them from memory
  free( str2 );

  return val;
}