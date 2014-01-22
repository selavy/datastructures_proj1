#ifndef _TERM_HPP_
#define _TERM_HPP_

#include <iostream>

struct Term
{
  Term( int c, int e ) : coeff(c), exp(e) {}
  Term( const Term& term ) : coeff( term.coeff ), exp( term.exp ) {}
  bool operator<( const Term& rhs ) const {
    return exp < rhs.exp;
  }
  bool operator>( const Term& rhs ) const {
    return exp > rhs.exp;
  }

  bool operator==( const Term& rhs ) const {
    return ( exp == rhs.exp );
  }
  
  bool operator<=( const Term& rhs ) const {
    return ( exp <= rhs.exp );
  }

  bool operator>=( const Term& rhs ) const {
    return ( exp >= rhs.exp );
  }

  void print( std::ostream& os ) const {
    int val = (coeff > 0) ? coeff : -1 * coeff;
    if( exp != 0 )
      os << val << "x^" << exp;
    else
      os << val; 
  }

  friend std::ostream& operator<<( std::ostream& os, const Term& term ) {
    term.print( os );
    return os;
  }

  int coeff;
  int exp;
};

#endif
