#ifndef _NODE_HPP_
#define _NODE_HPP_

#include "MyStd.hpp"
#include <cstring>

#ifndef _MMEM_CHECK_
//#define _MMEM_CHECK_
#endif

template <class T>
struct Node {
  explicit Node();
  explicit Node( const T& data, Node * next = NULL );
  explicit Node( const T& data, Node * next, Node * prev);
  virtual ~Node();
 
  struct Node * next();
  struct Node * prev();
  const T& data();

  T* _data;
  struct Node * _next;
  struct Node * _prev;

#ifdef _MMEM_CHECK_
  int id;
  static unsigned int next_id;
#endif
};

#ifdef _MMEM_CHECK_
template <class T>
/* static */ unsigned int Node<T>::next_id = 0;
#endif

/* Since templates still don't really work, can't separate */
/* declaration and definition.  Having these functions     */
/* inline shouldn't increase code size much.               */

template <class T>
Node<T>::Node() {
  _data = NULL;
  _next = NULL;

#ifdef _MMEM_CHECK_
  id = next_id;
  cout << "Creating node #" << id << endl;
  next_id++;
#endif
}

template <class T>
Node<T>::Node( const T& data, Node<T> * next ) {
  Node( data, next, NULL );
}

template <class T>
Node<T>::Node( const T& data, Node<T> * next, Node<T> * prev ) {
  _data = new T(data);
  _next = next;
  _prev = prev;

#ifdef _MMEM_CHECK_
  id = next_id;
  cout << "Creating node #" << id << endl;
  next_id++;
#endif
}

template <class T>
Node<T>::~Node() {
#ifdef _MMEM_CHECK_
  cout << "Deleting node #" << id << endl;
#endif

  if( _data != NULL )
    delete _data;
  _data = NULL;
}

template <class T>
struct Node<T> * Node<T>::next() {
  return _next;
}

template <class T>
struct Node<T> * Node<T>::prev() {
  return _prev;
}

template <class T>
const T& Node<T>::data() {
  return *_data;
}

#endif
