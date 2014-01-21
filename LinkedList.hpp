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

    /************************************************/
    /*
    class iterator
    {
    public:
      enum Status { begin = 0, end, middle };
    public:
      explicit iterator() {
      }

      virtual ~iterator() {
      }
      
      void forward() {
      }

      static iterator begin() {
	return _begin;
      }

      static iterator end() {
	return _end;
      }

    private:
      Node<T> * _iter;
      static const iterator _begin;
      static const iterator _end;
      Status _status;
    }
    */
    /************************************************/

  private:
    Node<T> * _head;
  };

}

#endif
