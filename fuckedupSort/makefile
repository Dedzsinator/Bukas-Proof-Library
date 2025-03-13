# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -O5 -march=native
CXXFLAGSDEBUG = -std=c++17 -Wall -O5 -march=native -pg -no-pie -g

# Source files
SOURCES = linuxfork.cpp best.cpp metaprog.cpp multithread.cpp no_asm.cpp radix.cpp turboheap.cpp ska_sort.cpp campsort.cpp

# Object files (not strictly necessary here but good practice)
OBJECTS = $(SOURCES:.cpp=.o)

# Executable names
EXECUTABLES = $(SOURCES:.cpp=.out)

# Default target
all: release

# Rule to compile each source file into an executable
%.out: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Rule to compile each source file into a debug executable
debug_%.out: %.cpp
	$(CXX) $(CXXFLAGSDEBUG) -o $@ $<

# Rule to run each executable and print its name
release: $(EXECUTABLES)
	@for exe in $(EXECUTABLES); do \
		echo "Running $$exe:"; \
		./$$exe; \
		echo ""; \
	done

# Rule to compile and run each debug executable and print its name
debug: $(SOURCES:%.cpp=debug_%.out)
	@for exe in $(SOURCES:%.cpp=debug_%.out); do \
		echo "Running $$exe:"; \
		./$$exe; \
		echo ""; \
	done

# Clean up generated files
clean:
	rm -f $(EXECUTABLES) $(SOURCES:%.cpp=debug_%.out) gmon.out core *.exe