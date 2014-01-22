#ifndef _LINKEDLIST_HPP_
#define _LINKEDLIST_HPP_

#include "Node.hpp"
#include "DecreasingOrderSort.hpp"
#include "Exception.hpp"

namespace LinkedList {

  template
  <
    class T,
    template <class> class SortingPolicy = SortingPolicies::DecreasingOrderSort
  >
  class LinkedList {
  public:
    explicit LinkedList() {
      _head = NULL;
      _begin.setStatus(iterator::BEGIN);
      _end.setStatus(iterator::END);
    } /* end LinkedList() */

    virtual ~LinkedList() {
      delete _head;
    } /* end ~LinkedList() */

    bool isEmpty() {
      return (_head == NULL) ? true : false;
    }

    void insert( const T& val ) {
      if( _head == NULL )
	{
	  _head = new Node<T>(val);
	  return;
	}

      Node<T> * node = _head;
      if( SortingPolicy<T>::putBefore( val, node->data()) )
	{
	  Node<T> * newNode = new Node<T>( val, _head );
	  _head = newNode;
	  return;
	}

      while( node->next() != NULL )
	{
	  if( SortingPolicy<T>::putBefore( val, node->next()->data() ) )
	    {
	      Node<T> * newNode = new Node<T>( val, node->next() );
	      node->_next = newNode;
	      return;
	    }
	  node = node->next();
	}

      /* putting the node at the end of the list */
      node->_next = new Node<T>( val );
      return;
    } /* end insert() */

    const T& get( int index ) {
      if( isEmpty() ) throw Exception("Tried to access data in empty list");
      if( index < 0 ) throw Exception("Tried to access with negative position");

      Node<T> * node = _head;
      for( int i = 0; i < index; ++i )
	{
	  if( node == NULL ) throw Exception("Tried to access data beyond bounds of list");

	  node = node->next();
	}

      if( node == NULL ) throw Exception("Tried to access data beyond bounds of list");
      else return node->data();
    } /* end get() */

    void set( const T& val, int index ) { /* TODO */ }

    int size() {
      Node<T> * n = _head;
      int count = 0;
      while( n != NULL )
	{
	  n = n->_next;
	  count++;
	}

      return count;
    }

    int length() {
      return size();
    }

    /************************************************/
    class iterator
    {
    public:
      enum Status { BEGIN = 0, END, MIDDLE };
    public:
      explicit iterator() {
	_iter = NULL;
	_status = BEGIN;
      }
      
      explicit iterator(const typename LinkedList<T>::iterator& it) {
	_iter = it.getData();
	_status = it.getStatus();
      }

      virtual ~iterator() {
      }
      
      void forward() {
	if( _status == BEGIN ) {
	  _iter = _head;
	  _status = MIDDLE;
	  return;
	}
	
	if( _status == END )
	  return;
	  
	if( _iter->next() != NULL )
	  _iter->next();
	else
	  {
	    _iter = NULL;
	    _status = END;
	  }
      }

      const T& getData() {
	return _iter->data();
      }

      Status getStatus() {
	return _status;
      }

      void setIter(Node<T> * node) {
	_iter = node;
        _status = (node != NULL) ? MIDDLE : END;
      }

      void setStatus(Status status) {
	_status = status;
      }

      typename LinkedList<T>::iterator& operator=( const typename LinkedList<T>::iterator& rhs ) {
	if( this == &rhs )
	  return *this;
	else
	  {
	    _iter = rhs._data;
	    _status = rhs._status;
	    return *this;
	  }
      }

      bool operator==( const typename LinkedList<T>::iterator& rhs ) {
	if( (_status == BEGIN) && (rhs._status == BEGIN) ) return true;
	else if( (_status == END) && (rhs._status == END) ) return true;
	else if( _iter == rhs._iter ) return true;
	else return false;
      }

      bool operator!=( const typename LinkedList<T>::iterator& rhs ) {
	return !(*this == rhs);
      }

      typename LinkedList<T>::iterator operator++() {
	forward();
	return *this;
      }

      typename LinkedList<T>::iterator operator++(int) {
	typename LinkedList<T>::iterator t(*this); // save obj
	forward();
	return t;
      }

    private:
      Node<T> * _iter;
      Status _status;
    };
    /************************************************/

    const typename LinkedList<T>::iterator& begin() {
      return _begin;
    }

    const typename LinkedList<T>::iterator& end() {
      return _end;
    }

  private:
    Node<T> * _head;
    typename LinkedList<T>::iterator _begin;
    typename LinkedList<T>::iterator _end;
  };

}

#endif
