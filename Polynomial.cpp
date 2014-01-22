#include "Polynomial.hpp"

Polynomial::Polynomial() {
}

Polynomial::Polynomial( char * poly ) {
}

Polynomial::~Polynomial() {
}

Polynomial& Polynomial::add( const Polynomial& rhs ) {
  Polynomial * retVal = new Polynomial;
  return *retVal;
}

Polynomial& Polynomial::sub( const Polynomial& rhs ) {
  Polynomial * retVal = new Polynomial;
  return *retVal;
}

Polynomial& Polynomial::mult( const Polynomial& rhs ) {
  Polynomial * retVal = new Polynomial;
  return *retVal;
}

Polynomial& Polynomial::div( const Polynomial& rhs ) {
  Polynomial * retVal = new Polynomial;
  return *retVal;
}

int Polynomial::eval( int point ) {
  return 0;
}

void Polynomial::differentiate() {
}

void Polynomial::integrate() {
}

void Polynomial::clear() {
}

void Polynomial::print() {
}
