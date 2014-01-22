#ifndef _USENEW_HPP_
#define _USENEW_HPP_

#include "MyStd.hpp"
#include "Node.hpp"

namespace AllocationPolicies
{
  
  template <class T>
  struct UseNew {
    Node<T> * newNode( int val, Node<T> * nnode, Node<T> * pnode ) {
      return new Node<T>( val, nnode, pnode );
    }

    Node<T> * newNode( int val, Node<T> * nnode ) {
      return newNode( val, nnode, NULL );
    }

    Node<T> * newNode( int val ) {
      return newNode( val, NULL, NULL );
    }
  };

}

#endif
