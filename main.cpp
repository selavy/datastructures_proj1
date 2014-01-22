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

  //int size = aList.size();
  //  for( int i = 0; i < size; ++i )
  for( LinkedList::LinkedList<int>::iterator it = aList.begin(); it != aList.begin(); it++ )
    cout << it.getData() << " ";
  cout << endl;
  return 0;
}
