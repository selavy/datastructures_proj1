#include <iostream>
#include <fstream>
#include <cstring>
#include "Polynomial.hpp"
#include "UseNodeList.hpp"
#include "MyStd.hpp"

#define _UNIT_TESTS_

using namespace std;

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

#ifdef _UNIT_TESTS_
/* Unit Tests */
void testCopy();
void testPrint();
void testAdd();
void testSub();
void testMult();
void testEval();
void testDiff();
void testIntg();
void testDiv();
void testRemove();
/* End Unit Tests */
#endif

int main( int argc, char ** argv )
{
#ifdef _UNIT_TESTS_
  testCopy();
  testPrint();
  testAdd();
#else

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
#endif

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

#ifdef _UNIT_TESTS_
void testCopy() {
  Polynomial a, b;
  a.addTerm( 10, 5 );
  cout << "a: "; a.print( cout ); cout << " copied to b..." << endl;
  b.copy( a );
  cout << "b: "; b.print( cout ); cout << endl;

  Polynomial c(a), d;
  c.addTerm( 6, 6 );
  c.addTerm( -1, 2 );
  cout << "c: "; c.print( cout ); cout << " copied to d..." << endl;
  d.copy( c );
  cout << "d: "; d.print( cout ); cout << endl;
  
  cout << "End testCopy()" << endl;
}

void testPrint() {
  cout << "testPrint()" << endl;
  Polynomial aPoly;
  aPoly.addTerm( 10, 5 );
  aPoly.addTerm( 15, 0 );
  aPoly.addTerm( -14, 3 );
  cout << "Result :";
  aPoly.print( cout );
  cout << "\nCorrect: 10x^5 - 14x^3 + 15" << endl;
  cout << "End testPrint()" << endl;
}

void testAdd() {
  cout << "testAdd()" << endl;
  Polynomial aPoly;
  aPoly.addTerm( 10, 5 );

  aPoly.addTerm( 15, 0 );
  aPoly.addTerm( -14, 3 );
  cout << "Adding ";
  aPoly.print( cout );
  cout << " to ";
  Polynomial bPoly;
  bPoly.addTerm( 14, 5 );
  bPoly.addTerm( 13, 0 );
  bPoly.addTerm( 20.4, 2 );
  bPoly.print( cout );
  cout << endl;

  Polynomial cPoly = aPoly.add( bPoly );
  cout << "Result :";
  cPoly.print( cout );
  cout << "\nCorrect: 24x^5 - 14x^3 + 20x^2 + 28" << endl;

  Polynomial d, e, f;
  d.addTerm( 10, 5 );
  d.addTerm( -4, 2 );
  d.addTerm( 10, 0 );
  e.addTerm( 12, 6 );
  e.addTerm( 5, 5 );
  e.addTerm( 4, 2 );
  e.addTerm( -10, 1 );
  e.addTerm( -10, 0 );
  f = d.add( e );
  cout << "Result :";
  f.print( cout );
  cout << "\nCorrect: 12x^6 + 15x^5 - 10x" << endl;

  cout << "End testAdd()" << endl;
}

void testSub() {
}

void testMult() {
}

void testEval() {
}

void testDiff() {
}

void testIntg() {
}

void testDiv() {
}

void testRemove() {
}

#endif
