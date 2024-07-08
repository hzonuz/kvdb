# Name of the output executable
TARGET = kvdb

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Ilib

# Source files
SRCS = src/main.cpp src/db.cpp src/utils.cpp src/db_manager.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Installation directory
PREFIX = /usr/local

# Default target to build executable
all: $(TARGET)

# Rule to link object files and create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Install the binary to the specified PREFIX directory
install: $(TARGET)
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 755 $(TARGET) $(DESTDIR)$(PREFIX)/bin

# Declares that these targets are not actual files
.PHONY: all clean install