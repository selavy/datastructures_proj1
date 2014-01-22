#ifndef _USENODELIST_HPP_
#define _USENODELIST_HPP_

#include "Node.hpp"

#ifndef NULL
#define NULL 0
#endif

namespace AllocationPolicies
{

  template <class T>
    struct UseNodeList {

    static Node<T> * newNode( int val, Node<T> * node ) {
      if( _head == NULL )
	return new Node<T>( val, node );
      else
	{
	  Node<T> * head = _head;
	  _head = _head->next();
	  head->_data = new T(val);
	  head->_next = node;
	    return head;
	  }
      }
      
      static Node<T> * newNode( int val ) {
	if( _head == NULL )
	  return new Node<T>( val );
	else
	  {
	    Node<T> * head = _head;
	    _head = _head->next();
	    head->_data = new T(val);
	    head->_next = NULL;
	    return head;
	  }
      }

    static void removeNode( Node<T> * node )
    {
      node->_next = _head;
      _head = node;
    }

    /* I have to add this hacky function because otherwise
       this design would lead to a memory leak. */
    /* User MUST call this function at the end of the 
       program */
    static void deleteFreeStore()
    {
      Node<T> * node = _head;
      Node<T> * tmp;
      while( node != NULL )
	{
	  tmp = node;
	  delete node;
	  node = tmp->next();
	}
    }

    static Node<T> * _head;
    static int count;
  };

  template <class T> Node<T> * UseNodeList<T>::_head = NULL;
  template <class T> int UseNodeList<T>::count = 0;
}

#endif
