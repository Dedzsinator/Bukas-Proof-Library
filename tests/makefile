# Compiler
CC = g++
CFLAGS = -Wall -O3 -g -std=c++11

# Source files
SORT_SRCS = sorttest.cpp ../headers/Misc-Algorithms/Sorting/sorts.cpp
MAPS_SRCS = tests/mapstest.cpp

# Object files
SORT_OBJS = $(SORT_SRCS:.cpp=.o)
MAPS_OBJS = $(MAPS_SRCS:.cpp=.o)

# Target executables
SORT_TARGET = sorttest
MAPS_TARGET = mapstest

# Default target
all: menu

# Menu to select which files to compile
menu:
	@echo "Choose the target to compile:"
	@echo "1. Sort Test"
	@echo "2. Maps Test"
	@echo "3. Clean"
	@read -p "Enter your choice: " choice; \
	if [ $$choice -eq 1 ]; then \
		$(MAKE) $(SORT_TARGET); \
	elif [ $$choice -eq 2 ]; then \
		$(MAKE) $(MAPS_TARGET); \
	elif [ $$choice -eq 3 ]; then \
		$(MAKE) clean; \
	else \
		echo "Invalid choice"; \
	fi

# Compile sort test
$(SORT_TARGET): $(SORT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile maps test
$(MAPS_TARGET): $(MAPS_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(SORT_TARGET) $(MAPS_TARGET) $(SORT_OBJS) $(MAPS_OBJS)

.PHONY: all menu clean
