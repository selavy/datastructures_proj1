#ifndef _USENODELIST_HPP_
#define _USENODELIST_HPP_

#include "MyStd.hpp"
#include "Node.hpp"

namespace AllocationPolicies
{

  /* For this assignment we are required to use our own
     version of "free store"--a linked list holding available
     nodes.  If a node isn't in the free store, then we can
     use new to get another node */

  /* The linked list here is singly linked since all nodes
     are the same for our purposes */
  template <class T>
    struct UseNodeList {

    static Node<T> * newNode( int val, Node<T> * nnode, Node<T> * pnode ) {
      if( _head == NULL )
	return new Node<T>( val, nnode, pnode );
      else
	{
	  Node<T> * head = _head;
	  _head = _head->next();
	  head->_data = new T(val);
	  head->_next = nnode;
	  head->_prev = pnode;
	  return head;
	}
    }

    static Node<T> * newNode( int val, Node<T> * nnode ) {
      return newNode( val, nnode, NULL );
    }
      
    static Node<T> * newNode( int val ) {
      return newNode( val, NULL, NULL );
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
  };

  template <class T> Node<T> * UseNodeList<T>::_head = NULL;
}

#endif
