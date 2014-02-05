#include "Polynomial.hpp"

/* Default constructor */
Polynomial::Polynomial() {
}

/* takes a c-string with a polynomial in the given format "exp coeff exp coeff etc..." */
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

/* copy constructor */
Polynomial::Polynomial( const Polynomial& other ) {
  copy( other );
}

/* copy method that just calls LinkedList copy */
void Polynomial::copy( const Polynomial& other ) {
  _list.copy( other._list );
}

/* returns the degree of the polynomial, useful for the division function */
int Polynomial::degree() const {
  return _list.get(0).degree();
}

/* adds a Term to the Polynomial */
void Polynomial::addTerm( const Term& aTerm ) {
  addTerm( aTerm.coeff, aTerm.exp );
}

/* adds a term to the Polynomial given coeff and exp */
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
	  if( it.getData().coeff == 0 ) // if 0 then don't add it
	    _list.remove( it );
	  return;
	}
      if( curr_exp < exp )
	break;
    }

  _list.insert( term );
}

/* turns out I don't actually need the subtraction function, but I already had it */
/* just reverse the coefficient and add it */
void Polynomial::subTerm( double coeff, int exp ) {
  addTerm( -1 * coeff, exp );
}

/* destructor doesn't need to do anything */
Polynomial::~Polynomial() {
}

/* add two polynomials together */
const Polynomial Polynomial::add( const Polynomial& rhs ) const {
  Polynomial retVal;

  for( itr_t it = _list.begin(); it != _list.end(); ++it )
    retVal.addTerm( it.getData().coeff, it.getData().exp );

  for( itr_t it = rhs._list.begin(); it != rhs._list.end(); ++it )
    retVal.addTerm( it.getData().coeff, it.getData().exp );
  return retVal;
}

/* again, I don't actually need this function */
const Polynomial Polynomial::sub( const Polynomial& rhs ) const {
  Polynomial retVal;

  for( itr_t it = _list.begin(); it != _list.end(); ++it )
    retVal.addTerm( it.getData().coeff, it.getData().exp );
  for( itr_t it = rhs._list.begin(); it != rhs._list.end(); ++it )
    retVal.subTerm( it.getData().coeff, it.getData().exp );
  return retVal;
}

/* multiply two polynomials together */
const Polynomial Polynomial::mult( const Polynomial& rhs ) const {
  Polynomial retVal;
  for( itr_t it = _list.begin(); it != _list.end(); ++it )
    {
      for( itr_t rit = rhs._list.begin(); rit != rhs._list.end(); ++rit )
	{
	  Term aterm = it.getData() * rit.getData();
	  if( aterm.coeff != 0 ) // don't have to have this check, since addTerm() already does it, but it can save a function jump
	    {
	      retVal.addTerm( aterm.coeff, aterm.exp );
	    }
	}
    }
  return retVal;
}

// doesn't return a remainder
// N.B. this function will break if there is a remainder
const Polynomial Polynomial::div( const Polynomial& rhs ) const {
  Polynomial retVal;

  if( degree() < rhs.degree() )
    {
      return retVal; // return 0
    }

  Polynomial rSide( *this );
  int rDeg = rhs.degree();
  double rCoeff = rhs._list.begin().getData().coeff;
  
  itr_t it = rSide._list.begin();
  while( 1 )
    {
      if( it == rSide._list.end() ) break;
      int deg_diff = it.getData().degree() - rDeg;
      if( deg_diff < 0 ) break; // TODO: check this condition, maybe need to put rest into remainder?
      
      double coeff = it.getData().coeff / rCoeff;
      Polynomial tmp;
      Term multiplier( coeff, deg_diff );
      retVal.addTerm( multiplier );
      
      for( itr_t itt = rhs._list.begin(); itt != rhs._list.end(); ++itt )
	{
	  Term res = itt.getData() * multiplier;
	  tmp.addTerm( res );
	}

      rSide = rSide.sub( tmp );
      it = rSide._list.begin();
    }
  
  return retVal;
}

/* evaluates the polynomial at a given point */
double Polynomial::eval( double point ) {
  double retVal = 0;

  /* just iterate through list and add the result */
  for( itr_t it = _list.begin(); it != _list.end(); ++it )
    {
      retVal += it.getData().coeff * pow( point, it.getData().exp );
    }
  return retVal;
}

/* differentiate the polynomial and return  */
/* since this class only holds polynomials, */
/* differentiation is simple, just multiply */
/* the coefficient by the exponent, and     */
/* decrement the coefficient                */
const Polynomial Polynomial::differentiate() {
  Polynomial retVal;

  for( itr_t it = _list.begin(); it != _list.end(); ++it )
    {
      int exp = it.getData().exp;
      double coeff = it.getIter()->_data->coeff * exp;

      if( (coeff != 0) && (exp != 0) )
	{
	  exp--;
	  retVal.addTerm( coeff, exp );
	}
    }

  return retVal;
}

/* integrate the polynomial and return       */
/* since this class only holds polynomials   */
/* itegration is easy. Just increment the    */
/* exponent and divide the coefficient by it */
const Polynomial Polynomial::integrate() {
  Polynomial retVal;

  for( itr_t it = _list.begin(); it != _list.end(); ++it )
    {
      int exp = it.getData().exp;
      exp++;
      double coeff = it.getIter()->_data->coeff / static_cast<double>(exp);
      retVal.addTerm( coeff, exp );
      // no way for a term to now be zero, so don't need to check
    }
  
  return retVal;
}

/* print the polynomial to the given ostream        */
/* don't need to check for 0 coefficients           */
/* because there is no way for them to have         */
/* been addded to the Polynomial in the first place */
void Polynomial::print( std::ostream& os ) const {
  itr_t it = _list.begin();

  if( it == _list.end() )
    {
      cout << "0";
      return;
    }

  if( it != _list.end() )
    {
      if( it.getData().coeff < 0.0f )
	os << "-";
      if( it != _list.begin() )
	os << " ";
      os << it.getData() << " ";
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

/* overload operator::= to be the copy constructor */
Polynomial& Polynomial::operator=( const Polynomial& rhs ) {
  copy( rhs );
  return *this;
}

/* overload the insertion operator to print the polynomial */
std::ostream& operator<<( std::ostream& os, const Polynomial& rhs ) {
  rhs.print( os );
  return os;
}
