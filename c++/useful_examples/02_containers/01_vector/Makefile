PROGRAM   = main.out
CXX       = g++
CXXFLAGS  = -g -std=c++20 -Wall -Wextra -Wpedantic
LDFLAGS   = -lfmt

$(PROGRAM): main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM)

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *
