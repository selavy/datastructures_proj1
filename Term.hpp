#ifndef _TERM_HPP_
#define _TERM_HPP_

#include <iostream>

struct Term
{
  Term( double c, int e ) : coeff(c), exp(e) {}
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

  const Term operator+( const Term& rhs ) const {
   return Term(*this) += rhs;
  }
  
  Term& operator+=( const Term& rhs ) {
    if( exp == rhs.exp )
      {
	coeff += rhs.coeff;
      }
    return *this;
  }

  Term& operator -=( const Term& rhs ) {
    if( exp == rhs.exp )
      {
	coeff -= rhs.coeff;
      }
    return *this;
  }

  const Term operator-( const Term& rhs ) {
    return Term(*this) -= rhs;
  }

  Term& operator*=( const int val ) {
    coeff *= val;
    return *this;
  }

  const Term operator*( int val ) const {
    return Term(*this) *= val;
  }
  
  Term& operator*=( const Term& rhs ) {
    coeff *= rhs.coeff;
    exp += rhs.exp;
    return *this;
  }

  const Term operator*( const Term& rhs ) const {
    return Term(*this) *= rhs;
  }

  Term& operator/=( const Term& rhs ) {
    coeff /= rhs.coeff;
    exp -= rhs.exp;
    return *this;
  }

  const Term operator/=( const Term& rhs ) const {
    return Term(*this) /= rhs;
  }

  void print( std::ostream& os ) const {
    double val = (coeff > 0) ? coeff : -1 * coeff;
    if( (exp != 0) && (exp != 1) && (val != 1) )
      os << val << "x^" << exp;
    else if( val == 1 && (exp != 1) )
      os << "x^" << exp;
    else if( (val != 1) && (exp == 1) )
      os << val << "x";
    else if( exp == 1 )
      os << "x";
    else
      os << val; 
  }

  friend std::ostream& operator<<( std::ostream& os, const Term& term ) {
    term.print( os );
    return os;
  }

  double coeff;
  int exp;
};

#endif
