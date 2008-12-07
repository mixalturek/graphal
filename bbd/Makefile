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

baseobject.o: baseobject.hpp general.hpp logger.hpp
init_static_objects.o: baseobject.hpp general.hpp valuestruct.hpp value.hpp
init_static_objects.o: valuenull.hpp logger.hpp
lexan.o: lexan.hpp general.hpp baseobject.hpp lexaniterator.hpp
lexan.o: lexantokens.hpp lexaniteratorstring.hpp lexaniteratorfile.hpp
lexan.o: logger.hpp
lexaniterator.o: lexaniterator.hpp general.hpp baseobject.hpp
lexaniteratorfile.o: lexaniteratorfile.hpp general.hpp lexaniterator.hpp
lexaniteratorfile.o: baseobject.hpp
lexaniteratorstring.o: lexaniteratorstring.hpp general.hpp lexaniterator.hpp
lexaniteratorstring.o: baseobject.hpp
logger.o: logger.hpp general.hpp baseobject.hpp
main.o: general.hpp baseobject.hpp logger.hpp tests.hpp
tests.o: tests.hpp general.hpp baseobject.hpp logger.hpp valueint.hpp
tests.o: value.hpp valuefloat.hpp valuebool.hpp valuestring.hpp
tests.o: valuestruct.hpp valuenull.hpp valuegraph.hpp valuevertex.hpp
tests.o: valueedge.hpp lexan.hpp lexaniterator.hpp lexantokens.hpp
valuebool.o: value.hpp general.hpp baseobject.hpp valuenull.hpp valuebool.hpp
valuebool.o: valueint.hpp valuefloat.hpp valuestring.hpp valuestruct.hpp
value.o: value.hpp general.hpp baseobject.hpp valuenull.hpp valuebool.hpp
value.o: valueint.hpp valuefloat.hpp valuestring.hpp valuestruct.hpp
value.o: valuereference.hpp valuegraph.hpp valuevertex.hpp valueedge.hpp
valueedge.o: valueedge.hpp general.hpp valuestruct.hpp value.hpp
valueedge.o: baseobject.hpp valuenull.hpp valuebool.hpp valuevertex.hpp
valuefloat.o: value.hpp general.hpp baseobject.hpp valuenull.hpp
valuefloat.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuefloat.o: valuestruct.hpp
valuegraph.o: valuegraph.hpp general.hpp value.hpp baseobject.hpp
valuegraph.o: valuebool.hpp valuevertex.hpp valueedge.hpp valuestruct.hpp
valuegraph.o: valuenull.hpp
valueint.o: value.hpp general.hpp baseobject.hpp valuenull.hpp valuebool.hpp
valueint.o: valueint.hpp valuefloat.hpp valuestring.hpp valuestruct.hpp
valuenull.o: value.hpp general.hpp baseobject.hpp valuenull.hpp valuebool.hpp
valuenull.o: valueint.hpp valuefloat.hpp valuestring.hpp valuestruct.hpp
valuereference.o: valuereference.hpp general.hpp value.hpp baseobject.hpp
valuereference.o: valuebool.hpp
valuestring.o: value.hpp general.hpp baseobject.hpp valuenull.hpp
valuestring.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuestring.o: valuestruct.hpp
valuestruct.o: value.hpp general.hpp baseobject.hpp valuenull.hpp
valuestruct.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuestruct.o: valuestruct.hpp
valuevertex.o: valuevertex.hpp general.hpp value.hpp baseobject.hpp
valuevertex.o: valuebool.hpp
