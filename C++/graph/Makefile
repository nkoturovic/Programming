PROGRAM = graph_demo.out 
CXX = g++
FLAGS = -std=c++17 -Wall -Wextra

$(PROGRAM): main.o graph.hpp
	$(CXX) $(FLAGS) $< -o $@

main.o: main.cpp
	$(CXX) $(FLAGS) -c $< 

.PHONY:
	clean

clean:
	rm -rf $(PROGRAM) *.o
