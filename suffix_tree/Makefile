# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -w  # Include the directory where exercise.h is located
TARGET = main
SRC_FILES = main.c tests/array_test.c internal/array.c tests/suffix_array_test.c internal/suffix_array.c tests/lcp_array_test.c internal/lcp_array.c # data_structure.c suffix_tree.c lcp_array.c  Add exercise.c as a source file

# Build target
all: $(TARGET)

# Compile the source files (main.c, exercise.c, munit.c) into the TARGET executable
$(TARGET): $(SRC_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC_FILES)

# Clean target (removes the executable)
clean:
	rm -f $(TARGET)

# Run the tests
run-tests: $(TARGET)
	./$(TARGET)

# PHONY ensures that these targets will run even if a file with the same name exists
.PHONY: all clean run-tests
