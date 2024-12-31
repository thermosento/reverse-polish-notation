.PHONY = all clean

# compile everything; this is the default rule that fires if a user
# just types "make" in the same directory as this Makefile
all: test_suite rpn


test_suite: catch.o test_suite.o test_deque.o Deque.o
	clang++-15 -g3 -gdwarf-4 -Wall --std=c++20 -o test_suite catch.o test_suite.o test_deque.o Deque.o

catch.o: catch.cpp catch.hpp
	clang++-15 -g3 -gdwarf-4 -Wall --std=c++20 -c catch.cpp

test_deque.o: test_deque.cpp Deque.h catch.cpp catch.hpp
	clang++-15 -g3 -gdwarf-4 -Wall --std=c++20 -c test_deque.cpp

test_suite.o: test_suite.cpp catch.cpp catch.hpp
	clang++-15 -g3 -gdwarf-4 -Wall --std=c++20 -c test_suite.cpp

rpn: rpn.o Deque.o
	clang-15 -g3 -gdwarf-4 -Wall -o rpn rpn.o Deque.o

rpn.o: rpn.c Deque.h rat_num.h
	clang-15 -g3 -gdwarf-4 -Wall -c rpn.c

Deque.o: Deque.c Deque.h rat_num.h
	clang-15 -g3 -gdwarf-4 -Wall -c Deque.c

clean:
	rm -f *.o *~ test_suite rpn
