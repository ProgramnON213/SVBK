# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Find all .cpp files in all subdirectories (weeks)
SOURCES := $(shell find . -name "*.cpp")
# Turn each source file into an executable name without extension
EXECUTABLES := $(SOURCES:.cpp=)

# Default target: build everything
all: $(EXECUTABLES)

# Rule: compile .cpp -> executable
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean all executables
clean:
	rm -f $(EXECUTABLES)
