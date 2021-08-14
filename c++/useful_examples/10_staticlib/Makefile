LIB   = libfunctions.a
CXX       = g++
CXXFLAGS  = -O3 -g -std=c++20 -Wall -Wextra -Wpedantic
LDFLAGS   = 

$(LIB): functions.o
	ar rvs $@ $^

functions.o: functions.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


main.out: main.cpp libfunctions.a
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) 



.PHONY: clean dist

clean:
	-rm *.o *.out *.so *.a $(PROGRAM)

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *
