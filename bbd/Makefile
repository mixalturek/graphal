TARGET		= bbd
CC			= g++
CFLAGS		= -std=c++98 -pedantic -Wall
LDFLAGS		=
OBJECTS		= $(shell ls *.cpp | sed 's/.cpp/.o/')


.PHONY: all
.PHONY: depend
.PHONY: run
.PHONY: clean
.PHONY: todo
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

todo:
	grep -rI TODO . | grep -v './.svn/'

lines:
	cat *.hpp *.cpp | wc -l



# DO NOT DELETE

baseobject.o: baseobject.hpp general.hpp logger.hpp
context.o: context.hpp general.hpp baseobject.hpp
init_static_objects.o: general.hpp baseobject.hpp valuestruct.hpp value.hpp
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
node.o: node.hpp general.hpp baseobject.hpp context.hpp
nodeunary.o: nodeunary.hpp general.hpp node.hpp baseobject.hpp context.hpp
nodeunaryminus.o: nodeunaryminus.hpp general.hpp nodeunary.hpp node.hpp
nodeunaryminus.o: baseobject.hpp context.hpp value.hpp
tests.o: tests.hpp general.hpp baseobject.hpp logger.hpp valueint.hpp
tests.o: value.hpp valuefloat.hpp valuebool.hpp valuestring.hpp
tests.o: valuestruct.hpp valuenull.hpp valuegraph.hpp valuevertex.hpp
tests.o: valueedgeset.hpp valueedge.hpp valuevertexset.hpp lexan.hpp
tests.o: lexaniterator.hpp lexantokens.hpp nodeunaryminus.hpp nodeunary.hpp
tests.o: node.hpp context.hpp
valuebool.o: value.hpp general.hpp baseobject.hpp valuenull.hpp valuebool.hpp
valuebool.o: valueint.hpp valuefloat.hpp valuestring.hpp valuestruct.hpp
value.o: value.hpp general.hpp baseobject.hpp valuenull.hpp valuebool.hpp
value.o: valueint.hpp valuefloat.hpp valuestring.hpp valuestruct.hpp
value.o: valuereference.hpp valuegraph.hpp valuevertex.hpp valueedgeset.hpp
value.o: valueedge.hpp
valueedge.o: valueedge.hpp general.hpp valuestruct.hpp value.hpp
valueedge.o: baseobject.hpp valuenull.hpp valuegraph.hpp valuebool.hpp
valueedge.o: valuevertex.hpp valueedgeset.hpp
valueedgeset.o: valueedgeset.hpp general.hpp value.hpp baseobject.hpp
valueedgeset.o: logger.hpp valuebool.hpp valueedge.hpp valuestruct.hpp
valueedgeset.o: valuenull.hpp valuegraph.hpp
valuefloat.o: value.hpp general.hpp baseobject.hpp valuenull.hpp
valuefloat.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuefloat.o: valuestruct.hpp
valuegraph.o: valuegraph.hpp general.hpp value.hpp baseobject.hpp logger.hpp
valuegraph.o: valuebool.hpp valuevertex.hpp valueedgeset.hpp valuestruct.hpp
valuegraph.o: valuenull.hpp valueedge.hpp
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
valuevertex.o: valueedgeset.hpp valuegraph.hpp valuestruct.hpp valuenull.hpp
valuevertex.o: valuebool.hpp valueedge.hpp valuevertexset.hpp
valuevertexset.o: valuevertexset.hpp general.hpp value.hpp baseobject.hpp
valuevertexset.o: valuebool.hpp valuevertex.hpp valueedgeset.hpp
valuevertexset.o: valuegraph.hpp valuestruct.hpp valuenull.hpp logger.hpp
