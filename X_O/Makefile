# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iheaders

# ncurses library
LDFLAGS = -lncurses

# Directories
SRC_DIR = src
OBJ_DIR = obj
HEADERS_DIR = headers

# Output executable
TARGET = xo_game

# Source and object files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Default rule
all: $(TARGET)

# Linking the final executable with ncurses
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

# Compiling source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean generated files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Phony targets
.PHONY: all clean