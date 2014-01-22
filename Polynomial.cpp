#include "Polynomial.hpp"

Polynomial::Polynomial() {
}

Polynomial::Polynomial( char * poly ) {
  // TODO
  // char line[SLEN];

  /* have to assume that the string is null terminated */
  /*
  for( int i = 0; (i < SLEN) && poly[i] != '\0'; ++i )
    {
      
    }
  */
}

void Polynomial::addTerm( int coeff, int exp ) {
  /* do not add terms with 0 coeff to the list */
  if( coeff == 0 )
    return;

  Term term( coeff, exp );

  /* check if the term is already in the list */
  for( itr_t it = _list.begin(); it != _list.end(); ++it )
    {
      if( it.getData().exp == exp )
	{
	  *(it.getIter()->_data) += term;
	  return;
	}
    }

  _list.insert( term );
}

Polynomial::~Polynomial() {
}

const Polynomial Polynomial::add( const Polynomial& rhs ) const {
  Polynomial retVal;
  
  return retVal;
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

void Polynomial::print( std::ostream& os ) {
  itr_t it = _list.begin();
  if( it != _list.end() )
    {
      if( it.getData().coeff < 0.0f )
	os << "-";
      os << " " << it.getData() << " ";
    }
  
  it++;
  for( ; it != _list.end(); ++it )
    {
      if( it.getData().coeff < 0.0f )
	os << "- ";
      else
	os << "+ ";
      os << it.getData() << " ";
    }
}
