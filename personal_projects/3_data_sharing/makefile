# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -pthread
LDFLAGS = -pthread

# Executable name (defaults to the name of the first .cpp file found)
TARGET = $(basename $(wildcard *.cpp))

# Default target (build the executable)
all: build

# Build the executable
build: $(TARGET)

$(TARGET): $(wildcard *.cpp)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Run the executable
run: build
	./$(TARGET)

# Clean up build artifacts
clean:
	rm -f $(TARGET)

.PHONY: all build run clean