#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

#include <new>
#include <cstring>

class Exception
{
public:
  explicit Exception();
  explicit Exception(const char * msg);
  virtual ~Exception();

  virtual const char* what() const;
private:
  char * _msg;
};

#endif
