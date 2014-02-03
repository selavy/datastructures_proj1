#ifndef _USEDELETE_HPP_
#define _USEDELETE_HPP_

namespace DeallocationPolicies
{
  template <class T>
  struct UseDelete {
    static void removeNode( Node<T> * node )
    {
      delete node;
    }

    static void deleteFreeStore() {
      return;
    }
  };
}

#endif
