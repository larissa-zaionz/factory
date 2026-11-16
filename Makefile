# Makefile multiplataforma: Linux/WSL/macOS e Windows (MinGW + mingw32-make)
# Uso: make | make run | make asan | make clean

CXX       = g++
CXXFLAGS  = -Wall -Wextra -std=c++17 -g
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer
SRCS      = $(wildcard src/*.cpp)
HDRS      = $(wildcard src/*.h)

# Detecta o sistema. Para forcar (ex.: Git Bash/MSYS2): make PLATAFORMA=linux
ifeq ($(OS),Windows_NT)
    PLATAFORMA ?= windows
else
    PLATAFORMA ?= linux
endif

ifeq ($(PLATAFORMA),windows)
    EXE     = factory.exe
    ASANEXE = factory_asan.exe
    RUN     = $(EXE)
    LIMPAR  = -del /Q /F $(EXE) $(ASANEXE) 2>NUL
else
    EXE     = factory
    ASANEXE = factory_asan
    RUN     = ./$(EXE)
    LIMPAR  = rm -f $(EXE) $(ASANEXE)
endif

all: $(EXE)

$(EXE): $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXE)

run: all
	$(RUN)

ifeq ($(PLATAFORMA),windows)
asan:
	@echo O AddressSanitizer nao funciona no MinGW. Use o WSL: wsl make asan
else
asan: $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $(SRCS) -o $(ASANEXE)
	./$(ASANEXE)
endif

clean:
	$(LIMPAR)

.PHONY: all run asan clean