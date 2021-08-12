LIB   = libfunctions.so
CXX       = g++
CXXFLAGS  = -O3 -g -std=c++20 -Wall -Wextra -Wpedantic
LDFLAGS   = -lfunctions

$(LIB): functions.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -shared

functions.o: functions.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


main.out: main.cpp
	$(CXX) -L/home/kotur/Desktop/iw/examples/09_dynlib  -Wl,-rpath=/home/kotur/Desktop/iw/examples/09_dynlib $(CXXFLAGS) -o $@ $^ $(LDFLAGS) 



.PHONY: clean dist

clean:
	-rm *.o *.out *.so $(PROGRAM)

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *
