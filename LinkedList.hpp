#ifndef _LINKEDLIST_HPP_
#define _LINKEDLIST_HPP_

#include "Node.hpp"
#include "IncreasingOrderSort.hpp"
#include "UseNew.hpp"
#include "Exception.hpp"

namespace LinkedList {

  template
  <
    class T,
    template <class> class SortingPolicy = SortingPolicies::IncreasingOrderSort,
    template <class> class AllocationPolicy = AllocationPolicies::UseNew
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
	  _head = AllocationPolicy<T>::newNode( val ); /* new Node<T>( val ); */
	  return;
	}

      Node<T> * node = _head;
      if( SortingPolicy<T>( val, node->data() ) )
	{
	  Node<T> * newNode =  AllocationPolicy<T>::newNode( val, _head ); /* new Node<T>( val, _head ); */
	  _head = newNode;
	  return;
	}

      while( node->next() != NULL )
	{
	  if( SortingPolicy<T>::putBefore( val, node->next()->data() ) )
	    {
	      Node<T> * newNode = AllocationPolicy<T>::newNode( val, node->next() ); /* new Node<T>( val, node->next() ); */
	      node->_next = newNode;
	      return;
	    }
	  node = node->next();
	}

      /* putting the node at the end of the list */
      node->_next = AllocationPolicy<T>::newNode( val ); /* new Node<T>( val ); */
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
      enum Status { NOP = 0, BEGIN, END, MIDDLE };
    public:
      explicit iterator() {
	_iter = NULL;
	_status = NOP;
      }
      
      iterator(const typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator& it) {
	_iter = it._iter;
	_status = it._status;
      }

      virtual ~iterator() {
      }
      
      void forward() {
	if( _status == NOP )
	  return;
	else if( _status == BEGIN ) {
	  _status = MIDDLE;
	  return;
	}
	else if( _status == END ) {
	  return;
	}
	else if( _iter->next() != NULL )
	  {
	    _iter = _iter->next();
	  }
	else
	  {
	    _iter = NULL;
	    _status = END;
	  }
      }

      const T& getData() {
	return _iter->data();
      }

      Node<T> * getIter() {
	return _iter;
      }

      void setIter(Node<T> * node) {
	_iter = node;
        _status = (node != NULL) ? MIDDLE : END;
      }

      void setStatus(Status status) {
	_status = status;
      }

      typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator& operator=( const typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator& rhs ) {
	if( this == &rhs )
	  return *this;
	else
	  {
	    _iter = rhs._data;
	    _status = rhs._status;
	    return *this;
	  }
      }

      bool operator==( const typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator& rhs ) {
	if( (_status == BEGIN) && (rhs._status == BEGIN) ) return true;
	else if( (_status == END) && (rhs._status == END) ) return true;
	else if( _iter == rhs._iter ) return true;
	else return false;
      }

      bool operator!=( const typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator& rhs ) {
	return !(*this == rhs);
      }

      typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator operator++() {
	forward();
	return *this;
      }

      typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator operator++(int) {
	typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator t(*this); // save obj
	forward();
	return t;
      }

      Node<T> * getNode() {
	return _iter;
      }
      
      void insertAfter( const typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator& itr, T& val ) {
	Node<T> * newNode = AllocationPolicy<T>::newNode( val ); /* new Node<T>( val ); */
	newNode._next = itr._iter;
	itr._iter = newNode;
      }

    private:
      Node<T> * _iter;
      Status _status;
    };
    /************************************************/

    typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator& begin() {
      _begin.setIter( _head );
      return _begin;
    }

    typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator& end() {
      return _end;
    }

    void remove( typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator& it ) {
      Node<T> * node = it.getIter();
      /* TODO */
      
    }

  private:
    Node<T> * _head;
    typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator _begin;
    typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator _end;
  };

}

#endif
