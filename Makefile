CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# The executable must be named 'examheap' per lab instructions
target := examheap

# Sources: heap implementation + test harness provided by instructor
SRCS    := heap.cpp examheap.cpp
OBJS    := $(SRCS:.cpp=.o)

# Default: build the executable
all: $(target)

# Link step
e $(target): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile each .cpp into .o
%.o: %.cpp heap.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(target)

.PHONY: all clean