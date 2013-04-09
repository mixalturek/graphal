TARGET  = bbd
CC      = g++
CFLAGS  = -std=c++98 -pedantic -Wall
# CFLAGS  = -std=c++98 -pedantic -Wall -O2 -s -DNDEBUG
LDFLAGS =
OBJECTS = $(shell ls *.cpp | sed 's/.cpp/.o/')

.PHONY: build
.PHONY: rebuild
.PHONY: all
.PHONY: run
.PHONY: clean
.PHONY: todo
.PHONY: lines
.PHONY: bison
.PHONY: operators
.PHONY: builtin
.PHONY: listbuiltin
.PHONY: version
.PHONY: depend
#.PHONY: install

build: $(TARGET)

rebuild: clean all

all: version bison operators builtin depend build

%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

bison:
	bison -d -o parser.cpp parser.y

operators: gen_operators.pl
	perl gen_operators.pl

builtin: gen_builtin.pl
	perl gen_builtin.pl

version:
	echo '#define SVN_VERSION' $(shell svnversion | tr 'A-Z' ' ' | cut -d ':' -f 1) > version.hpp

depend:
	touch Makefile.dep
	makedepend -f Makefile.dep -Y -m $(shell ls *.cpp) 2>&1 | grep -v '\(cassert\|cstdio\|algorithm\|set\|stream\|fstream\|iostream\|map\|deque\|vector\|stack\|list\|typeinfo\|stdexcept\|cmath\)' ; rm Makefile.dep.bak

Makefile.dep:
	touch Makefile.dep

run:
	./$(TARGET)

memoryleaks:
	valgrind ./$(TARGET) --unit-tests ../samples/tests.txt

clean:
	rm -f $(TARGET) *.o core

todo:
	grep -rI TODO . | grep -v './.svn/'

listbuiltin:
	grep '\$funcdecl =' gen_builtin.pl | sed "s/.*'\(.*\)'.*/\1/"

include Makefile.dep
