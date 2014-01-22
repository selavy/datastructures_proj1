#ifndef _USENEW_HPP_
#define _USENEW_HPP_

#include "Node.hpp"

namespace AllocationPolicies
{
  
  template <class T>
  struct UseNew {
    Node<T> * newNode( int val, Node<T> * node ) {
      return new Node<T>( val, node );
    }

    Node<T> * newNode( int val ) {
      return new Node<T>( val );
    }
  };

}

#endif
