#include <iostream>
#include "LinkedList.hpp"
#include "Node.hpp"
#include "Exception.hpp"
#include "FIFOSort.hpp"

using namespace std;

int main( int argc, char ** argv )
{
  LinkedList::LinkedList<int> aList;
  aList.insert(1);
  aList.insert(2);
  aList.insert(4);
  aList.insert(3);

  int size = aList.size();
  for( int i = 0; i < size; ++i )
    cout << aList.get(i) << " ";
  cout << endl;
  return 0;
}
