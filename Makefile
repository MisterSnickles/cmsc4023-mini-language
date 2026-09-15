# Compiler and Flags
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
# Target Executable
TARGET   = mini-language

# Source Files and Object Files
SRCS     = main.cpp SymbolTable.cpp Validator.cpp Interpreter.cpp
OBJS     = $(SRCS:.cpp=.o)

# Default Rule
all: $(TARGET)

# Link Object Files into Executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp Files to .o Files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Up Built Files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean