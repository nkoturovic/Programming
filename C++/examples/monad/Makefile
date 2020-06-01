PROGRAM   = main.out
CXX       = g++
CXXFLAGS  = -g -std=c++2a -Wall -Wextra -Wpedantic -O3

$(PROGRAM): main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *
