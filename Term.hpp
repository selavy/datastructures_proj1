#ifndef _TERM_HPP_
#define _TERM_HPP_

#include <iostream>

struct Term
{
  Term( int c, int e ) : coeff(c), exp(e) {}
  bool operator<(Term& rhs) {
    return exp < rhs.exp;
  }

  void print( std::ostream& os ) {
    int val = (coeff > 0) ? coeff : -1 * coeff;
    os << val << "x^" << exp;
  }

  std::ostream& operator<<( std::ostream& os ) {
    print( os );
    return os;
  }

  int coeff;
  int exp;
};

#endif
