#ifndef _NODE_HPP_
#define _NODE_HPP_

#ifndef NULL
#define NULL 0
#endif

#include <cstring>

template <class T>
struct Node {
  explicit Node();
  explicit Node( const T& data, Node * next = NULL );
  virtual ~Node();
 
  struct Node * next();
  const T& data();

  T* _data;
  struct Node * _next;
};

/* Since templates still don't really work, can't separate */
/* declaration and definition.  Having these functions     */
/* inline shouldn't increase code size much.               */

template <class T>
Node<T>::Node() {
  _data = NULL;
  _next = NULL;
}

template <class T>
Node<T>::Node( const T& data, Node<T> * next ) {
  _data = new T(data);
  _next = next;
}

template <class T>
Node<T>::~Node() {
  if( _data != NULL )
    delete _data;
  if( _next != NULL )
    delete _next;
}

template <class T>
struct Node<T> * Node<T>::next() {
  return _next;
}

template <class T>
const T& Node<T>::data() {
  return *_data;
}

#endif
