#ifndef _FIFOSORT_HPP_
#define _FIFOSORT_HPP_

namespace SortingPolicies {

  template <class T>
  struct FIFOSort
  {
    bool operator() (const T& a, const T& b) {
      return false;
    }
  };

}

#endif
