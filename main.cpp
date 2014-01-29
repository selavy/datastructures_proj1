#include <iostream>
#include <fstream>
#include <cstring>
#include "Polynomial.hpp"
#include "UseNodeList.hpp"
#include "MyStd.hpp"
#include "Term.hpp"

//#define _UNIT_TESTS_
//#define _INPUT_TEST_
//#define _FUNC_HDR_

#define INVALID(x) ((x < 0) || (x >= nArrs))

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
void testPolyConstr();
/* End Unit Tests */
#endif

int main( int argc, char ** argv )
{
#ifdef _UNIT_TESTS_
  testPolyConstr();
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

      // chomp the newline character
      size_t end = strlen( file_name );
      file_name[end] = '\0';

      if( strncmp( file_name, "quit", strlen("quit") + 1 ) == 0 ) return 0;
      in.open( file_name );
    }
  if(! in.is_open() )
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

  char throwaway;
  in >> throwaway;
  
#ifdef _INPUT_TEST_
  cout << "n = " << N << endl;
#endif

  for( int i = 0; i < N; ++i )
    {
      char line[SLEN];
      in.getline( line, SLEN );

#ifdef _INPUT_TEST_
      cout << "line = " << line << endl;
#endif

      poly_list[i] = new Polynomial( line );
    }

#ifdef _INPUT_TEST_
  cout << "printing polys..." << endl;
  printAll();
#endif

  bool quit = false;

  while( in.good() && !quit )
    {
      char line[SLEN];
      in.getline( line, SLEN );

#ifdef _INPUT_TEST_
      cout << line << endl;
#else
      
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
#endif

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
#ifdef _FUNC_HDR_
  cout << "add()" << endl;
#endif

  line += 2;
  char curr[SLEN];
  int index = 0;
  
  int a = 0, b = 0, c = 0;
  bool mode = true;

  for( int i = 0; (i < SLEN) && (line[i] != '\0'); ++i )
    {
      if( (line[i] == ' ') )
	{
	  curr[index] = '\0';
	  if( mode )
	    {
	      a = atoi( curr );
	      mode = false;
	    }
	  else if( !mode )
	    {
	      b = atoi( curr );
	    }
	  index = 0;
	}
      else
	{
	  curr[index] = line[i];
	  index++;
	}
    }

  c = atoi( curr );

  a--; b--; c--;

  if( INVALID(a) || INVALID(b) || INVALID(c) ) return;
  if( poly_list[a] == NULL ) return;
  if( poly_list[b] == NULL ) return;

  Polynomial retVal = poly_list[a]->add( *(poly_list[b]) );
  if( poly_list[c] == NULL )
    poly_list[c] = new Polynomial( retVal );
  else
    poly_list[c]->copy( retVal );

#ifdef _RSLT_
  cout << "Added " << *(poly_list[a]) << " + " << *(poly_list[b]) << " = " << *(poly_list[c]) << endl;
#endif
}

void mult( char * line ) {
#ifdef _FUNC_HDR_
  cout << "mult()" << endl;
#endif

  line += 2;
  char curr[SLEN];
  int index = 0;
  
  int a = 0, b = 0, c = 0;
  bool mode = true;

  for( int i = 0; (i < SLEN) && (line[i] != '\0'); ++i )
    {
      if( (line[i] == ' ') )
	{
	  curr[index] = '\0';
	  if( mode )
	    {
	      a = atoi( curr );
	      mode = false;
	    }
	  else if( !mode )
	    {
	      b = atoi( curr );
	    }
	  index = 0;
	}
      else
	{
	  curr[index] = line[i];
	  index++;
	}
    }

  c = atoi( curr );

  a--; b--; c--;

  if( INVALID(a) || INVALID(b) || INVALID(c) ) return;
  if( poly_list[a] == NULL ) return;
  if( poly_list[b] == NULL ) return;

  Polynomial retVal = poly_list[a]->mult( *(poly_list[b]) );
  if( poly_list[c] == NULL )
    poly_list[c] = new Polynomial( retVal );
  else
    poly_list[c]->copy( retVal );
}

