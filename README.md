datastructures_proj1
====================

Data Structures Project 1: Polynomial Package

To run:
>make
>./proj1 <input_file>

To run on test scripts:
>make test

For the LinkedList class I have used some template metaprogramming and
Policy-based design.  So several of the files in here are not used, 
but show how other memory allocation and deletion policies could be used
(such as UseNew.hpp UseDelete.hpp, IncreasingOrderSort.hpp, FIFOSort.hpp).
The allocation policies used by the Polynomial class are DecreasingOrderSort,
and UseNodeList.hpp.  Pursuant to the specificiations, the linked list
checks a free store of nodes first before allocating more memory.  This results
a slightly awkward implementation where the top-level user must call
UseNodeList::deleteFreeStore() otherwise memory is leaked.  But, as long as
the user does call this method, no memory is leaked (as verified by valgrind).
