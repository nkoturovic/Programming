GOAL = main
CXX = g++
FLAGS = -Wall -Wextra

$(GOAL): main.o
	$(CXX) $^ -o $@

main.o: main.cpp
	$(CXX) $< -c

.PHONY:
	clean

clean: 
	rm *.o main 
