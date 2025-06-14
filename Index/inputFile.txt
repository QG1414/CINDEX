#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"
#include <memory.h>

LP_TreeItem ReadInputFile( char* fileName ); // function to read data from file
void WriteOutputFile( LP_TreeItem tree ); // function to write data into file
int IsIdentifier( char c ); // checking if letter is correct to be used as identifier
int IsStartingIdentifier( char c ); // checking if letter is correct to be used as first letter in identifier

#define ARGCNUM 2 // number of arguments passed to main
#define WORDLENGTH 5 // words length change
#define OUTPUTFILE "WordsIndex.txt" // name of output file

int main( int argc, char* argv[] )
{
  if( argc != ARGCNUM ) // checking if number of arguments is correct
  {
    printf( "Usage %s <input_file.txt>", argv[0] );
    return 1;
  }

  LP_TreeItem tree = ReadInputFile( argv[1] ); // reading input and returning tree pointer

  if( !tree ) // checking if pointer is not null
  {
    printf( "while reading data error occured or file is empty\n" );
    return 2;
  }

  WriteOutputFile( tree ); // writing data from tree into a file

  tree = FreeTree( tree ); // free tree from memory

  return 0;
}

LP_TreeItem ReadInputFile( char* fileName )
{
  FILE* file = fopen( fileName, "r" ); // trying to open file in read mode
  LP_TreeItem tree = NULL; // creating null pointer to tree

  if( !file ) // checking if file was opened
    return NULL;

  char letter;
  int lineNo = 1;

  while( ( letter = fgetc( file ) ) != EOF ) // work until we don't reach end of file
  {
    if( letter == '\n' ) // if its new line then skip and increase line number
    {
      lineNo++;
      continue;
    }

    char* word = (char*)calloc( WORDLENGTH, sizeof( char ) ); // create word for saving data with basic size

    if( !word ) // checking if word was created if not close file, and free tree if exists
    {
      fclose( file );

      if( tree )
        tree = FreeTree( tree );

      return NULL;
    }

    int letterNo = 0;
    int wordSize = WORDLENGTH; // set size of tree because it will be changing

    if( !IsStartingIdentifier( letter ) ) // check if letter can be start of word
      continue;

    word[letterNo++] = letter; // set letter at the correct position of word
    letter = fgetc( file ); // get next letter

    while( IsIdentifier( letter ) ) // while new letter is correct to be used as identifier
    {
      if( letterNo >= wordSize - 1) // if we exceeded free space for letters
      {
        word = (char*)realloc( word, wordSize + WORDLENGTH ); // realloc new memory with bigger size

        if( !word ) // check if reallocation was sucessful
        {
          fclose( file );

          if( tree )
            tree = FreeTree( tree );
          return NULL;
        }

        memset( word + wordSize, 0, WORDLENGTH ); // set new space to 0 to not create a problem while reading data
        wordSize += WORDLENGTH; // cheng current max size
      }

      word[letterNo++] = letter; // add new letter to correct spot
      letter = fgetc( file ); // get new letter
    }

    ungetc( letter, file ); // return last letter that it can be checked by main loop and new line detection
    FindInsert( &tree, word, lineNo ); // add new word to tree
  }

  fclose( file ); // close file
  return tree;
}

void WriteOutputFile( LP_TreeItem tree )
{
  if( !tree ) // check if file exists
  {
    printf( "ERROR TreeItem was not provided\n" );
    return;
  }

  FILE* wFile = fopen( OUTPUTFILE, "w" ); // open file in write mode

  if( !wFile ) // check if file was opened sucessfuly
  {
    printf( "ERROR while opening file to write data\n" );
    return;
  }

  inOrder( tree, wFile ); // go through it in order and save to created file pointer

  fclose( wFile ); // close file

  printf( "file <%s> was created sucessfully\n", OUTPUTFILE ); // message for users
}

int IsIdentifier( char c ) // function to check if letter can be a identifier
{
  return ( ( c >= 'A' && c <= 'Z' ) || ( c >= 'a' && c <= 'z' ) || ( c >= '0' && c <= '9' ) || c == '_' );
}

int IsStartingIdentifier( char c ) // function to check if letter can be a start of identifier
{
  if( c >= '0' && c <= '9' )
    return 0;

  return IsIdentifier( c );
}