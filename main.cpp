#include <iostream>
#include <fstream>
#include <cstring>
#include "Polynomial.hpp"
#include "UseNodeList.hpp"
#include "Node.hpp"
#include "MyStd.hpp"
#include "Term.hpp"

//#define _UNIT_TESTS_
//#define _INPUT_TEST_
//#define _FUNC_HDR_
//#define _RSLT_

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
// Unit Tests //
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
// End Unit Tests //
#endif

int main( int argc, char ** argv )
{
  /* If you want to run the unit tests, then uncomment the line #define _UNIT_TESTS_ */
  /* Otherwise the regular program is run */
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

  /* the main program */
  /* try to get the input file name from the command line */
  /* if not available then ask for it from the user */
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

  // initialize polynomial array pointers
  for( int i = 0; i < nArrs; ++i )
    poly_list[i] = NULL;

  // I am going to assume that the input file is correctly formatted
  int N;
  in >> N;
  in.get(); // move past the newline character

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
      /* the polynomial class supports a constuctor that takes a c-string so just let it handle initializing itself */
      /* NB. Still assuming that the input file is correctly formatted */
      poly_list[i] = new Polynomial( line );
    }

#ifdef _INPUT_TEST_
  cout << "printing polys..." << endl;
  printAll();
#endif

  /* main loop for reading in the file and executing the commands */
  bool quit = false;
  while( in.good() && !quit )
    {
      char * line = new char[SLEN]; // can NOT pass non-malloc'd c-string to getline
      memset( line, 0, SLEN );
      size_t size = SLEN;
      in.getline( line, size );

#ifdef _INPUT_TEST_
      cout << line << endl;
#endif
      
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
      
      delete [] line;
    }

  // deallocate memory
  for( int i = 0; i < nArrs; ++i )
    {
      if( poly_list[i] != NULL )
	{
	  delete poly_list[i];
	  poly_list[i] = NULL;
	}
    }

  // this function must be called to remove the list of free store nodes
  // kind of awkward, but no easier way to do this since it is static
  // and c++ handling of the static keyword is awkward
  AllocationPolicies::UseNodeList<Term>::deleteFreeStore();
      
#endif

  return 0;
}

/* reads from a c-string, and executes the Polynomial add function
   on 2 polynomials storing the result in a third */
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

  /*Polynomial retVal = poly_list[a]->add( *(poly_list[b]) );
  if( poly_list[c] == NULL )
    poly_list[c] = new Polynomial( retVal );
  else
  poly_list[c]->copy( retVal ); */
  if( poly_list[c] == NULL ) poly_list[c] = new Polynomial;
  poly_list[c]->copy( poly_list[a]->add( *(poly_list[b] ) ) );

#ifdef _RSLT_
  cout << "Added (" << *(poly_list[a]) << ") + (" << *(poly_list[b]) << ") = " << *(poly_list[c]) << endl;
#endif
}

/* reads from a c-string, and executes the Polynomial mult function
   on 2 polynomials stroing the result in a third */
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

  /*Polynomial retVal = poly_list[a]->mult( *(poly_list[b]) );
  if( poly_list[c] == NULL )
    poly_list[c] = new Polynomial( retVal );
  else
  poly_list[c]->copy( retVal ); */
  if( poly_list[c] == NULL ) poly_list[c] = new Polynomial;
  poly_list[c]->copy( poly_list[a]->mult( *(poly_list[b] ) ) );

#ifdef _RSLT_
  cout << "Result (mult): " << *(poly_list[c]) << endl;
#endif
}

/* reads from a c-string, and executes the Polynomial eval function
   printing the result to the stdout */
