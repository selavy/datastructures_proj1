#ifndef _DECREASINGORDERSORT_HPP_
#define _DECREASINGORDERSORT_HPP_

namespace SortingPolicies {

  template <class T>
  struct DecreasingOrderSort
  {
    static bool putBefore (const T& a, const T& b) {
      return a < b;
    }
  };

}

#endif
