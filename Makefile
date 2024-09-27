# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# List all .cpp files in the current directory
SOURCES := $(wildcard *.cpp)

# Generate executable names by stripping the .cpp extension
EXECUTABLES := $(SOURCES:.cpp=)

# Default target: build all executables
all: $(EXECUTABLES)

# Rule to compile each .cpp file into an executable with the same name
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean up generated executables
clean:
	rm -f $(EXECUTABLES)

.PHONY: all clean
