CPP = g++
CFLAGS = -Wall -Werror -pedantic -ansi -g -frepo

OBJS = main.o Exception.o Polynomial.o # LinkedList.o 
TEMPLATES = LinkedList.hpp Node.hpp DecreasingOrderSort.hpp IncreasingOrderSort.hpp FIFOSort.hpp
HEADERS = Term.hpp MyStd.hpp UseNew.hpp UseNodeList.hpp UseDelete.hpp
TESTS = test_add test_mult test_div test_diff test_int

proj1: $(OBJS) $(TEMPLATES) $(HEADERS)
	$(CPP) $(CFLAGS) $(OBJS) -o proj1
main.o: main.cpp $(TEMPLATES) $(HEADERS)
	$(CPP) -c $(CFLAGS) main.cpp
Polynomial.o: Polynomial.hpp Polynomial.cpp $(TEMPLATES) $(HEADERS)
	$(CPP) -c $(CFLAGS) Polynomial.cpp
Exception.o: Exception.hpp Exception.cpp
	$(CPP) -c $(CFLAGS) Exception.cpp

# tests
test: $(TESTS)
test_add: proj1
	echo "Checking addition functionality..."
	./proj1 test_add.txt > out_add.txt
	diff -b -B out_add.txt correct_test_add.txt
test_mult: proj1
	./proj1 test_mult.txt > out_mult.txt
	diff -b -B out_mult.txt correct_test_mult.txt
test_div: proj1
	./proj1 test_div.txt > out_div.txt
	diff -b -B out_div.txt correct_test_div.txt
test_diff: proj1
	./proj1 test_diff.txt > out_diff.txt
	diff -b -B out_diff.txt correct_test_diff.txt
test_int: proj1
	./proj1 test_int.txt > out_int.txt
	diff -b -B out_int.txt correct_test_int.txt

# These were moved to templates so don't need to compile
#LinkedList.o: LinkedList.hpp LinkedList.cpp
#	$(CPP) -c $(CFLAGS) LinkedList.cpp
#Node.o: Node.hpp Node.cpp
#	$(CPP) -c $(CFLAGS) Node.cpp

clean:
	rm -rf *.o *.rpo proj1 out_*.txt