void eval( char * line ) {
#ifdef _FUNC_HDR_
  cout << "eval()" << endl;
#endif

  int n = 0, index = 0;
  char num[SLEN];
  char pnt[SLEN];
  double point;

  line += 2; // go past the 'E' at the beginning of line 

  for( int i = 0; (i < SLEN) && (line[i] != '\0'); ++i )
    {
      if( line[i] == ' ' )
	{
	  num[index] = '\0';
	  n = atoi( num );
	  line[SLEN - 3] = '\0'; // guarantee that it is a C-string
	  line += (i + 1);
	  strcpy( pnt, line );
	  point = atof( pnt );
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

#ifdef _RSLT_
  cout << "Result (eval): ";
#endif

  cout << retVal << endl;

  return;
}
  
/* reads from a c-string an executes the Polynomial differentiate function
 storing the result in a second Polynomial */
void diff( char * line ) {
#ifdef _FUNC_HDR_
  cout << "diff(): ";
#endif

  int n1 = 0, n2 = 0, index = 0;
  char num1[SLEN], num2[SLEN];
  line += 2; // go past the 'D' at the beginning

  for( int i = 0; (i < SLEN) && (line[i] != '\0'); ++i )
    {
      if( line[i] == ' ' )
	{
	  num1[index] = '\0';
	  n1 = atoi( num1 );
	  line[SLEN - 3] = '\0'; // guarantee is c-string
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

#ifdef _FUNC_HDR_
  cout << "#" << n1 << " put into #" << n2 << endl;
#endif

  n1--; n2--;

  if( INVALID(n1) || INVALID(n2) ) return;
  if( poly_list[n1] == NULL ) return;
  if( poly_list[n2] == NULL ) poly_list[n2] = new Polynomial;

  poly_list[n2]->copy( poly_list[n1]->differentiate() );

#ifdef _RSLT_
  cout << "Result (diff): " << *(poly_list[n2]) << endl;
#endif
}

/* reads from a c-string to execute the Polynomial integration function
   storing the result in a second Polynomial */
void integ( char * line ) {
#ifdef _FUNC_HDR_
  cout << "integ()" << endl;
#endif

  int n1 = 0, n2 = 0, index = 0;
  char num1[SLEN], num2[SLEN];
  line += 2; // go past the 'I' at the beginning

  for( int i = 0; (i < SLEN) && (line[i] != '\0'); ++i )
    {
      if( line[i] == ' ' )
	{
	  num1[index] = '\0';
	  n1 = atoi( num1 );
	  line[SLEN - 3] = '\0'; // guarantee is c-string
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

#ifdef _FUNC_HDR_
  cout << "#" << n1 << " put into #" << n2 << endl;
#endif

  n1--; n2--;

  if( INVALID(n1) || INVALID(n2) ) return;
  if( poly_list[n1] == NULL ) return;
  if( poly_list[n2] == NULL ) poly_list[n2] = new Polynomial;
  //Polynomial retVal = poly_list[n1]->integrate();
  poly_list[n2]->copy( poly_list[n1]->integrate() );

#ifdef _RSLT_
  cout << "Result (integ): " << *(poly_list[n2]) << endl;
#endif
}

/* Reads from a c-string to execute the Polynomial div function
   storing the result in a third polynomial */
void div( char * line ) {
#ifdef _FUNC_HDR_
  cout << "div() of: ";
#endif

  line += 2;
  char curr[SLEN];
  memset( curr, 0, SLEN );
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
  
  curr[SLEN - 1] = '\0';
  c = atoi( curr );

  a--; b--; c--;

  if( INVALID(a) || INVALID(b) || INVALID(c) ) return;
  if( poly_list[a] == NULL ) return;
  if( poly_list[b] == NULL ) return;

#ifdef _FUNC_HDR_
  cout << "#" << (a + 1) << " ( " << *(poly_list[a]) << ") by #" << (b + 1) << " ( " << *(poly_list[b]) << ")" << endl;
#endif

  if( poly_list[c] == NULL ) poly_list[c] = new Polynomial;
  poly_list[c]->copy( poly_list[a]->div( *(poly_list[b]) ) );

#ifdef _RSLT_
  cout << "Result (div): " << *(poly_list[c]) << endl;
#endif
}

/* Reads in a Polynomial from a c-string */
void read( char * line ) {
#ifdef _FUNC_HDR_
  cout << "read(): " << line << endl;
#endif

  line += 2; // go past the 'R'
  char polyNum[SLEN];
  int index = 0, n = 0, i = 0;

  for( ; (i < SLEN) && (line[i] != '\0'); ++i )
    {
      if( line[i] == ' ' )
	{
	  polyNum[index] = '\0';
	  n = atoi( polyNum );
	  break;
	}
      else
	{
	  polyNum[index] = line[i];
	  index++;
	}
    }

  line += (i + 1);
  n--;

  if( INVALID(n) ) return;

  if( poly_list[n] != NULL )
    {
      delete poly_list[n];
      poly_list[n] = NULL;
    }

  poly_list[n] = new Polynomial( line );

#ifdef _RSLT_
  cout << "Read in: " << *(poly_list[n]) << endl;
#endif
}

void print( char * line ) {
#ifdef _FUNC_HDR_
  cout << "print(): #";
#endif
  line += 2;
  int n = atoi( line );
#ifdef _FUNC_HDR_
  cout << n << endl;
#endif
  n--;
  if( INVALID(n) ) return;
  if( poly_list[n] == NULL ) {
    cout << "0" << endl;
    return;
  }

  cout << *(poly_list[n]) << endl;
}

/* Reads a c-string to remove a polynomial */
void remove( char * line ) {
#ifdef _FUNC_HDR_
  cout << "remove(): " << line << endl;
#endif
  line += 2; // move past the 'Z'
  int index = atoi( line );
  index--;
  if( INVALID( index ) ) return;
  if( poly_list[index] != NULL )
    {    
      delete poly_list[index];
      poly_list[index] = NULL;
    }

#ifdef _RSLT_
  if( poly_list[index] == NULL )
    cout << "successfullly removed" << endl;
  else
    cout << "NOT successfully removed" << endl;
#endif
}

/* Prints all the polynomials in the poly_list array,
   If a pointer is NULL, then it is skipped */
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
}

/*************************************************************************************/
/* The functions below are all unit tests to test the Polynomial functions           */
/*************************************************************************************/
#ifdef _UNIT_TESTS_
void testCopy() {
  //cout << "Test copy" << endl;
  Polynomial a, b;
  a.addTerm( 10, 5 );
  //  cout << "a: " << a << " copied to b..." << endl;
  b.copy( a );
  //cout << "b: " << b << endl;

  Polynomial c(a), d;
  c.addTerm( 6, 6 );
  c.addTerm( -1, 2 );
  //cout << "c: " << c << " copied to d..." << endl;
  d.copy( c );
  //cout << "d: " << d << endl;

  //cout << "d: " << d << " copied to a..." << endl;
  a.copy( d );
  //cout << "a: " << a << endl;
  
  //cout << "End testCopy()\n\n" << endl;
}

void testPrint() {
  cout << "testPrint()" << endl;
  Polynomial aPoly;
  aPoly.addTerm( 10, 5 );
  aPoly.addTerm( 15, 0 );
  aPoly.addTerm( -14, 3 );
  cout << "Result : ";
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
  cout << "Result : ";
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
  cout << "Result : ";
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
  cout << "Correct: -25x^8 + 5.5x^5 + 4.4x^4 - 1.7x^3 + 6.2x^2 + 4x" << endl;
  cout << endl;

  Polynomial c;
  c.addTerm( 1, 3 );
  c.addTerm( 6, 2 );
  c.addTerm( 11, 1 );
  c.addTerm( 6, 0 );
  Polynomial d;
  d.addTerm( 1, 3 );
  d.addTerm( 3, 2 );
  Polynomial e = c.sub( d );
  cout << "( " << c << ") - ( " << d << "):" << endl;
  cout << "Result : " << e << endl;
  cout << "Correct: 3x^2 + 11x + 6" << endl;
  Polynomial f;
  f.addTerm( 3, 2 );
  f.addTerm( 9, 1 );
  cout << "( " << e << ") - ( " << f << "):" << endl;
  e = e.sub( f );
  cout << "Result : " << e << endl;
  cout << "Correct: 2x + 6" << endl;
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
  cout << "Result : " << a.mult( b ) << endl;
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
  cout << "Result : " << b << endl;
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
  cout << "Result : " << b << endl;
  cout << "Correct: 0.166667x^6 - 0.2x^5 + 0.75x^4 + 1.33333x^3 + 2.5x^2 + 250x" << endl;
  cout << "End testIntg()\n\n" << endl;
}

void testDiv() {
  cout << "testDiv()" << endl;

  Polynomial a, b;
  a.addTerm( 1, 3 );
  a.addTerm( 6, 2 );
  a.addTerm( 11, 1 );
  a.addTerm( 6, 0 );

  b.addTerm( 1, 1 );
  b.addTerm( 3, 0 );
  cout << "Dividing ( " << a << ") by ( " << b << ")" << endl;
  Polynomial c = a.div(b);
  cout << "Result : " << c << endl;
  cout << "Correct: x^2 + 3x + 2" << endl;
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
  cout << "Result : " << a << endl;
  cout << "Correct: " << "6x^3 + 5x^2 + 3x + 1" << endl;
  cout << "End testPolyConstr()\n\n" << endl;
}
#endif
