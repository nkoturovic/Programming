TARGET=main.out
CXX=g++
FLAGS=-std=c++17 -Wall -Wextra

$(TARGET): main.o
	$(CXX) -o $@ $(FLAGS) $^

main.o: main.cpp tests_passed shared_ptr.hpp unique_ptr.hpp
	$(CXX) -o $@ $(FLAGS) -c $< 

tests_passed: tests.out shared_ptr.hpp unique_ptr.hpp
	./$<

tests.out: tests.o shared_ptr.hpp unique_ptr.hpp
	$(CXX) -o $@ $(FLAGS) $<
	
tests.o: tests.cpp shared_ptr.hpp unique_ptr.hpp
	$(CXX) -c -o $@ $(FLAGS) $<
	
.PHONY:
	clean

clean:
	rm -rf $(TARGET) *.o *.out
