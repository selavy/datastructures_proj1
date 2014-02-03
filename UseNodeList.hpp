#ifndef _USENODELIST_HPP_
#define _USENODELIST_HPP_

#include "MyStd.hpp"
#include "Node.hpp"

#ifndef _MMEM_CHECK_
//#define _MMEM_CHECK_
#endif

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

    static Node<T> * newNode( const T& val, Node<T> * nnode, Node<T> * pnode ) {
      if( _head == NULL )
	return new Node<T>( val, nnode, pnode );
      else
	{
	  Node<T> * head = _head;
	  _head = _head->next();
	  if( head->_data != NULL )
	    delete head->_data;
	  head->_data = new T(val);
	  head->_next = nnode;
	  head->_prev = pnode;
#ifdef _MMEM_CHECK_
	  cout << "Returning node #" << head->id << " from the free store" << endl;
	  printFreeStore();
#endif
	  return head;
	}
    }

    static Node<T> * newNode( const T& val, Node<T> * nnode ) {
      return newNode( val, nnode, NULL );
    }
      
    static Node<T> * newNode( const T& val ) {
      return newNode( val, NULL, NULL );
    }

#ifdef _MMEM_CHECK_
    static void printFreeStore() {
      Node<T> * node = _head;
      int i = 0;
      cout << "Free store: ";
      while( node != NULL )
	{
	  cout << node->id << " ";
	  node = node->next();
	  ++i;
	}
      cout << endl;
      int sze = sizeof(Node<T>);
      cout << i << " nodes allocated accounting for: " << i * sze << " bytes." << endl;
    }
#endif
    
    static void removeNode( Node<T> * node )
    {
#ifdef _MMEM_CHECK_
      cout << "Adding node #" << node->id << " to the free store; ";
#endif
      node->_next = NULL;
      node->_prev = NULL;

      if( node->_data != NULL )
	{
	  delete node->_data;
	  node->_data = NULL;
	}

      if( _head == NULL )
	{
	  _head = node;
	}
      else
	{
	  node->_next = _head;
	  _head = node;
	}

#ifdef _MMEM_CHECK_
      cout << "Head is now: #" << _head->id << endl;
      printFreeStore();
#endif
    }

    /* I have to add this hacky function because otherwise
       this design would lead to a memory leak. */
    /* User MUST call this function at the end of the 
       program */
    static void deleteFreeStore()
    {
#ifdef _MMEM_CHECK_
      cout << "deleteFreeStore()" << endl;
#endif
      Node<T> * node = _head;
      Node<T> * tmp;
      
      while( node != NULL )
	{
	  tmp = node;
	  delete node;
	  node = tmp->next();
	}

      _head = NULL;
    }

    static Node<T> * _head;
  };

  template <class T> Node<T> * UseNodeList<T>::_head = NULL;
}

#endif
