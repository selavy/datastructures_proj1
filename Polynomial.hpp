#ifndef _POLYNOMIAL_HPP
#define _POLYNOMIAL_HPP

#include "LinkedList.hpp"
#include "UseNodeList.hpp"
#include "Term.hpp"
#include <iostream>
#include <cmath>

class Polynomial
{
public:
  typedef LinkedList::LinkedList<
    Term,
  SortingPolicies::IncreasingOrderSort,
  AllocationPolicies::UseNodeList
  >::iterator itr_t;

  typedef LinkedList::LinkedList<
    Term,
    SortingPolicies::IncreasingOrderSort,
    AllocationPolicies::UseNodeList
    > poly_t;

public:
  explicit Polynomial();
  explicit Polynomial( char * poly );
  Polynomial( const Polynomial& other );
  virtual ~Polynomial();

  void addTerm( double coeff, int exp );
  void subTerm( double coeff, int exp );
  void copy( const Polynomial& other );

  const Polynomial add( const Polynomial& rhs ) const;
  const Polynomial sub( const Polynomial& rhs ) const;
  Polynomial& mult( const Polynomial& rhs );
  Polynomial& div( const Polynomial& rhs );
  double eval( int point );
  void differentiate();
  void integrate();
  void clear();
  void print( std::ostream& os ) const;

  Polynomial& operator=( const Polynomial& rhs );
  friend std::ostream& operator<<( std::ostream& os, const Polynomial& rhs );

private:
  poly_t _list;
};

#endif
