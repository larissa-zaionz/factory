CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
SRCS = $(wildcard src/*.cpp)

all: factory

factory: $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o factory
