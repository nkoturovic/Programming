GOAL = main
CXX = g++
FLAGS = -Wall -Wextra

$(GOAL): main.o razlomak.o
	$(CXX) $^ -o $@

main.o: main.cpp
	$(CXX) $< -c

razlomak.o: razlomak.cpp razlomak.hpp
	$(CXX) $< -c

.PHONY:
	clean

clean: 
	rm *.o main 
