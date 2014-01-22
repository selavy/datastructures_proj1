#ifndef _INCREASINGORDERSORT_HPP_
#define _INCREASINGORDERSORT_HPP_

namespace SortingPolicies {
  
  template <class T>
  struct IncreasingOrderSort
  {
    bool operator() (const T& a, const T& b) {
      return a > b;
    }
  };

}

#endif
