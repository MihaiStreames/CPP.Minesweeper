# Compiler and flags
CXX = g++
CXXFLAGS += -std=c++17

# Enable warnings and optimizations
CXXFLAGS += -pedantic -Wall -Wextra -O2

# Enable sanitizers
# CXXFLAGS += -fsanitize=address,undefined
# LDFLAGS += -fsanitize=address,undefined

# Additional compiler warnings
CXXFLAGS += -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op \
            -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align \
            -Wnull-dereference -Wold-style-cast -Wuseless-cast \
            -Wdouble-promotion -Wzero-as-null-pointer-constant -Wstrict-null-sentinel \
            -Wswitch-enum -Wswitch-default -Wunreachable-code -Wundef

# Include directories
INCLUDES = -Iinclude

# Libraries and linker flags
LDLIBS += $(shell pkg-config allegro-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5 --libs) -lallegro_main
CXXFLAGS += $(shell pkg-config allegro-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5 --cflags)

# Source and object files
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Target executable
TARGET = minesweeper

# Default rule
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# Compile source files into object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJ)