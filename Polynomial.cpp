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

Polynomial::Polynomial( const Polynomial& other ) {
  copy( other );
}

void Polynomial::copy( const Polynomial& other ) {
  _list.copy( other._list );
}

void Polynomial::addTerm( double coeff, int exp ) {
  /* do not add terms with 0 coeff to the list */
  if( coeff == 0 )
    return;

  Term term( coeff, exp );

  /* check if the term is already in the list */
  for( itr_t it = _list.begin(); it != _list.end(); ++it )
    {
      int curr_exp = it.getData().exp;
      if( curr_exp == exp )
	{
	  *(it.getIter()->_data) += term;
	  if( it.getData().coeff == 0 )
	    _list.remove( it );
	  return;
	}
      if( curr_exp < exp )
	break;
    }

  _list.insert( term );
}

void Polynomial::subTerm( double coeff, int exp ) {
  addTerm( -1 * coeff, exp );
}

Polynomial::~Polynomial() {
}

const Polynomial Polynomial::add( const Polynomial& rhs ) const {
  Polynomial retVal;

  for( itr_t it = _list.begin(); it != _list.end(); ++it )
    retVal.addTerm( it.getData().coeff, it.getData().exp );

  for( itr_t it = rhs._list.begin(); it != rhs._list.end(); ++it )
    retVal.addTerm( it.getData().coeff, it.getData().exp );
  return retVal;
}

const Polynomial Polynomial::sub( const Polynomial& rhs ) const {
  Polynomial retVal;

  for( itr_t it = _list.begin(); it != _list.end(); ++it )
    retVal.addTerm( it.getData().coeff, it.getData().exp );
  for( itr_t it = rhs._list.begin(); it != rhs._list.end(); ++it )
    retVal.subTerm( it.getData().coeff, it.getData().exp );
  return retVal;
}

Polynomial& Polynomial::mult( const Polynomial& rhs ) {
  Polynomial * retVal = new Polynomial;
  return *retVal;
}

Polynomial& Polynomial::div( const Polynomial& rhs ) {
  Polynomial * retVal = new Polynomial;
  return *retVal;
}

double Polynomial::eval( int point ) {
  double retVal = 0;

  for( itr_t it = _list.begin(); it != _list.end(); ++it )
    {
      retVal += it.getData().coeff * pow( point, it.getData().exp );
    }
  return retVal;
}

void Polynomial::differentiate() {
  for( itr_t it = _list.begin(); it != _list.end(); ++it )
    {
      int exp = it.getData().exp;
      it.getIter()->_data->coeff *= exp;
      if( it.getData().exp == 0 )
	{
	  _list.remove( it );
	  return;
	}

      it.getIter()->_data->exp--;
      if( it.getData().coeff == 0 )
	_list.remove( it );
    }
}

void Polynomial::integrate() {
}

void Polynomial::clear() {
  // _list.clear();
}

void Polynomial::print( std::ostream& os ) const {
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

Polynomial& Polynomial::operator=( const Polynomial& rhs ) {
  copy( rhs );
  return *this;
}

std::ostream& operator<<( std::ostream& os, const Polynomial& rhs ) {
  rhs.print( os );
  return os;
}
