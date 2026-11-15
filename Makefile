SRCS = $(wildcard src/*.cpp)
HDRS = $(wildcard src/*.h)          # novo

all: factory

factory: $(SRCS) $(HDRS)            # acrescentado $(HDRS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o factory

asan: $(SRCS) $(HDRS)               # acrescentado $(HDRS)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $(SRCS) -o factory_asan
	./factory_asan

run: all
	./factory

clean:
	rm -f factory factory.exe factory_asan factory_asan.exe

.PHONY: all asan run clean          # novo