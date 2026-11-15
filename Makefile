CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer
SRCS = $(wildcard src/*.cpp)

all: factory

factory: $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o factory

asan: $(SRCS)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $(SRCS) -o factory_asan
	./factory_asan

run: all
	./factory

clean:
	rm -f factory factory.exe factory_asan factory_asan.exe