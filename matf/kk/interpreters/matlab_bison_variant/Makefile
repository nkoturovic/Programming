GOAL = matlab
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused

$(GOAL): lex.yy.o parser.tab.o driver.o matrica.o
	$(CXX) -o $@ $^

matrica.o: matrica.cpp matrica.hpp
	$(CXX) $(CXXFLAGS) $< -c

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
	rm *.o parser.tab.* parser.output lex.yy.* stack.hh position.hh location.hh $(GOAL)
