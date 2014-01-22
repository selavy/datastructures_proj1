#include <iostream>
#include <fstream>
#include <cstring>
#include "Polynomial.hpp"

using namespace std;

const int SLEN = 512;
const int nArrs = 10;

Polynomial * poly_list[nArrs];

void add( char * line );
void mult( char * line );
void eval( char * line );
void diff( char * line );
void integ( char * line );
void div( char * line );
void read( char * line );
void print( char * line );
void remove( char * line );
void printAll();

int main( int argc, char ** argv )
{
  ifstream in;
  if( argc == 2 )
    {
      in.open( argv[1] );
    }
  else
    {
      char file_name[SLEN];
      cout << "Input file? ";
      cin.getline( file_name, SLEN );
      in.open( argv[1] );
    }

  if(! in.good() )
    {
      cerr << "Unable to open input file!" << endl;
      return 1;
    }

  /* initialize polynomial array pointers */
  for( int i = 0; i < nArrs; ++i )
    poly_list[i] = NULL;

  /* I am going to assume that the input file is correctly formatted */
  int N;
  in >> N;
  for( int i = 0; i < N; ++i )
    {
      char line[SLEN];
      cin.getline( line, SLEN );
      poly_list[N] = new Polynomial( line );
    }

  bool quit = false;

  while( in.good() && !quit )
    {
      char line[SLEN];
      cin.getline( line, SLEN );
      
      switch( line[0] )
	{
	case 'A':
	case 'a':
	  add( line );
	  break;
	case 'M':
	case 'm':
	  mult( line );
	  break;
	case 'E':
	case 'e':
	  eval( line );
	  break;
	case 'D':
	case 'd':
	  diff( line );
	  break;
	case 'I':
	case 'i':
	  integ( line );
	  break;
	case 'X':
	case 'x':
	  div( line );
	  break;
	case 'R':
	case 'r':
	  read( line );
	  break;
	case 'P':
	case 'p':
	  print( line );
	  break;
	case 'Z':
	case 'z':
	  remove( line );
	  break;
	case 'Q':
	case 'q':
	  printAll();
	  quit = true;
	default:
	  break;
	}
    }

  /* deallocate memory */
  for( int i = 0; i < nArrs; ++i )
    {
      if( poly_list[i] != NULL )
	delete poly_list[i];
    }

  return 0;
}

void add( char * line ) {
}

void mult( char * line ) {
}

void eval( char * line ) {
}

void diff( char * line ) {
}

void integ( char * line ) {
}

void div( char * line ) {
}

void read( char * line ) {
}

void print( char * line ) {
}

void remove( char * line ) {
}

void printAll() {
}
