# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Iinclude

# Tools
CPPCHECK := cppcheck
CPPCHECK_FLAGS := \
	--enable=all \
	--inconclusive \
	--std=c++17 \
	--error-exitcode=1 \
	--suppress=missingIncludeSystem \
	--suppress=normalCheckLevelMaxBranches \
	--suppress=useStlAlgorithm \
	--suppress=unusedFunction \
	-I include

# Directories
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build

# Sources and objects
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Output executable
TARGET := $(BUILD_DIR)/main.exe

# Default target
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile each .cpp into .o inside build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/*.h
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the compiled program
run: all
	./$(TARGET)

# Run static analysis
check:
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SRC_DIR) $(INC_DIR)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: all clean run check
