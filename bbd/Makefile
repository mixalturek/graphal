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
.PHONY: operators
.PHONY: builtin
.PHONY: svnlog
#.PHONY: install

build: $(TARGET)

rebuild: clean all

all: bison operators builtin depend $(TARGET)

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

svnlog:
	svn log --revision $(shell svnversion -c | tr 'A-Z' ' ') --verbose

# DO NOT DELETE

baseobject.o: baseobject.hpp general.hpp logger.hpp
context.o: context.hpp general.hpp baseobject.hpp countptr.hpp value.hpp
context.o: stringtable.hpp valuenull.hpp nodefunction.hpp node.hpp
context.o: nodefunctioncall.hpp valuearray.hpp valuestring.hpp
context.o: valuereference.hpp nodevalue.hpp nodeblock.hpp logger.hpp
context.o: nodebuiltinecho.hpp nodefunctionbuiltin.hpp nodebuiltindump.hpp
context.o: nodebuiltinarray.hpp nodebuiltinstruct.hpp nodebuiltingraph.hpp
context.o: nodebuiltinsize.hpp
init_static_objects.o: general.hpp baseobject.hpp logger.hpp context.hpp
init_static_objects.o: countptr.hpp value.hpp stringtable.hpp valuenull.hpp
init_static_objects.o: valuebool.hpp
lexan.o: lexan.hpp general.hpp baseobject.hpp lexaniterator.hpp
lexan.o: lexantokens.hpp node.hpp countptr.hpp value.hpp nodeblock.hpp
lexan.o: nodefunctioncall.hpp parser.hpp lexaniteratorstring.hpp
lexan.o: lexaniteratorfile.hpp logger.hpp context.hpp stringtable.hpp
lexaniterator.o: lexaniterator.hpp general.hpp baseobject.hpp
lexaniteratorfile.o: lexaniteratorfile.hpp general.hpp lexaniterator.hpp
lexaniteratorfile.o: baseobject.hpp context.hpp countptr.hpp value.hpp
lexaniteratorfile.o: stringtable.hpp
lexaniteratorstring.o: lexaniteratorstring.hpp general.hpp lexaniterator.hpp
lexaniteratorstring.o: baseobject.hpp context.hpp countptr.hpp value.hpp
lexaniteratorstring.o: stringtable.hpp
logger.o: logger.hpp general.hpp baseobject.hpp
main.o: general.hpp baseobject.hpp logger.hpp tests.hpp context.hpp
main.o: countptr.hpp value.hpp stringtable.hpp
nodebinaryadd.o: nodebinaryadd.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryadd.o: baseobject.hpp countptr.hpp value.hpp
nodebinaryand.o: nodebinaryand.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryand.o: baseobject.hpp countptr.hpp value.hpp
nodebinaryassadd.o: nodebinaryassadd.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryassadd.o: baseobject.hpp countptr.hpp value.hpp
nodebinaryass.o: nodebinaryass.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryass.o: baseobject.hpp countptr.hpp value.hpp
nodebinaryassdiv.o: nodebinaryassdiv.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryassdiv.o: baseobject.hpp countptr.hpp value.hpp
nodebinaryassmod.o: nodebinaryassmod.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryassmod.o: baseobject.hpp countptr.hpp value.hpp
nodebinaryassmult.o: nodebinaryassmult.hpp general.hpp nodebinary.hpp
nodebinaryassmult.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodebinaryasssub.o: nodebinaryasssub.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryasssub.o: baseobject.hpp countptr.hpp value.hpp
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
nodebuiltinarray.o: nodebuiltinarray.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinarray.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinarray.o: value.hpp context.hpp stringtable.hpp logger.hpp
nodebuiltinarray.o: valuearray.hpp valuebool.hpp valueint.hpp valuefloat.hpp
nodebuiltinarray.o: valuenull.hpp
nodebuiltindump.o: nodebuiltindump.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltindump.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltindump.o: value.hpp context.hpp stringtable.hpp logger.hpp
nodebuiltinecho.o: nodebuiltinecho.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinecho.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinecho.o: value.hpp context.hpp stringtable.hpp logger.hpp
nodebuiltingraph.o: nodebuiltingraph.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltingraph.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltingraph.o: value.hpp context.hpp stringtable.hpp logger.hpp
nodebuiltingraph.o: valuegraph.hpp
nodebuiltinsize.o: nodebuiltinsize.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinsize.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinsize.o: value.hpp context.hpp stringtable.hpp logger.hpp
nodebuiltinsize.o: valuearray.hpp valuestring.hpp valueint.hpp
nodebuiltinstruct.o: nodebuiltinstruct.hpp general.hpp
nodebuiltinstruct.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinstruct.o: baseobject.hpp countptr.hpp value.hpp context.hpp
nodebuiltinstruct.o: stringtable.hpp logger.hpp valuestruct.hpp valuenull.hpp
nodecondition.o: nodecondition.hpp general.hpp node.hpp baseobject.hpp
nodecondition.o: countptr.hpp value.hpp valuenull.hpp nodeemptycommand.hpp
node.o: node.hpp general.hpp baseobject.hpp countptr.hpp value.hpp
nodeemptycommand.o: nodeemptycommand.hpp general.hpp node.hpp baseobject.hpp
nodeemptycommand.o: countptr.hpp value.hpp valuenull.hpp
nodefunctionbuiltin.o: nodefunctionbuiltin.hpp general.hpp nodefunction.hpp
nodefunctionbuiltin.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodefunctionbuiltin.o: context.hpp stringtable.hpp logger.hpp
nodefunctioncall.o: nodefunctioncall.hpp general.hpp node.hpp baseobject.hpp
nodefunctioncall.o: countptr.hpp value.hpp nodefunction.hpp nodeblock.hpp
nodefunctioncall.o: valuenull.hpp logger.hpp context.hpp stringtable.hpp
nodefunction.o: nodefunction.hpp general.hpp node.hpp baseobject.hpp
nodefunction.o: countptr.hpp value.hpp context.hpp stringtable.hpp
nodefunctionscript.o: nodefunctionscript.hpp general.hpp nodefunction.hpp
nodefunctionscript.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodefunctionscript.o: nodeemptycommand.hpp valuenull.hpp context.hpp
nodefunctionscript.o: stringtable.hpp
nodejumpbreak.o: nodejumpbreak.hpp general.hpp node.hpp baseobject.hpp
nodejumpbreak.o: countptr.hpp value.hpp valuenull.hpp
nodejumpcontinue.o: nodejumpcontinue.hpp general.hpp node.hpp baseobject.hpp
nodejumpcontinue.o: countptr.hpp value.hpp valuenull.hpp
nodeloop.o: nodeloop.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodeloop.o: value.hpp valuenull.hpp valuebool.hpp nodeemptycommand.hpp
nodeloop.o: nodevalue.hpp nodejumpbreak.hpp nodejumpcontinue.hpp
nodeunary.o: nodeunary.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodeunary.o: value.hpp
nodeunarydecpost.o: valuebool.hpp general.hpp value.hpp baseobject.hpp
nodeunarydecpost.o: countptr.hpp nodeunarydecpost.hpp nodeunary.hpp node.hpp
nodeunarydecpre.o: valuebool.hpp general.hpp value.hpp baseobject.hpp
nodeunarydecpre.o: countptr.hpp nodeunarydecpre.hpp nodeunary.hpp node.hpp
nodeunaryincpost.o: valuebool.hpp general.hpp value.hpp baseobject.hpp
nodeunaryincpost.o: countptr.hpp nodeunaryincpost.hpp nodeunary.hpp node.hpp
nodeunaryincpre.o: valuebool.hpp general.hpp value.hpp baseobject.hpp
nodeunaryincpre.o: countptr.hpp nodeunaryincpre.hpp nodeunary.hpp node.hpp
nodeunarynot.o: nodeunarynot.hpp general.hpp nodeunary.hpp node.hpp
nodeunarynot.o: baseobject.hpp countptr.hpp value.hpp
nodeunaryreturn.o: nodeunaryreturn.hpp general.hpp nodeunary.hpp node.hpp
nodeunaryreturn.o: baseobject.hpp countptr.hpp value.hpp
nodeunarysub.o: nodeunarysub.hpp general.hpp nodeunary.hpp node.hpp
nodeunarysub.o: baseobject.hpp countptr.hpp value.hpp
nodevalue.o: nodevalue.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodevalue.o: value.hpp
parser.o: general.hpp lexan.hpp baseobject.hpp lexaniterator.hpp
parser.o: lexantokens.hpp node.hpp countptr.hpp value.hpp nodeblock.hpp
parser.o: nodefunctioncall.hpp parser.hpp context.hpp stringtable.hpp
parser.o: nodebinaryadd.hpp nodebinary.hpp nodebinaryand.hpp
parser.o: nodebinaryass.hpp nodebinaryassadd.hpp nodebinaryasssub.hpp
parser.o: nodebinaryassmult.hpp nodebinaryassdiv.hpp nodebinaryassmod.hpp
parser.o: nodebinarydiv.hpp nodebinaryeq.hpp nodebinaryge.hpp
parser.o: nodebinarygt.hpp nodebinaryle.hpp nodebinarylt.hpp
parser.o: nodebinarymod.hpp nodebinarymult.hpp nodebinaryne.hpp
parser.o: nodebinaryor.hpp nodebinarysub.hpp nodebinaryindex.hpp
parser.o: nodebinarymember.hpp nodecondition.hpp nodeemptycommand.hpp
parser.o: nodefunctionscript.hpp nodefunction.hpp nodeloop.hpp
parser.o: nodeunarynot.hpp nodeunary.hpp nodeunaryreturn.hpp nodeunarysub.hpp
parser.o: nodeunaryincpre.hpp nodeunaryincpost.hpp nodeunarydecpre.hpp
parser.o: nodeunarydecpost.hpp nodevalue.hpp nodejumpbreak.hpp
parser.o: nodejumpcontinue.hpp valuebool.hpp valueedge.hpp valuestruct.hpp
parser.o: valuenull.hpp valuegraph.hpp valueedgeset.hpp valuefloat.hpp
parser.o: valueint.hpp valuestring.hpp valuevertex.hpp valuevertexset.hpp
parser.o: valueidentifier.hpp logger.hpp
stringtable.o: stringtable.hpp general.hpp baseobject.hpp
tests.o: tests.hpp general.hpp baseobject.hpp logger.hpp valueint.hpp
tests.o: value.hpp countptr.hpp valuefloat.hpp valuebool.hpp valuestring.hpp
tests.o: valuestruct.hpp valuenull.hpp valuereference.hpp valueidentifier.hpp
tests.o: context.hpp stringtable.hpp valuegraph.hpp valuevertex.hpp
tests.o: valueedgeset.hpp valueedge.hpp valuevertexset.hpp lexan.hpp
tests.o: lexaniterator.hpp lexantokens.hpp node.hpp nodeblock.hpp
tests.o: nodefunctioncall.hpp parser.hpp nodeunarysub.hpp nodeunary.hpp
tests.o: nodeunarynot.hpp nodebinaryadd.hpp nodebinary.hpp nodebinarysub.hpp
tests.o: nodecondition.hpp nodeemptycommand.hpp nodefunctionscript.hpp
tests.o: nodefunction.hpp nodebinaryass.hpp nodevalue.hpp nodebinarylt.hpp
tests.o: nodeunaryreturn.hpp nodebinarymult.hpp valuearray.hpp
valuearray.o: valuearray.hpp general.hpp value.hpp baseobject.hpp
valuearray.o: countptr.hpp valuebool.hpp valuereference.hpp valuenull.hpp
valuearray.o: valueint.hpp valuefloat.hpp logger.hpp
valuebool.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuebool.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuebool.o: valuestruct.hpp valuearray.hpp logger.hpp
value.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
value.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
value.o: valuestruct.hpp valuearray.hpp valuereference.hpp
value.o: valueidentifier.hpp context.hpp stringtable.hpp valuegraph.hpp
value.o: valuevertex.hpp valueedgeset.hpp valueedge.hpp logger.hpp
valueedge.o: valueedge.hpp general.hpp valuestruct.hpp value.hpp
valueedge.o: baseobject.hpp countptr.hpp valuenull.hpp valuegraph.hpp
valueedge.o: valuebool.hpp valuevertex.hpp valueedgeset.hpp
valueedgeset.o: valueedgeset.hpp general.hpp value.hpp baseobject.hpp
valueedgeset.o: countptr.hpp logger.hpp valuebool.hpp valueedge.hpp
valueedgeset.o: valuestruct.hpp valuenull.hpp valuegraph.hpp
valuefloat.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuefloat.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuefloat.o: valuestruct.hpp valuearray.hpp logger.hpp
valuegraph.o: valuegraph.hpp general.hpp value.hpp baseobject.hpp
valuegraph.o: countptr.hpp logger.hpp valuebool.hpp valuevertex.hpp
valuegraph.o: valueedgeset.hpp valuestruct.hpp valuenull.hpp valueedge.hpp
valueidentifier.o: valueidentifier.hpp general.hpp value.hpp baseobject.hpp
valueidentifier.o: countptr.hpp context.hpp stringtable.hpp valuenull.hpp
valueidentifier.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valueidentifier.o: valuestruct.hpp valuereference.hpp valuegraph.hpp
valueidentifier.o: valuevertex.hpp valueedgeset.hpp valueedge.hpp
valueidentifier.o: valuevertexset.hpp logger.hpp
valueint.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valueint.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valueint.o: valuestruct.hpp valuearray.hpp logger.hpp
valuenull.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuenull.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuenull.o: valuestruct.hpp
valuereference.o: valuereference.hpp general.hpp value.hpp baseobject.hpp
valuereference.o: countptr.hpp valuenull.hpp valuebool.hpp valueint.hpp
valuereference.o: valuefloat.hpp valuestring.hpp valuestruct.hpp
valuereference.o: valueidentifier.hpp context.hpp stringtable.hpp
valuereference.o: valuegraph.hpp valuevertex.hpp valueedgeset.hpp
valuereference.o: valueedge.hpp valuevertexset.hpp
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
