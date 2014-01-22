#ifndef _POLYNOMIAL_HPP
#define _POLYNOMIAL_HPP

#include "LinkedList.hpp"
#include "Term.hpp"

class Polynomial
{
public:
  explicit Polynomial();
  explicit Polynomial( char * poly );
  virtual ~Polynomial();

  Polynomial& add( const Polynomial& rhs );
  Polynomial& sub( const Polynomial& rhs );
  Polynomial& mult( const Polynomial& rhs );
  Polynomial& div( const Polynomial& rhs );
  int eval( int point );
  void differentiate();
  void integrate();
  void clear();

private:
  LinkedList::LinkedList<Term> _list;
};

#endif
