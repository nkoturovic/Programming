TARGET=main.out
CXX=g++
FLAGS=-std=c++17 -Wall -Wextra

$(TARGET): main.o
	$(CXX) $(FLAGS) $^ -o $@

main.o: main.cpp
	$(CXX) $(FLAGS) -c $< 

.PHONY:
	clean

clean:
	rm -rf $(TARGET) *.o *.out
