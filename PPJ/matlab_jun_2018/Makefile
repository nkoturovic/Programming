CXXFLAGS = -Wall -Wextra -g

matlab: matrica.o lex.yy.o parser.tab.o
	g++ $(CXXFLAGS) $^ -o $@

matrica.o: matrica.cpp matrica.hpp
	g++ $(CXXFLAGS) $< -c


lex.yy.o: lex.yy.c parser.tab.hpp
	g++ $(CXXFLAGS) $< -c


parser.tab.o: parser.tab.cpp
	g++ $(CXXFLAGS) $^ -c

lex.yy.c: lexer.l parser.tab.hpp
	flex $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -v -d $<

.PHONY: 
	clean

clean:
	rm -rf *.o parser.tab.* lex.yy.* parser.output matlab
