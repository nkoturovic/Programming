CXX = g++
FLAGS = -std=c++17 -Wall -Wextra

demos: graph_demo.out dfs_demo.out

graph_demo.out: main.o
	$(CXX) $(FLAGS) $< -o $@

dfs_demo.out: dfs_demo.o
	$(CXX) $(FLAGS) $< -o $@

dfs_demo.o: dfs_demo.cpp
	$(CXX) $(FLAGS) -c $< 

main.o: main.cpp
	$(CXX) $(FLAGS) -c $< 


.PHONY:
	clean

clean:
	rm -rf *.o *.out
