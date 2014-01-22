#ifndef _USENEW_HPP_
#define _USENEW_HPP_

#include "MyStd.hpp"
#include "Node.hpp"

namespace AllocationPolicies
{
  
  template <class T>
  struct UseNew {
    static Node<T> * newNode( const T& val, Node<T> * nnode, Node<T> * pnode ) {
      return new Node<T>( val, nnode, pnode );
    }

    static Node<T> * newNode( const T& val, Node<T> * nnode ) {
      return newNode( val, nnode, NULL );
    }

    static Node<T> * newNode( const T& val ) {
      return newNode( val, NULL, NULL );
    }
  };

}

#endif
