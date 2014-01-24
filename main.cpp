#include <iostream>
#include <fstream>
#include <cstring>
#include "Polynomial.hpp"
#include "UseNodeList.hpp"
#include "MyStd.hpp"
#include "Term.hpp"

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
  testSub();
  testMult();
  testEval();
  testDiff();
  testIntg();
  testDiv();
  testRemove();
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
  cout << "Test copy" << endl;
  Polynomial a, b;
  a.addTerm( 10, 5 );
  cout << "a: " << a << " copied to b..." << endl;
  b.copy( a );
  cout << "b: " << b << endl;

  Polynomial c(a), d;
  c.addTerm( 6, 6 );
  c.addTerm( -1, 2 );
  cout << "c: " << c << " copied to d..." << endl;
  d.copy( c );
  cout << "d: " << d << endl;
  
  cout << "End testCopy()\n\n" << endl;
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
  cout << "End testPrint()\n\n" << endl;
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

  Polynomial d, e;
  d.addTerm( 10, 5 );
  d.addTerm( -4, 2 );
  d.addTerm( 10, 0 );
  e.addTerm( 12, 6 );
  e.addTerm( 5, 5 );
  e.addTerm( 4, 2 );
  e.addTerm( -10, 1 );
  e.addTerm( -10, 0 );
  Polynomial f;
  f = ( d.add( e ) );
  cout << "Result :";
  f.print( cout );
  cout << "\nCorrect: 12x^6 + 15x^5 - 10x" << endl;

  cout << "End testAdd()\n\n" << endl;
}

void testSub() {
  cout << "testSub()" << endl;
  Polynomial a, b;
  a.addTerm( 1, 1 );
  a.addTerm( 2.2f, 2 );
  a.addTerm( 3.3f, 3 );
  a.addTerm( 4.4f, 4 );
  a.addTerm( 5.5f, 5 );
  b.addTerm( -3, 1 );
  b.addTerm( -4, 2 );
  b.addTerm( 5, 3 );
  b.addTerm( 25, 8 );
  cout << "a: " << a << endl;
  cout << "b: " << b << endl;
  cout << "Result : " << a.sub(b) << endl;
  cout << "Correct: - 25x^8 + 5.5x^5 + 4.4x^4 - 1.7x^3 + 6.2x^2 + 4x" << endl;
  cout << "End testSub()\n\n" << endl;
}

void testMult() {
  cout << "testMult()" << endl;
  Polynomial a, b;
  a.addTerm( 6, 1 );
  a.addTerm( 3, 0 );
  b.addTerm( 4, 1 );
  b.addTerm( 2, 0 );
  cout << "a: " << a << endl;
  cout << "b: " << b << endl;
  cout << "Result :" << a.mult( b ) << endl;
  cout << "Correct: 24x^2 + 24x + 6" << endl;
  cout << "end testMult()\n\n" << endl;
}

void testEval() {
  cout << "testEval()" << endl;
  Polynomial a;
  a.addTerm( 1, 5 );
  a.addTerm( -3, 4 );
  a.addTerm( 4, 3 );

  cout << "a: " << a << endl;
  cout << "eval at 3" << endl;
  cout << "Result : " << a.eval(3) << endl;
  cout << "Correct: 108" << endl;

  cout << "End testEval()\n\n" << endl;
}

void testDiff() {
  cout << "testDiff()" << endl;
  Polynomial a;
  a.addTerm( 1, 5 );
  a.addTerm( -1, 4 );
  a.addTerm( 3, 3 );
  a.addTerm( 4, 2 );
  a.addTerm( 5, 1 );
  a.addTerm( 250, 0 );
  cout << "a: " << a << endl;
  cout << "Differentiating..." << endl;
  a.differentiate();
  cout << "Result :" << a << endl;
  cout << "Correct: 5x^4 - 4x^3 + 9x^2 + 8x + 5" << endl;
  cout << "End testDiff()\n\n" << endl;
}

void testIntg() {
  cout << "testIntg()" << endl;
  Polynomial a;
  a.addTerm( 1, 5 );
  a.addTerm( -1, 4 );
  a.addTerm( 3, 3 );
  a.addTerm( 4, 2 );
  a.addTerm( 5, 1 );
  a.addTerm( 250, 0 );
  cout << "a: " << a << endl;
  cout << "Integrating..." << endl;
  a.integrate();
  cout << "Result :" << a << endl;
  cout << "Correct: 0.1667x^6 - 0.2x^5 + 0.75x^4 + 1.3333x^3 + 2.5x^2 + 250x" << endl;
  cout << "End testIntg()\n\n" << endl;
}

void testDiv() {
  cout << "testDiv()" << endl;
  cout << "End testDiv()\n\n" << endl;
}

void testRemove() {
  cout << "testRemove()" << endl;
  Polynomial * a = new Polynomial;
  a->addTerm( 10, 5 );
  a->addTerm( -1.2, 3 );
  delete a;
  cout << "Polynomial destructor works\n";
  cout << "End testRemove()\n\n" << endl;
}


#endif
