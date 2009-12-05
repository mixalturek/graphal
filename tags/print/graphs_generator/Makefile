TARGET  = generator
CC      = g++
CFLAGS  = -std=c++98 -pedantic -Wall
# CFLAGS  = -std=c++98 -pedantic -Wall -O2 -s -DNDEBUG
LDFLAGS =
OBJECTS = $(shell ls *.c | sed 's/.c/.o/')

.PHONY: build
.PHONY: depend
.PHONY: clean
.PHONY: todo

build: $(TARGET)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

depend:
	makedepend -Y -m $(shell ls *.cpp) 2>&1 | grep -v '\(cassert\|algorithm\|set\|stream\|fstream\|iostream\|map\|deque\|vector\|stack\|list\|typeinfo\|stdexcept\|cmath\)'

clean:
	rm -f $(TARGET) *.o core Makefile.bak

todo:
	grep -rI TODO . | grep -v './.svn/'
