TARGET		= bbd
CC			= g++
CFLAGS		= -std=c++98 -pedantic -Wall
LDFLAGS		=
OBJECTS		= $(shell ls *.cpp | sed 's/.cpp/.o/')

.PHONY: build
.PHONY: rebuild
.PHONY: all
.PHONY: depend
.PHONY: run
.PHONY: clean
.PHONY: todo
.PHONY: lines
.PHONY: bison
.PHYNY: operators
#.PHONY: install

build: $(TARGET)

rebuild: clean all

all: bison operators depend $(TARGET)

%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

bison:
	bison -d -o parser.cpp parser.y

operators: gen_operators.pl
	perl gen_operators.pl

depend:
	makedepend -Y -m $(shell ls *.cpp) 2>&1 | grep -v '\(cassert\|algorithm\|set\|stream\|fstream\|iostream\|map\|deque\|vector\|stack\|list\|typeinfo\|stdexcept\|cmath\)'

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
context.o: nodefunctioncall.hpp valuearray.hpp valuestring.hpp nodevalue.hpp
context.o: nodeblock.hpp logger.hpp
init_static_objects.o: general.hpp baseobject.hpp valuestruct.hpp value.hpp
init_static_objects.o: countptr.hpp valuenull.hpp logger.hpp context.hpp
init_static_objects.o: stringtable.hpp
lexan.o: lexan.hpp general.hpp baseobject.hpp lexaniterator.hpp
lexan.o: lexantokens.hpp node.hpp countptr.hpp value.hpp nodeblock.hpp
lexan.o: nodefunctioncall.hpp parser.hpp stringtable.hpp
lexan.o: lexaniteratorstring.hpp lexaniteratorfile.hpp logger.hpp context.hpp
lexaniterator.o: lexaniterator.hpp general.hpp baseobject.hpp
lexaniteratorfile.o: lexaniteratorfile.hpp general.hpp lexaniterator.hpp
lexaniteratorfile.o: baseobject.hpp
lexaniteratorstring.o: lexaniteratorstring.hpp general.hpp lexaniterator.hpp
lexaniteratorstring.o: baseobject.hpp
logger.o: logger.hpp general.hpp baseobject.hpp
main.o: general.hpp baseobject.hpp logger.hpp tests.hpp context.hpp
main.o: countptr.hpp value.hpp stringtable.hpp
nodebinaryadd.o: nodebinaryadd.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryadd.o: baseobject.hpp countptr.hpp value.hpp
nodebinaryand.o: nodebinaryand.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryand.o: baseobject.hpp countptr.hpp value.hpp
nodebinaryassadd.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodebinaryassadd.o: countptr.hpp value.hpp nodebinaryassadd.hpp
nodebinaryassadd.o: nodebinary.hpp
nodebinaryass.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodebinaryass.o: countptr.hpp value.hpp nodebinaryass.hpp nodebinary.hpp
nodebinaryassdiv.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodebinaryassdiv.o: countptr.hpp value.hpp nodebinaryassdiv.hpp
nodebinaryassdiv.o: nodebinary.hpp
nodebinaryassmod.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodebinaryassmod.o: countptr.hpp value.hpp nodebinaryassmod.hpp
nodebinaryassmod.o: nodebinary.hpp
nodebinaryassmult.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodebinaryassmult.o: countptr.hpp value.hpp nodebinaryassmult.hpp
nodebinaryassmult.o: nodebinary.hpp
nodebinaryasssub.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodebinaryasssub.o: countptr.hpp value.hpp nodebinaryasssub.hpp
nodebinaryasssub.o: nodebinary.hpp
nodebinary.o: nodebinary.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodebinary.o: value.hpp
nodebinarydiv.o: nodebinarydiv.hpp general.hpp nodebinary.hpp node.hpp
nodebinarydiv.o: baseobject.hpp countptr.hpp value.hpp
nodebinaryeq.o: nodebinaryeq.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryeq.o: baseobject.hpp countptr.hpp value.hpp
nodebinaryge.o: nodebinaryge.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryge.o: baseobject.hpp countptr.hpp value.hpp
nodebinarygt.o: nodebinarygt.hpp general.hpp nodebinary.hpp node.hpp
nodebinarygt.o: baseobject.hpp countptr.hpp value.hpp
nodebinaryindex.o: nodebinaryindex.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryindex.o: baseobject.hpp countptr.hpp value.hpp
nodebinaryle.o: nodebinaryle.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryle.o: baseobject.hpp countptr.hpp value.hpp
nodebinarylt.o: nodebinarylt.hpp general.hpp nodebinary.hpp node.hpp
nodebinarylt.o: baseobject.hpp countptr.hpp value.hpp
nodebinarymember.o: nodebinarymember.hpp general.hpp nodebinary.hpp node.hpp
nodebinarymember.o: baseobject.hpp countptr.hpp value.hpp
nodebinarymod.o: nodebinarymod.hpp general.hpp nodebinary.hpp node.hpp
nodebinarymod.o: baseobject.hpp countptr.hpp value.hpp
nodebinarymult.o: nodebinarymult.hpp general.hpp nodebinary.hpp node.hpp
nodebinarymult.o: baseobject.hpp countptr.hpp value.hpp
nodebinaryne.o: nodebinaryne.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryne.o: baseobject.hpp countptr.hpp value.hpp
nodebinaryor.o: nodebinaryor.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryor.o: baseobject.hpp countptr.hpp value.hpp
nodebinarysub.o: nodebinarysub.hpp general.hpp nodebinary.hpp node.hpp
nodebinarysub.o: baseobject.hpp countptr.hpp value.hpp
nodeblock.o: nodeblock.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodeblock.o: value.hpp nodefunctioncall.hpp valuenull.hpp
nodecondition.o: nodecondition.hpp general.hpp node.hpp baseobject.hpp
nodecondition.o: countptr.hpp value.hpp valuenull.hpp nodeemptycommand.hpp
node.o: node.hpp general.hpp baseobject.hpp countptr.hpp value.hpp
nodeemptycommand.o: nodeemptycommand.hpp general.hpp node.hpp baseobject.hpp
nodeemptycommand.o: countptr.hpp value.hpp valuenull.hpp
nodefunctioncall.o: nodefunctioncall.hpp general.hpp node.hpp baseobject.hpp
nodefunctioncall.o: countptr.hpp value.hpp nodefunction.hpp nodeblock.hpp
nodefunctioncall.o: valuenull.hpp logger.hpp context.hpp stringtable.hpp
nodefunction.o: nodefunction.hpp general.hpp node.hpp baseobject.hpp
nodefunction.o: countptr.hpp value.hpp nodeemptycommand.hpp valuenull.hpp
nodefunction.o: context.hpp stringtable.hpp
nodejumpbreak.o: nodejumpbreak.hpp general.hpp node.hpp baseobject.hpp
nodejumpbreak.o: countptr.hpp value.hpp valuenull.hpp
nodejumpcontinue.o: nodejumpcontinue.hpp general.hpp node.hpp baseobject.hpp
nodejumpcontinue.o: countptr.hpp value.hpp valuenull.hpp
nodeloop.o: nodeloop.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodeloop.o: value.hpp valuenull.hpp valuebool.hpp nodeemptycommand.hpp
nodeloop.o: nodevalue.hpp nodejumpbreak.hpp nodejumpcontinue.hpp
nodeunary.o: nodeunary.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodeunary.o: value.hpp
nodeunarydecpost.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodeunarydecpost.o: countptr.hpp value.hpp valueint.hpp nodeunarydecpost.hpp
nodeunarydecpost.o: nodeunary.hpp
nodeunarydecpre.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodeunarydecpre.o: countptr.hpp value.hpp valueint.hpp nodeunarydecpre.hpp
nodeunarydecpre.o: nodeunary.hpp
nodeunaryincpost.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodeunaryincpost.o: countptr.hpp value.hpp valueint.hpp nodeunaryincpost.hpp
nodeunaryincpost.o: nodeunary.hpp
nodeunaryincpre.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodeunaryincpre.o: countptr.hpp value.hpp valueint.hpp nodeunaryincpre.hpp
nodeunaryincpre.o: nodeunary.hpp
nodeunarynot.o: nodeunarynot.hpp general.hpp nodeunary.hpp node.hpp
nodeunarynot.o: baseobject.hpp countptr.hpp value.hpp
nodeunaryreturn.o: nodeunaryreturn.hpp general.hpp nodeunary.hpp node.hpp
nodeunaryreturn.o: baseobject.hpp countptr.hpp value.hpp
nodeunarysub.o: nodeunarysub.hpp general.hpp nodeunary.hpp node.hpp
nodeunarysub.o: baseobject.hpp countptr.hpp value.hpp
nodevalue.o: nodevalue.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodevalue.o: value.hpp
nodevariable.o: nodevariable.hpp general.hpp node.hpp baseobject.hpp
nodevariable.o: countptr.hpp value.hpp valuefloat.hpp context.hpp
nodevariable.o: stringtable.hpp
parser.o: general.hpp lexan.hpp baseobject.hpp lexaniterator.hpp
parser.o: lexantokens.hpp node.hpp countptr.hpp value.hpp nodeblock.hpp
parser.o: nodefunctioncall.hpp parser.hpp stringtable.hpp context.hpp
parser.o: nodebinaryadd.hpp nodebinary.hpp nodebinaryand.hpp
parser.o: nodebinaryass.hpp nodebinaryassadd.hpp nodebinaryasssub.hpp
parser.o: nodebinaryassmult.hpp nodebinaryassdiv.hpp nodebinaryassmod.hpp
parser.o: nodebinarydiv.hpp nodebinaryeq.hpp nodebinaryge.hpp
parser.o: nodebinarygt.hpp nodebinaryle.hpp nodebinarylt.hpp
parser.o: nodebinarymod.hpp nodebinarymult.hpp nodebinaryne.hpp
parser.o: nodebinaryor.hpp nodebinarysub.hpp nodebinaryindex.hpp
parser.o: nodebinarymember.hpp nodecondition.hpp nodeemptycommand.hpp
parser.o: nodefunction.hpp nodeloop.hpp nodeunarynot.hpp nodeunary.hpp
parser.o: nodeunaryreturn.hpp nodeunarysub.hpp nodeunaryincpre.hpp
parser.o: nodeunaryincpost.hpp nodeunarydecpre.hpp nodeunarydecpost.hpp
parser.o: nodevalue.hpp nodevariable.hpp nodejumpbreak.hpp
parser.o: nodejumpcontinue.hpp valuebool.hpp valueedge.hpp valuestruct.hpp
parser.o: valuenull.hpp valuegraph.hpp valueedgeset.hpp valuefloat.hpp
parser.o: valueint.hpp valuestring.hpp valuevertex.hpp valuevertexset.hpp
stringtable.o: stringtable.hpp general.hpp baseobject.hpp
tests.o: tests.hpp general.hpp baseobject.hpp logger.hpp valueint.hpp
tests.o: value.hpp countptr.hpp valuefloat.hpp valuebool.hpp valuestring.hpp
tests.o: valuestruct.hpp valuenull.hpp valuereference.hpp valuegraph.hpp
tests.o: valuevertex.hpp valueedgeset.hpp valueedge.hpp valuevertexset.hpp
tests.o: lexan.hpp lexaniterator.hpp lexantokens.hpp node.hpp nodeblock.hpp
tests.o: nodefunctioncall.hpp parser.hpp stringtable.hpp context.hpp
tests.o: nodeunarysub.hpp nodeunary.hpp nodeunarynot.hpp nodebinaryadd.hpp
tests.o: nodebinary.hpp nodebinarysub.hpp nodecondition.hpp nodevariable.hpp
tests.o: nodeemptycommand.hpp nodefunction.hpp nodebinaryass.hpp
tests.o: nodevalue.hpp nodebinarylt.hpp nodeunaryreturn.hpp
tests.o: nodebinarymult.hpp
valuearray.o: valuearray.hpp general.hpp value.hpp baseobject.hpp
valuearray.o: countptr.hpp valuenull.hpp valuebool.hpp valuereference.hpp
valuearray.o: logger.hpp
valuebool.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuebool.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuebool.o: valuestruct.hpp logger.hpp
value.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
value.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
value.o: valuestruct.hpp valuereference.hpp valuegraph.hpp valuevertex.hpp
value.o: valueedgeset.hpp valueedge.hpp
valueedge.o: valueedge.hpp general.hpp valuestruct.hpp value.hpp
valueedge.o: baseobject.hpp countptr.hpp valuenull.hpp valuegraph.hpp
valueedge.o: valuebool.hpp valuevertex.hpp valueedgeset.hpp
valueedgeset.o: valueedgeset.hpp general.hpp value.hpp baseobject.hpp
valueedgeset.o: countptr.hpp logger.hpp valuebool.hpp valueedge.hpp
valueedgeset.o: valuestruct.hpp valuenull.hpp valuegraph.hpp
valuefloat.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuefloat.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuefloat.o: valuestruct.hpp logger.hpp
valuegraph.o: valuegraph.hpp general.hpp value.hpp baseobject.hpp
valuegraph.o: countptr.hpp logger.hpp valuebool.hpp valuevertex.hpp
valuegraph.o: valueedgeset.hpp valuestruct.hpp valuenull.hpp valueedge.hpp
valueint.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valueint.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valueint.o: valuestruct.hpp logger.hpp
valuenull.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuenull.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuenull.o: valuestruct.hpp
valuereference.o: valuereference.hpp general.hpp value.hpp baseobject.hpp
valuereference.o: countptr.hpp valuebool.hpp
valuestring.o: value.hpp general.hpp baseobject.hpp countptr.hpp
valuestring.o: valuenull.hpp valuebool.hpp valueint.hpp valuefloat.hpp
valuestring.o: valuestring.hpp valuestruct.hpp
valuestruct.o: valuestruct.hpp general.hpp value.hpp baseobject.hpp
valuestruct.o: countptr.hpp valuenull.hpp valuebool.hpp valuereference.hpp
valuestruct.o: context.hpp stringtable.hpp
valuevertex.o: valuevertex.hpp general.hpp value.hpp baseobject.hpp
valuevertex.o: countptr.hpp valueedgeset.hpp valuegraph.hpp valuestruct.hpp
valuevertex.o: valuenull.hpp valuebool.hpp valueedge.hpp valuevertexset.hpp
valuevertexset.o: valuevertexset.hpp general.hpp value.hpp baseobject.hpp
valuevertexset.o: countptr.hpp valuebool.hpp valuevertex.hpp valueedgeset.hpp
valuevertexset.o: valuegraph.hpp valuestruct.hpp valuenull.hpp logger.hpp
