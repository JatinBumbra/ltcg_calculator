# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11
DEBUG_FLAGS = -g
OPT_FLAGS = -O2

# Source and output files
SRC = ltcg_calculator.cpp
DEBUG_BIN = ltcg_debug
OPT_BIN = ltcg_optimized

# Default target
all: debug optimized

# Debug build
debug: $(SRC)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(SRC) -o $(DEBUG_BIN)

# Optimized build
optimized: $(SRC)
	$(CXX) $(CXXFLAGS) $(OPT_FLAGS) $(SRC) -o $(OPT_BIN)

# Clean up build artifacts
clean:
	rm -f $(DEBUG_BIN) $(OPT_BIN)
