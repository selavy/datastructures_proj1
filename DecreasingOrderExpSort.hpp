#ifndef _DECREASINGORDEREXPSORT_HPP_
#define _DECREASINGORDEREXPSORT_HPP_

#include "Term.hpp"

namespace SortingPolicies {
  
  template <class T>
  struct DecreasingOrderExpSort
  {
    static bool putBefore(const T& a, const T& b) {
      return a < b;
    }

    static bool putBefore(const Term& a, const Term& b) {
      return a.exp < b.exp;
    }
  };

}

#endif
