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

$(TARGET): parser.o $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

parser.o: parser.cpp
	g++ -c parser.cpp

parser.cpp parser.hpp: parser.y
	bison -d -o parser.cpp parser.y

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
context.o: context.hpp general.hpp baseobject.hpp countptr.hpp value.hpp
context.o: stringtable.hpp valuenull.hpp nodefunction.hpp node.hpp
init_static_objects.o: general.hpp baseobject.hpp valuestruct.hpp value.hpp
init_static_objects.o: countptr.hpp valuenull.hpp logger.hpp
lexan.o: lexan.hpp general.hpp baseobject.hpp lexaniterator.hpp
lexan.o: lexantokens.hpp node.hpp context.hpp countptr.hpp value.hpp
lexan.o: stringtable.hpp parser.hpp lexaniteratorstring.hpp
lexan.o: lexaniteratorfile.hpp logger.hpp
lexaniterator.o: lexaniterator.hpp general.hpp baseobject.hpp
lexaniteratorfile.o: lexaniteratorfile.hpp general.hpp lexaniterator.hpp
lexaniteratorfile.o: baseobject.hpp
lexaniteratorstring.o: lexaniteratorstring.hpp general.hpp lexaniterator.hpp
lexaniteratorstring.o: baseobject.hpp
logger.o: logger.hpp general.hpp baseobject.hpp
main.o: general.hpp baseobject.hpp logger.hpp tests.hpp context.hpp
main.o: countptr.hpp value.hpp stringtable.hpp
nodebinaryadd.o: nodebinaryadd.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryadd.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodebinaryadd.o: stringtable.hpp
nodebinaryand.o: nodebinaryand.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryand.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodebinaryand.o: stringtable.hpp
nodebinaryassadd.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodebinaryassadd.o: context.hpp countptr.hpp value.hpp stringtable.hpp
nodebinaryassadd.o: nodebinaryassadd.hpp nodebinary.hpp
nodebinaryass.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodebinaryass.o: context.hpp countptr.hpp value.hpp stringtable.hpp
nodebinaryass.o: nodebinaryass.hpp nodebinary.hpp
nodebinaryassdiv.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodebinaryassdiv.o: context.hpp countptr.hpp value.hpp stringtable.hpp
nodebinaryassdiv.o: nodebinaryassdiv.hpp nodebinary.hpp
nodebinaryassmod.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodebinaryassmod.o: context.hpp countptr.hpp value.hpp stringtable.hpp
nodebinaryassmod.o: nodebinaryassmod.hpp nodebinary.hpp
nodebinaryassmult.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodebinaryassmult.o: context.hpp countptr.hpp value.hpp stringtable.hpp
nodebinaryassmult.o: nodebinaryassmult.hpp nodebinary.hpp
nodebinaryasssub.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodebinaryasssub.o: context.hpp countptr.hpp value.hpp stringtable.hpp
nodebinaryasssub.o: nodebinaryasssub.hpp nodebinary.hpp
nodebinary.o: nodebinary.hpp general.hpp node.hpp baseobject.hpp context.hpp
nodebinary.o: countptr.hpp value.hpp stringtable.hpp
nodebinarydiv.o: nodebinarydiv.hpp general.hpp nodebinary.hpp node.hpp
nodebinarydiv.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodebinarydiv.o: stringtable.hpp
nodebinaryeq.o: nodebinaryeq.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryeq.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodebinaryeq.o: stringtable.hpp
nodebinaryge.o: nodebinaryge.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryge.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodebinaryge.o: stringtable.hpp
nodebinarygt.o: nodebinarygt.hpp general.hpp nodebinary.hpp node.hpp
nodebinarygt.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodebinarygt.o: stringtable.hpp
nodebinaryle.o: nodebinaryle.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryle.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodebinaryle.o: stringtable.hpp
nodebinarylt.o: nodebinarylt.hpp general.hpp nodebinary.hpp node.hpp
nodebinarylt.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodebinarylt.o: stringtable.hpp
nodebinarymod.o: nodebinarymod.hpp general.hpp nodebinary.hpp node.hpp
nodebinarymod.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodebinarymod.o: stringtable.hpp
nodebinarymult.o: nodebinarymult.hpp general.hpp nodebinary.hpp node.hpp
nodebinarymult.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodebinarymult.o: stringtable.hpp
nodebinaryne.o: nodebinaryne.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryne.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodebinaryne.o: stringtable.hpp
nodebinaryor.o: nodebinaryor.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryor.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodebinaryor.o: stringtable.hpp
nodebinarysub.o: nodebinarysub.hpp general.hpp nodebinary.hpp node.hpp
nodebinarysub.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodebinarysub.o: stringtable.hpp
nodeblock.o: nodeblock.hpp general.hpp node.hpp baseobject.hpp context.hpp
nodeblock.o: countptr.hpp value.hpp stringtable.hpp nodefunctioncall.hpp
nodeblock.o: valuenull.hpp
nodecondition.o: nodecondition.hpp general.hpp node.hpp baseobject.hpp
nodecondition.o: context.hpp countptr.hpp value.hpp stringtable.hpp
nodecondition.o: valuenull.hpp nodeemptycommand.hpp
node.o: node.hpp general.hpp baseobject.hpp context.hpp countptr.hpp
node.o: value.hpp stringtable.hpp
nodeemptycommand.o: nodeemptycommand.hpp general.hpp node.hpp baseobject.hpp
nodeemptycommand.o: context.hpp countptr.hpp value.hpp stringtable.hpp
nodeemptycommand.o: valuenull.hpp
nodefunctioncall.o: nodefunctioncall.hpp general.hpp node.hpp baseobject.hpp
nodefunctioncall.o: context.hpp countptr.hpp value.hpp stringtable.hpp
nodefunctioncall.o: nodefunction.hpp nodeblock.hpp valuenull.hpp
nodefunction.o: nodefunction.hpp general.hpp node.hpp baseobject.hpp
nodefunction.o: context.hpp countptr.hpp value.hpp stringtable.hpp
nodefunction.o: nodeemptycommand.hpp valuenull.hpp
nodeloop.o: nodeloop.hpp general.hpp node.hpp baseobject.hpp context.hpp
nodeloop.o: countptr.hpp value.hpp stringtable.hpp valuenull.hpp
nodeloop.o: valuebool.hpp nodeemptycommand.hpp nodevalue.hpp
nodeunary.o: nodeunary.hpp general.hpp node.hpp baseobject.hpp context.hpp
nodeunary.o: countptr.hpp value.hpp stringtable.hpp
nodeunarynot.o: nodeunarynot.hpp general.hpp nodeunary.hpp node.hpp
nodeunarynot.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodeunarynot.o: stringtable.hpp
nodeunaryreturn.o: nodeunaryreturn.hpp general.hpp nodeunary.hpp node.hpp
nodeunaryreturn.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodeunaryreturn.o: stringtable.hpp
nodeunarysub.o: nodeunarysub.hpp general.hpp nodeunary.hpp node.hpp
nodeunarysub.o: baseobject.hpp context.hpp countptr.hpp value.hpp
nodeunarysub.o: stringtable.hpp
nodevalue.o: nodevalue.hpp general.hpp node.hpp baseobject.hpp context.hpp
nodevalue.o: countptr.hpp value.hpp stringtable.hpp
nodevariable.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodevariable.o: context.hpp countptr.hpp value.hpp stringtable.hpp
nodevariable.o: valuefloat.hpp
parser.o: general.hpp lexan.hpp baseobject.hpp lexaniterator.hpp
parser.o: lexantokens.hpp node.hpp context.hpp countptr.hpp value.hpp
parser.o: stringtable.hpp parser.hpp nodebinaryadd.hpp nodebinary.hpp
parser.o: nodebinaryand.hpp nodebinaryass.hpp nodebinaryassadd.hpp
parser.o: nodebinaryasssub.hpp nodebinaryassmult.hpp nodebinaryassdiv.hpp
parser.o: nodebinaryassmod.hpp nodebinarydiv.hpp nodebinaryeq.hpp
parser.o: nodebinaryge.hpp nodebinarygt.hpp nodebinaryle.hpp nodebinarylt.hpp
parser.o: nodebinarymod.hpp nodebinarymult.hpp nodebinaryne.hpp
parser.o: nodebinaryor.hpp nodebinarysub.hpp nodeblock.hpp
parser.o: nodefunctioncall.hpp nodecondition.hpp nodeemptycommand.hpp
parser.o: nodefunction.hpp nodeloop.hpp nodeunarynot.hpp nodeunary.hpp
parser.o: nodeunaryreturn.hpp nodeunarysub.hpp nodevalue.hpp nodevariable.hpp
parser.o: valuebool.hpp valueedge.hpp valuestruct.hpp valuenull.hpp
parser.o: valuegraph.hpp valueedgeset.hpp valuefloat.hpp valueint.hpp
parser.o: valuereference.hpp valuestring.hpp valuevertex.hpp
parser.o: valuevertexset.hpp
stringtable.o: stringtable.hpp general.hpp baseobject.hpp node.hpp
stringtable.o: context.hpp countptr.hpp value.hpp
tests.o: tests.hpp general.hpp baseobject.hpp logger.hpp valueint.hpp
tests.o: value.hpp countptr.hpp valuefloat.hpp valuebool.hpp valuestring.hpp
tests.o: valuestruct.hpp valuenull.hpp valuegraph.hpp valuevertex.hpp
tests.o: valueedgeset.hpp valueedge.hpp valuevertexset.hpp lexan.hpp
tests.o: lexaniterator.hpp lexantokens.hpp node.hpp context.hpp
tests.o: stringtable.hpp parser.hpp nodeunarysub.hpp nodeunary.hpp
tests.o: nodeunarynot.hpp nodebinaryadd.hpp nodebinary.hpp nodebinarysub.hpp
tests.o: nodeblock.hpp nodefunctioncall.hpp nodecondition.hpp
tests.o: nodevariable.hpp nodeemptycommand.hpp nodefunction.hpp
tests.o: nodebinaryass.hpp nodevalue.hpp nodebinarylt.hpp nodeunaryreturn.hpp
tests.o: nodebinarymult.hpp
valuebool.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuebool.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuebool.o: valuestruct.hpp node.hpp context.hpp stringtable.hpp
value.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
value.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
value.o: valuestruct.hpp valuereference.hpp valuegraph.hpp valuevertex.hpp
value.o: valueedgeset.hpp valueedge.hpp
valueedge.o: valueedge.hpp general.hpp valuestruct.hpp value.hpp
valueedge.o: baseobject.hpp countptr.hpp valuenull.hpp valuegraph.hpp
valueedge.o: valuebool.hpp valuevertex.hpp valueedgeset.hpp node.hpp
valueedge.o: context.hpp stringtable.hpp
valueedgeset.o: valueedgeset.hpp general.hpp value.hpp baseobject.hpp
valueedgeset.o: countptr.hpp logger.hpp valuebool.hpp valueedge.hpp
valueedgeset.o: valuestruct.hpp valuenull.hpp valuegraph.hpp node.hpp
valueedgeset.o: context.hpp stringtable.hpp
valuefloat.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuefloat.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuefloat.o: valuestruct.hpp node.hpp context.hpp stringtable.hpp
valuegraph.o: valuegraph.hpp general.hpp value.hpp baseobject.hpp
valuegraph.o: countptr.hpp logger.hpp valuebool.hpp valuevertex.hpp
valuegraph.o: valueedgeset.hpp valuestruct.hpp valuenull.hpp valueedge.hpp
valuegraph.o: node.hpp context.hpp stringtable.hpp
valueint.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valueint.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valueint.o: valuestruct.hpp node.hpp context.hpp stringtable.hpp
valuenull.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuenull.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuenull.o: valuestruct.hpp node.hpp context.hpp stringtable.hpp
valuereference.o: valuereference.hpp general.hpp value.hpp baseobject.hpp
valuereference.o: countptr.hpp valuebool.hpp node.hpp context.hpp
valuereference.o: stringtable.hpp
valuestring.o: value.hpp general.hpp baseobject.hpp countptr.hpp
valuestring.o: valuenull.hpp valuebool.hpp valueint.hpp valuefloat.hpp
valuestring.o: valuestring.hpp valuestruct.hpp node.hpp context.hpp
valuestring.o: stringtable.hpp
valuestruct.o: value.hpp general.hpp baseobject.hpp countptr.hpp
valuestruct.o: valuenull.hpp valuebool.hpp valueint.hpp valuefloat.hpp
valuestruct.o: valuestring.hpp valuestruct.hpp node.hpp context.hpp
valuestruct.o: stringtable.hpp
valuevertex.o: valuevertex.hpp general.hpp value.hpp baseobject.hpp
valuevertex.o: countptr.hpp valueedgeset.hpp valuegraph.hpp valuestruct.hpp
valuevertex.o: valuenull.hpp valuebool.hpp valueedge.hpp valuevertexset.hpp
valuevertex.o: node.hpp context.hpp stringtable.hpp
valuevertexset.o: valuevertexset.hpp general.hpp value.hpp baseobject.hpp
valuevertexset.o: countptr.hpp valuebool.hpp valuevertex.hpp valueedgeset.hpp
valuevertexset.o: valuegraph.hpp valuestruct.hpp valuenull.hpp logger.hpp
valuevertexset.o: node.hpp context.hpp stringtable.hpp
