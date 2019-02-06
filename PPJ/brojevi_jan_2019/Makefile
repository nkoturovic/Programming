GOAL = brojevi
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra

$(GOAL): lex.yy.o parser.tab.o List.o
	$(CXX) -o $@ $^

List.o: List.cpp List.hpp
	$(CXX) $(CXXFLAGS) -c $<

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

lex.yy.o: lex.yy.c parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

lex.yy.c: lexer.lex
	flex $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -v -d $<

.PHONY: clean

clean:
	rm *.o parser.tab.* parser.output lex.yy.* $(GOAL)

