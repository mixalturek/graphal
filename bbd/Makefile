TARGET		= bbd
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
edge.o: edge.hpp general.hpp valuestruct.hpp value.hpp baseobject.hpp
edge.o: valuenull.hpp valueadapter.hpp vertex.hpp
graph.o: graph.hpp general.hpp baseobject.hpp vertex.hpp valuestruct.hpp
graph.o: value.hpp valuenull.hpp valueadapter.hpp edge.hpp
lexan.o: lexan.hpp general.hpp baseobject.hpp lexaniterator.hpp
lexan.o: lexantokens.hpp lexaniteratorstring.hpp lexaniteratorfile.hpp
lexan.o: logger.hpp
lexaniterator.o: lexaniterator.hpp general.hpp baseobject.hpp
lexaniteratorfile.o: lexaniteratorfile.hpp general.hpp lexaniterator.hpp
lexaniteratorfile.o: baseobject.hpp
lexaniteratorstring.o: lexaniteratorstring.hpp general.hpp lexaniterator.hpp
lexaniteratorstring.o: baseobject.hpp
logger.o: logger.hpp general.hpp
main.o: general.hpp logger.hpp graph.hpp baseobject.hpp valueint.hpp
main.o: value.hpp valuebool.hpp valuefloat.hpp valuestruct.hpp valuenull.hpp
main.o: valueadapter.hpp valuestring.hpp vertex.hpp edge.hpp
valueadapter.o: valueadapter.hpp value.hpp general.hpp baseobject.hpp
valueadapter.o: valuenull.hpp valuebool.hpp valueint.hpp valuefloat.hpp
valueadapter.o: valuestring.hpp valuestruct.hpp
valuebool.o: value.hpp general.hpp baseobject.hpp valuenull.hpp
valuebool.o: valueadapter.hpp valuebool.hpp valueint.hpp valuefloat.hpp
valuebool.o: valuestring.hpp valuestruct.hpp
value.o: value.hpp general.hpp baseobject.hpp valuebool.hpp
valuefloat.o: value.hpp general.hpp baseobject.hpp valuenull.hpp
valuefloat.o: valueadapter.hpp valuebool.hpp valueint.hpp valuefloat.hpp
valuefloat.o: valuestring.hpp valuestruct.hpp
valueint.o: value.hpp general.hpp baseobject.hpp valuenull.hpp
valueint.o: valueadapter.hpp valuebool.hpp valueint.hpp valuefloat.hpp
valueint.o: valuestring.hpp valuestruct.hpp
valuenull.o: value.hpp general.hpp baseobject.hpp valuenull.hpp
valuenull.o: valueadapter.hpp valuebool.hpp valueint.hpp valuefloat.hpp
valuenull.o: valuestring.hpp valuestruct.hpp
valuestring.o: value.hpp general.hpp baseobject.hpp valuenull.hpp
valuestring.o: valueadapter.hpp valuebool.hpp valueint.hpp valuefloat.hpp
valuestring.o: valuestring.hpp valuestruct.hpp
valuestruct.o: value.hpp general.hpp baseobject.hpp valuenull.hpp
valuestruct.o: valueadapter.hpp valuebool.hpp valueint.hpp valuefloat.hpp
valuestruct.o: valuestring.hpp valuestruct.hpp
vertex.o: vertex.hpp general.hpp valuestruct.hpp value.hpp baseobject.hpp
vertex.o: valuenull.hpp valueadapter.hpp
