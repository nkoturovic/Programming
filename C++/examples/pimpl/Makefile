TARGET = main.out
CXX = g++

OPENCV_CFLAGS := $(shell pkg-config opencv4 --cflags)
OPENCV_LIBS := $(shell pkg-config opencv4 --libs)

CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic $(OPENCV_CFLAGS)
LDLIBS = $(OPENCV_LIBS)

$(TARGET): main.o image.o image_impl.o transform.o display.o
	$(CXX) -o $@ $(CXXFLAGS) $(LDLIBS) $^

main.o: main.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

image.o: image.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

image_impl.o: image_impl.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

transform.o: transform.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

display.o: display.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

.PHONY:
	clean

clean:
	rm -rf $(TARGET) *.out *.o compile_commands.json
