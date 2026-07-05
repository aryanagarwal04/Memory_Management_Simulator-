# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -I include

# Source files
SRC = src/main.cpp \
      src/cli.cpp \
      src/allocator.cpp \
      src/memory_block.cpp \
      src/cache.cpp

# Output executable
TARGET = memsim

# Default target
all: $(TARGET)

# Build executable
$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean build artifacts
clean:
	del $(TARGET).exe 2>nul || exit 0
