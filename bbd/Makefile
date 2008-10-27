TARGET		= graphs
CC			= g++
CFLAGS		= -std=c++98 -pedantic -Wall
LDFLAGS		=
OBJECTS		= $(shell ls *.cpp | sed 's/.cpp/.o/')


.PHONY: all
.PHONY: depend
.PHONY: run
.PHONY: clean
.PHONY: lines
#.PHONY: install

all:$(TARGET)

%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Mozna bude nadavat kvuliva STL hlavickam, ale je to OK
depend:
	makedepend $(shell ls *.cpp)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o core

# ;-)
lines:
	cat *.hpp *.cpp | wc -l



# DO NOT DELETE

baseobject.o: baseobject.hpp general.hpp
edge.o: edge.hpp general.hpp baseobject.hpp
graph.o: graph.hpp general.hpp vertex.hpp valuestruct.hpp value.hpp
graph.o: baseobject.hpp valuenull.hpp edge.hpp
main.o: general.hpp graph.hpp vertex.hpp valuestruct.hpp value.hpp
main.o: baseobject.hpp valuenull.hpp edge.hpp valueint.hpp valuebool.hpp
main.o: valuestring.hpp
valuebool.o: value.hpp general.hpp baseobject.hpp valuenull.hpp valuebool.hpp
valuebool.o: valueint.hpp valuefloat.hpp valuestring.hpp valuestruct.hpp
value.o: value.hpp general.hpp baseobject.hpp valuebool.hpp
valuefloat.o: value.hpp general.hpp baseobject.hpp valuenull.hpp
valuefloat.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuefloat.o: valuestruct.hpp
valueint.o: value.hpp general.hpp baseobject.hpp valuenull.hpp valuebool.hpp
valueint.o: valueint.hpp valuefloat.hpp valuestring.hpp valuestruct.hpp
valuenull.o: value.hpp general.hpp baseobject.hpp valuenull.hpp valuebool.hpp
valuenull.o: valueint.hpp valuefloat.hpp valuestring.hpp valuestruct.hpp
valuestring.o: value.hpp general.hpp baseobject.hpp valuenull.hpp
valuestring.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuestring.o: valuestruct.hpp
valuestruct.o: value.hpp general.hpp baseobject.hpp valuenull.hpp
valuestruct.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuestruct.o: valuestruct.hpp
vertex.o: vertex.hpp general.hpp valuestruct.hpp value.hpp baseobject.hpp
vertex.o: valuenull.hpp
