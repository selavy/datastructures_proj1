#include "Exception.hpp"

Exception::Exception() {
  _msg = new char;
  _msg = '\0';
}

Exception::Exception( const char * msg ) {
  if( msg == NULL )
    {
      Exception();
    }
  else
    {
      size_t len = strlen(msg) + 1;
      _msg = new char[ len + 1 ];
      memcpy( _msg, msg, len );
      _msg[ len ] = '\0'; /* just in case */
    }
}

Exception::~Exception() {
  delete _msg;
}

const char * Exception::what() const {
  return _msg;
}




