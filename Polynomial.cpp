#include "Polynomial.hpp"

Polynomial::Polynomial() {
}

Polynomial::Polynomial( char * poly ) {
  /* have to assume that the string is null terminated */
  char curr[SLEN];
  int index = 0;
  curr[0] = '\0';
  double coeff = 0.0f;
  int exp = 0;

  // true => coeff, false => exp
  bool mode = true;

  for( int i = 0; (i < SLEN) && (poly[i] != '\0'); ++i )
    {
      if( (poly[i] == ' ') && mode )
	{
	  curr[index] = '\0';
	  coeff = atof(curr);
	  mode = false;
	  index = 0;
	}      
      else if( (poly[i] == ' ') && !mode )
	{
	  curr[index] = '\0';
	  exp = atoi(curr);
	  mode = true;
	  addTerm( coeff, exp );
	  index = 0;
	}
      else
	{
	  curr[index] = poly[i];
	  index++;
	}
    }

  
  // the last set of terms will have been collected, but not trigger poly[i] == ' '
  curr[index] = '\0';
  exp = atoi(curr);
  addTerm( coeff, exp );
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

const Polynomial Polynomial::mult( const Polynomial& rhs ) const {
  Polynomial retVal;
  for( itr_t it = _list.begin(); it != _list.end(); ++it )
    {
      for( itr_t rit = rhs._list.begin(); rit != rhs._list.end(); ++rit )
	{
	  Term aterm = it.getData() * rit.getData();
	  if( aterm.coeff != 0 )
	    {
	      retVal.addTerm( aterm.coeff, aterm.exp );
	    }
	}
    }
  return retVal;
}

const Polynomial Polynomial::div( const Polynomial& rhs ) const {
  Polynomial retVal;
  return retVal;
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
  for( itr_t it = _list.begin(); it != _list.end(); ++it )
    {
      it.getIter()->_data->exp++;
      int exp = it.getData().exp;
      it.getIter()->_data->coeff /= static_cast<double>(exp);
      // no way for a term to now be zero, so don't need to check
    }
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
