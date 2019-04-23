GOAL = mylang.out
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused

$(GOAL): lex.yy.o parser.tab.o driver.o
	$(CXX) -o $@ $^

parser.tab.o: parser.tab.cpp parser.tab.hpp driver.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

lex.yy.o: lex.yy.c parser.tab.hpp position.hh location.hh driver.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

driver.o: driver.cpp driver.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

lex.yy.c: lexer.lex
	flex $<


parser.tab.cpp parser.tab.hpp position.hh location.hh: parser.ypp
	bison -v -d $<

.PHONY: clean

clean:
	rm $(GOAL) *.o *.out parser.tab.* parser.output lex.yy.* stack.hh position.hh location.hh
