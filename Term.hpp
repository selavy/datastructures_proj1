#ifndef _TERM_HPP_
#define _TERM_HPP_

struct Term
{
  Term( int c, int e ) : coeff(c), exp(e) {}
  bool operator<(Term& rhs) {
    return exp < rhs.exp;
  }

  int coeff;
  int exp;
};

#endif
