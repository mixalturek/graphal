CC      = g++
CFLAGS  = -std=c++98 -pedantic -Wall -O2 -s -DNDEBUG
LDFLAGS =

all: var array func

loop: var.cpp
	$(CC) -o var var.cpp $(CFLAGS)

array: array.cpp
	$(CC) -o array array.cpp $(CFLAGS)

func: func.cpp
	$(CC) -o func func.cpp $(CFLAGS)

clean:
	rm -f var array func core
