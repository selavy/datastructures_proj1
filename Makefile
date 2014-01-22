CPP = g++
CFLAGS = -Wall -Werror -pedantic -ansi -g -frepo

OBJS = main.o Exception.o Polynomial.o # LinkedList.o 
TEMPLATES = LinkedList.hpp Node.hpp DecreasingOrderSort.hpp IncreasingOrderSort.hpp FIFOSort.hpp UseNew.hpp UseNodeList.hpp
HEADERS = Term.hpp MyStd.hpp

proj1: $(OBJS)
	$(CPP) $(CFLAGS) $(OBJS) -o proj1
main.o: main.cpp $(TEMPLATES) $(HEADERS)
	$(CPP) -c $(CFLAGS) main.cpp
Polynomial.o: Polynomial.hpp Polynomial.cpp
	$(CPP) -c $(CFLAGS) Polynomial.cpp
Exception.o: Exception.hpp Exception.cpp
	$(CPP) -c $(CFLAGS) Exception.cpp

# These were moved to templates so don't need to compile
#LinkedList.o: LinkedList.hpp LinkedList.cpp
#	$(CPP) -c $(CFLAGS) LinkedList.cpp
#Node.o: Node.hpp Node.cpp
#	$(CPP) -c $(CFLAGS) Node.cpp

clean:
	rm -rf *.o *.rpo proj1
