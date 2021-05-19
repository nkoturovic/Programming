PROGRAM   = main.out
CXX       = clang++
CXXFLAGS  = -g -std=c++20 -Wall -Wextra -Wpedantic -fmodules # -fimplicit-module-maps

$(PROGRAM): main.cpp utils.o
	$(CXX) $(CXXFLAGS) -fprebuilt-module-path=. -o $@ $^

## -fimplicit-modules -fimplicit-module-maps 

## main.o: main.cpp utils.o
##	 $(CXX) $(CXXFLAGS) -fprebuilt-module-path=. -c -o $@ $^

utils.o: utils.pcm
	$(CXX) $(CXXFLAGS) -c $^ -o $@

utils.pcm: utils.cppm
	$(CXX) $(CXXFLAGS) --precompile utils.cppm -o utils.pcm

.PHONY: clean dist

clean:
	-rm *.o *.pcm $(PROGRAM)

dist: clean
	-tar -czvf $(PROGRAM).tar.bz2 *
