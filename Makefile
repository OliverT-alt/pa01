# Makefile for Heap lab

# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Executable name
TARGET   := heap_test

# Source files (add or remove .cpp files as needed)
SRCS     := heap.cpp main.cpp
OBJS     := $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
<TAB>$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile each .cpp into .o
%.o: %.cpp heap.h
<TAB>$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove build artifacts
clean:
<TAB>rm -f $(OBJS) $(TARGET)

.PHONY: all clean
