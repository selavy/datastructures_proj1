#ifndef _LINKEDLIST_HPP_
#define _LINKEDLIST_HPP_

#include <iostream>
using namespace std;

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
      _begin.setIter(_head);
      _end.setStatus(iterator::END);
    } /* end LinkedList() */

    LinkedList( const LinkedList& other ) {
      copy( other );
    }

    void copy( const LinkedList& other ) {
      clear();
      Node<T> * node = other._head;
      while( node != NULL )
	{
	  insert( node->data() );
	  node = node->next();
	}

      _begin.setIter(_head);
    }

    virtual ~LinkedList() {
      clear();
    } /* end ~LinkedList() */

    void printVisual() {
      Node<T> * node = _head;
      while( node != NULL )
	{
	  if( node->prev() != NULL )
	    cout << "<-";
	  else
	    cout << "|-";
	  cout << node->data();
	  if( node->next() != NULL )
	    cout << "->";
	  else
	    cout << "-|";
	  node = node->next();
	}
      cout << endl;
    }
 
    bool isEmpty() {
      return (_head == NULL) ? true : false;
    }
    
    void insert( const T& val ) {
      if( _head == NULL )
	{
	  _head = AllocationPolicy<T>::newNode( val );
	  _begin.setIter(_head);
	  return;
	}

      Node<T> * node = _head;
      if( SortingPolicy<T>::putBefore( val, node->data() ) )
	{
	  Node<T> * newNode =  AllocationPolicy<T>::newNode( val, _head );
	  _head->_prev = newNode;
	  _head = newNode;
	  _begin.setIter(_head);
	  return;
	}

      while( node->next() != NULL )
	{
	  if( SortingPolicy<T>::putBefore( val, node->next()->data() ) )
	    {
	      Node<T> * newNode = AllocationPolicy<T>::newNode( val, node->next(), node ); /* new Node<T>( val, node->next() ); */
	      node->next()->_prev = newNode;
	      node->_next = newNode;
	      return;
	    }
	  node = node->next();
	}

      /* putting the node at the end of the list */
      node->_next = AllocationPolicy<T>::newNode( val, NULL, node ); /* new Node<T>( val ); */
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
 	    _iter = rhs._iter;
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
      
    private:
      Node<T> * _iter;
      Status _status;
    };
    /************************************************/

    const typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator& begin() const {
      return _begin;
    }

    const typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator& end() const {
      return _end;
    }

    void remove( typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator& it ) {
      Node<T> * node = it.getIter();
      if( node == NULL ) return;

      Node<T> * prev = node->prev();
      Node<T> * next = node->next();

      if( node == _head )
	_head = next;

      it.setIter( prev );
      it.setStatus( ( it.getIter() == NULL ) ?
        LinkedList<T, SortingPolicy, AllocationPolicy>::iterator::BEGIN :
			     LinkedList<T, SortingPolicy, AllocationPolicy>::iterator::MIDDLE);
	
      
      if( prev != NULL )
	prev->_next = next;
      if( next != NULL )
	next->_prev = prev;

      AllocationPolicy<T>::removeNode( node );
    }

    void remove( int index ) {
      if( index < 0 ) return;
      typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator it = begin();
      for( int i = 0; (i < index) && (it != end()); ++i)
	it++;

      remove(it);
    }

    void clear() {
      Node<T> * node = _head;
      Node<T> * tmp;

      while( node != NULL )
	{
	  tmp = node->next();
	  AllocationPolicy<T>::removeNode( node );
	  node = tmp;
	  if( node != NULL )
	    node->_prev = NULL;
	}

      _head = NULL;
    }

  private:
    Node<T> * _head;
    typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator _begin;
    typename LinkedList<T, SortingPolicy, AllocationPolicy>::iterator _end;
  };

}

#endif