void eval( char * line ) {
#ifdef _FUNC_HDR_
  cout << "eval()" << endl;
#endif

  int n = 0, point = 0, index = 0;
  char num[SLEN];
  char pnt[SLEN];

  line += 2; // go past the 'E' at the beginning of line 

  for( int i = 0; (i < SLEN) && (line[i] != '\0'); ++i )
    {
      if( line[i] == ' ' )
	{
	  num[index] = '\0';
	  n = atoi( num );
	  line[SLEN - 1] = '\0'; // guarantee that it is a C-string
	  line += (i + 1);
	  strcpy( pnt, line );
	  point = atoi( pnt );
	  break;
	}
      else
	{
	  num[index] = line[i];
	  index++;
	}
    }
	 
  n--;

  if( INVALID(n) ) return;
  if( poly_list[n] == NULL ) return;
  
  double retVal = poly_list[n]->eval( point );
  cout << retVal << endl;
  return;
}
  
void diff( char * line ) {
#ifdef _FUNC_HDR_
  cout << "diff()" << endl;
#endif

  int n1 = 0, n2 = 0, index = 0;
  char num1[SLEN], num2[SLEN];

  for( int i = 0; (i < SLEN) && (line[i] != '\0'); ++i )
    {
      if( line[i] == ' ' )
	{
	  num1[index] = '\0';
	  n1 = atoi( num1 );
	  line[SLEN - 1] = '\0'; // guarantee is c-string
	  line += (i + 1);
	  strcpy( num2, line );
	  n2 = atoi( num2 );
	  break;
	}
      else
	{
	  num1[index] = line[i];
	  index++;
	}
    }

  n1--; n2--;
  if( INVALID(n1) || INVALID(n2) ) return;
  if( poly_list[n1] == NULL ) return;
  if( poly_list[n2] == NULL ) poly_list[n2] = new Polynomial;

  Polynomial retVal = poly_list[n1]->differentiate();
  poly_list[n2]->copy( retVal );
}

void integ( char * line ) {
#ifdef _FUNC_HDR_
  cout << "integ()" << endl;
#endif

  int n1 = 0, n2 = 0, index = 0;
  char num1[SLEN], num2[SLEN];

  for( int i = 0; (i < SLEN) && (line[i] != '\0'); ++i )
    {
      if( line[i] == ' ' )
	{
	  num1[index] = '\0';
	  n1 = atoi( num1 );
	  line[SLEN - 1] = '\0'; // guarantee is c-string
	  line += (i + 1);
	  strcpy( num2, line );
	  n2 = atoi( num2 );
	  break;
	}
      else
	{
	  num1[index] = line[i];
	  index++;
	}
    }

  n1--; n2--;
  if( INVALID(n1) || INVALID(n2) ) return;
  if( poly_list[n1] == NULL ) return;
  if( poly_list[n2] == NULL ) poly_list[n2] = new Polynomial;

  Polynomial retVal = poly_list[n1]->integrate();
  poly_list[n2]->copy( retVal );
}

void div( char * line ) {
#ifdef _FUNC_HDR_
  cout << "div()" << endl;
#endif
}

void read( char * line ) {
#ifdef _FUNC_HDR_
  cout << "read()";
#endif
}

void print( char * line ) {
#ifdef _FUNC_HDR_
  cout << "print(): ";
#endif
  line += 2;
  int n = atoi( line );
#ifdef _FUNC_HDR_
  cout << n << endl;
#endif
  n--;
  if( INVALID(n) ) return;
  if( poly_list[n] == NULL ) return;

  cout << *(poly_list[n]) << endl;
}

void remove( char * line ) {
#ifdef _FUNC_HDR_
  cout << "remove()" << endl;
#endif
  
  int index = atoi( line );
  if( poly_list[index] != NULL )
    {    
      delete poly_list[index];
      poly_list[index] = NULL;
    }
}

void printAll() {
#ifdef _FUNC_HDR_
  cout << "printAll()" << endl;
#endif

  for( int i = 0; i < nArrs; ++i )
    {
      if( poly_list[i] != NULL )
	{
#ifdef _FUNC_HDR_
	  cout << i + 1 << ": ";
#endif
	  cout << *(poly_list[i]) << endl;
	}
    }
  cout << endl;
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
  Polynomial b = a.differentiate();
  cout << "Result :" << b << endl;
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
  Polynomial b = a.integrate();
  cout << "Result :" << b << endl;
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

void testPolyConstr() {
  cout << "testPolyConstr()" << endl;
  char line[] = "6 3 5 2 3 1 1 0";
  Polynomial a( line );
  cout << "Result :" << a << endl;
  cout << "Correct: " << "6x^3 + 5x^2 + 3x + 1" << endl;
  cout << "End testPolyConstr()\n\n" << endl;
}
#endif
