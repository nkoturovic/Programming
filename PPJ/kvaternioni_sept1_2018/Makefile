GOAL = kvaternioni
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra

$(GOAL): lex.yy.o parser.tab.o kvaternion.o
	$(CXX) -o $@ $^

kvaternion.o: kvaternion.cpp kvaternion.hpp
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
