CC = g++
CFLAGS = -Wall -O3 -g# Changed from O4 to O3 for standard optimization level

main: sorttest.o sorts.o
	$(CC) $(CFLAGS) -o main sorttest.o sorts.o

sorttest.o: sorttest.cpp
	$(CC) $(CFLAGS) -c sorttest.cpp

sorts.o: ../headers/Misc-Algorithms/Sorting/sorts.cpp
	$(CC) $(CFLAGS) -c ../headers/Misc-Algorithms/Sorting/sorts.cpp

.PHONY: clean
clean:
	rm -f *.o main
