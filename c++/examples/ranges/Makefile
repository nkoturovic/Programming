TARGET = main.out
CXX = g++
CXXFLAGS = -std=c++2a -Wall -Wextra -Wpedantic -fconcepts

$(TARGET): main.o
	$(CXX) -o $@ $(CXXFLAGS) $^

main.o: main.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

.PHONY:
	clean

clean:
	rm -rf $(TARGET) *.out *.o compile_commands.json
