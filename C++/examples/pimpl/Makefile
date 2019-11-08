TARGET = main.out
CXX = g++

OPENCV_CFLAGS := $(shell pkg-config opencv4 --cflags)
OPENCV_LIBS := $(shell pkg-config opencv4 --libs)

CXXFLAGS = -std=c++17 -Wall -Wextra $(OPENCV_CFLAGS) -Iinclude
LDLIBS = $(OPENCV_LIBS)

$(TARGET): main.o image.o image_impl.o transformations.o transformations_impl.o
	$(CXX) -o $@ $(CXXFLAGS) $(LDLIBS) $^

main.o: main.cpp include/image.hpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

image.o: src/image.cpp include/image.hpp include/implementation/image_impl.hpp 
	$(CXX) -c -o $@ $(CXXFLAGS) $<

image_impl.o: src/implementation/image_impl.cpp include/implementation/image_impl.hpp include/image.hpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

transformations.o: src/transformations.cpp include/transformations.hpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

transformations_impl.o: src/implementation/transformations_impl.cpp include/implementation/transformations_impl.hpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<


.PHONY:
	clean

clean:
	rm -rf $(TARGET) *.out *.o compile_commands.json
