TARGET = main.out
CXX = g++

OPENCV_CFLAGS := $(shell pkg-config opencv4 --cflags)
OPENCV_LIBS := $(shell pkg-config opencv4 --libs)

CXXFLAGS = -std=c++17 -Wall -Wextra $(OPENCV_CFLAGS)
LDLIBS = $(OPENCV_LIBS)

$(TARGET): main.o image.o image_impl.o
	$(CXX) -o $@ $(CXXFLAGS) $(LDLIBS) $^

main.o: main.cpp image.hpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

image.o: image.cpp image.hpp image_impl.hpp 
	$(CXX) -c -o $@ $(CXXFLAGS) $<

image_impl.o: image_impl.cpp image_impl.hpp image.hpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

.PHONY:
	clean

clean:
	rm -rf $(TARGET) *.out *.o compile_commands.json
