CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer
SRCS = $(wildcard src/*.cpp)
HDRS = $(wildcard src/*.h)

all: factory

factory: $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o factory

asan: $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $(SRCS) -o factory_asan
	./factory_asan

run: all
	./factory

clean:
	rm -f factory factory.exe factory_asan factory_asan.exe

.PHONY: all asan run clean
