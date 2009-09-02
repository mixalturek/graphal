TARGET  = bbd
CC      = g++
CFLAGS  = -std=c++98 -pedantic -Wall
# CFLAGS  = -std=c++98 -pedantic -Wall -O2 -s -DNDEBUG
LDFLAGS =
OBJECTS = $(shell ls *.cpp | sed 's/.cpp/.o/')

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
.PHONY: listbuiltin
.PHONY: version
#.PHONY: install

build: $(TARGET)

rebuild: clean all

all: version bison operators builtin depend $(TARGET)

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
	makedepend -Y -m $(shell ls *.cpp) 2>&1 | grep -v '\(cassert\|algorithm\|set\|stream\|fstream\|iostream\|map\|deque\|vector\|stack\|list\|typeinfo\|stdexcept\|cmath\)'

run:
	./$(TARGET)

memoryleaks:
	valgrind ./$(TARGET) --unit-tests ../samples/tests.txt

clean:
	rm -f $(TARGET) *.o core Makefile.bak

todo:
	grep -rI TODO . | grep -v './.svn/'

lines:
	cat *.hpp *.cpp | wc -l

svnlog:
	svn log --revision $(shell svnversion -c | tr 'A-Z' ' ') --verbose

listbuiltin:
	grep '\$funcdecl =' gen_builtin.pl | sed "s/.*'\(.*\)'.*/\1/"

# DO NOT DELETE

baseobject.o: baseobject.hpp general.hpp logger.hpp objectcreator.hpp
baseobject.o: mutexlocker.hpp mutex.hpp
callstackitem.o: callstackitem.hpp general.hpp baseobject.hpp countptr.hpp
callstackitem.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
callstackitem.o: context.hpp stringtable.hpp codeposition.hpp valuenull.hpp
callstackitem.o: valuereference.hpp
clifactory.o: clifactory.hpp general.hpp objectfactory.hpp baseobject.hpp
clifactory.o: clilogger.hpp logger.hpp objectcreator.hpp mutexlocker.hpp
clifactory.o: mutex.hpp climutex.hpp context.hpp countptr.hpp value.hpp
clifactory.o: stringtable.hpp codeposition.hpp callstackitem.hpp
clilogger.o: clilogger.hpp general.hpp logger.hpp baseobject.hpp
clilogger.o: objectcreator.hpp mutexlocker.hpp mutex.hpp context.hpp
clilogger.o: countptr.hpp value.hpp stringtable.hpp codeposition.hpp
clilogger.o: callstackitem.hpp
climutex.o: climutex.hpp general.hpp mutex.hpp
codeposition.o: codeposition.hpp general.hpp baseobject.hpp context.hpp
codeposition.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
codeposition.o: value.hpp stringtable.hpp callstackitem.hpp
context.o: context.hpp general.hpp baseobject.hpp countptr.hpp
context.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
context.o: stringtable.hpp codeposition.hpp callstackitem.hpp valuenull.hpp
context.o: nodefunction.hpp node.hpp nodefunctioncall.hpp valuearray.hpp
context.o: valuestring.hpp valuereference.hpp nodevalue.hpp nodeblock.hpp
context.o: logger.hpp exitvalue.hpp
exitvalue.o: exitvalue.hpp general.hpp baseobject.hpp countptr.hpp
exitvalue.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
init_static_objects.o: general.hpp baseobject.hpp valuenull.hpp value.hpp
init_static_objects.o: countptr.hpp objectcreator.hpp mutexlocker.hpp
init_static_objects.o: mutex.hpp valuebool.hpp
lexan.o: lexan.hpp general.hpp baseobject.hpp lexaniterator.hpp
lexan.o: lexantokens.hpp node.hpp countptr.hpp objectcreator.hpp
lexan.o: mutexlocker.hpp mutex.hpp value.hpp nodeblock.hpp
lexan.o: nodefunctioncall.hpp codeposition.hpp parser.hpp
lexan.o: lexaniteratorstring.hpp lexaniteratorfile.hpp logger.hpp context.hpp
lexan.o: stringtable.hpp callstackitem.hpp
lexaniterator.o: lexaniterator.hpp general.hpp baseobject.hpp
lexaniteratorfile.o: lexaniteratorfile.hpp general.hpp lexaniterator.hpp
lexaniteratorfile.o: baseobject.hpp context.hpp countptr.hpp
lexaniteratorfile.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
lexaniteratorfile.o: stringtable.hpp codeposition.hpp callstackitem.hpp
lexaniteratorstring.o: lexaniteratorstring.hpp general.hpp lexaniterator.hpp
lexaniteratorstring.o: baseobject.hpp context.hpp countptr.hpp
lexaniteratorstring.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
lexaniteratorstring.o: stringtable.hpp codeposition.hpp callstackitem.hpp
logger.o: logger.hpp general.hpp baseobject.hpp objectcreator.hpp
logger.o: mutexlocker.hpp mutex.hpp
main.o: general.hpp baseobject.hpp logger.hpp objectcreator.hpp
main.o: mutexlocker.hpp mutex.hpp tests.hpp context.hpp countptr.hpp
main.o: value.hpp stringtable.hpp codeposition.hpp callstackitem.hpp
main.o: nodebuiltin_inst.hpp version.hpp clifactory.hpp objectfactory.hpp
main.o: valuenull.hpp valuebool.hpp
mutex.o: mutex.hpp general.hpp
mutexlocker.o: mutexlocker.hpp general.hpp mutex.hpp
nodebinaryadd.o: nodebinaryadd.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryadd.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebinaryadd.o: mutexlocker.hpp mutex.hpp value.hpp
nodebinaryand.o: nodebinaryand.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryand.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebinaryand.o: mutexlocker.hpp mutex.hpp value.hpp
nodebinaryassadd.o: nodebinaryassadd.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryassadd.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebinaryassadd.o: mutexlocker.hpp mutex.hpp value.hpp
nodebinaryass.o: nodebinaryass.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryass.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebinaryass.o: mutexlocker.hpp mutex.hpp value.hpp
nodebinaryassdiv.o: nodebinaryassdiv.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryassdiv.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebinaryassdiv.o: mutexlocker.hpp mutex.hpp value.hpp
nodebinaryassmod.o: nodebinaryassmod.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryassmod.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebinaryassmod.o: mutexlocker.hpp mutex.hpp value.hpp
nodebinaryassmult.o: nodebinaryassmult.hpp general.hpp nodebinary.hpp
nodebinaryassmult.o: node.hpp baseobject.hpp countptr.hpp objectcreator.hpp
nodebinaryassmult.o: mutexlocker.hpp mutex.hpp value.hpp
nodebinaryassref.o: valueidentifier.hpp general.hpp value.hpp baseobject.hpp
nodebinaryassref.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
nodebinaryassref.o: context.hpp stringtable.hpp codeposition.hpp
nodebinaryassref.o: callstackitem.hpp nodebinaryassref.hpp nodebinary.hpp
nodebinaryassref.o: node.hpp
nodebinaryasssub.o: nodebinaryasssub.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryasssub.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebinaryasssub.o: mutexlocker.hpp mutex.hpp value.hpp
nodebinary.o: nodebinary.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodebinary.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodebinarydiv.o: nodebinarydiv.hpp general.hpp nodebinary.hpp node.hpp
nodebinarydiv.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebinarydiv.o: mutexlocker.hpp mutex.hpp value.hpp
nodebinaryeq.o: nodebinaryeq.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryeq.o: baseobject.hpp countptr.hpp objectcreator.hpp mutexlocker.hpp
nodebinaryeq.o: mutex.hpp value.hpp
nodebinaryge.o: nodebinaryge.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryge.o: baseobject.hpp countptr.hpp objectcreator.hpp mutexlocker.hpp
nodebinaryge.o: mutex.hpp value.hpp
nodebinarygt.o: nodebinarygt.hpp general.hpp nodebinary.hpp node.hpp
nodebinarygt.o: baseobject.hpp countptr.hpp objectcreator.hpp mutexlocker.hpp
nodebinarygt.o: mutex.hpp value.hpp
nodebinaryindex.o: nodebinaryindex.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryindex.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebinaryindex.o: mutexlocker.hpp mutex.hpp value.hpp
nodebinaryle.o: nodebinaryle.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryle.o: baseobject.hpp countptr.hpp objectcreator.hpp mutexlocker.hpp
nodebinaryle.o: mutex.hpp value.hpp
nodebinarylt.o: nodebinarylt.hpp general.hpp nodebinary.hpp node.hpp
nodebinarylt.o: baseobject.hpp countptr.hpp objectcreator.hpp mutexlocker.hpp
nodebinarylt.o: mutex.hpp value.hpp
nodebinarymember.o: nodebinarymember.hpp general.hpp nodebinary.hpp node.hpp
nodebinarymember.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebinarymember.o: mutexlocker.hpp mutex.hpp value.hpp
nodebinarymod.o: nodebinarymod.hpp general.hpp nodebinary.hpp node.hpp
nodebinarymod.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebinarymod.o: mutexlocker.hpp mutex.hpp value.hpp
nodebinarymult.o: nodebinarymult.hpp general.hpp nodebinary.hpp node.hpp
nodebinarymult.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebinarymult.o: mutexlocker.hpp mutex.hpp value.hpp
nodebinaryne.o: nodebinaryne.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryne.o: baseobject.hpp countptr.hpp objectcreator.hpp mutexlocker.hpp
nodebinaryne.o: mutex.hpp value.hpp
nodebinaryor.o: nodebinaryor.hpp general.hpp nodebinary.hpp node.hpp
nodebinaryor.o: baseobject.hpp countptr.hpp objectcreator.hpp mutexlocker.hpp
nodebinaryor.o: mutex.hpp value.hpp
nodebinarysub.o: nodebinarysub.hpp general.hpp nodebinary.hpp node.hpp
nodebinarysub.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebinarysub.o: mutexlocker.hpp mutex.hpp value.hpp
nodeblock.o: nodeblock.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodeblock.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodeblock.o: nodefunctioncall.hpp codeposition.hpp valuenull.hpp
nodebuiltinadd.o: nodebuiltinadd.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinadd.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinadd.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodebuiltinadd.o: valuenull.hpp context.hpp stringtable.hpp codeposition.hpp
nodebuiltinadd.o: callstackitem.hpp logger.hpp valuevertexset.hpp
nodebuiltinadd.o: valuevertex.hpp valueedgeset.hpp valuegraph.hpp
nodebuiltinadd.o: valuestruct.hpp valueedge.hpp
nodebuiltinarray.o: nodebuiltinarray.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinarray.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinarray.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodebuiltinarray.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinarray.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinarray.o: valuearray.hpp valuebool.hpp valueint.hpp valuefloat.hpp
nodebuiltinassert.o: nodebuiltinassert.hpp general.hpp
nodebuiltinassert.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinassert.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinassert.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinassert.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinassert.o: callstackitem.hpp logger.hpp
nodebuiltinback.o: nodebuiltinback.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinback.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinback.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodebuiltinback.o: valuenull.hpp context.hpp stringtable.hpp codeposition.hpp
nodebuiltinback.o: callstackitem.hpp logger.hpp valuearray.hpp
nodebuiltinbreakpoint.o: nodebuiltinbreakpoint.hpp general.hpp
nodebuiltinbreakpoint.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinbreakpoint.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinbreakpoint.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinbreakpoint.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinbreakpoint.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltincontains.o: nodebuiltincontains.hpp general.hpp
nodebuiltincontains.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltincontains.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltincontains.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltincontains.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltincontains.o: callstackitem.hpp logger.hpp valuegraph.hpp
nodebuiltincontains.o: valuevertexset.hpp valueedgeset.hpp valuevertex.hpp
nodebuiltincontains.o: valuestruct.hpp valueedge.hpp valuebool.hpp
nodebuiltindeleteedge.o: nodebuiltindeleteedge.hpp general.hpp
nodebuiltindeleteedge.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltindeleteedge.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltindeleteedge.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltindeleteedge.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltindeleteedge.o: callstackitem.hpp logger.hpp valuegraph.hpp
nodebuiltindeleteedge.o: valueedge.hpp valuestruct.hpp valueedgeset.hpp
nodebuiltindeletevertex.o: nodebuiltindeletevertex.hpp general.hpp
nodebuiltindeletevertex.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltindeletevertex.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltindeletevertex.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltindeletevertex.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltindeletevertex.o: callstackitem.hpp logger.hpp valuegraph.hpp
nodebuiltindeletevertex.o: valuevertex.hpp valueedgeset.hpp valuestruct.hpp
nodebuiltindeletevertex.o: valuevertexset.hpp
nodebuiltindifference.o: nodebuiltindifference.hpp general.hpp
nodebuiltindifference.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltindifference.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltindifference.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltindifference.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltindifference.o: callstackitem.hpp logger.hpp valuevertexset.hpp
nodebuiltindifference.o: valueedgeset.hpp
nodebuiltindump.o: nodebuiltindump.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltindump.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltindump.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodebuiltindump.o: valuenull.hpp context.hpp stringtable.hpp codeposition.hpp
nodebuiltindump.o: callstackitem.hpp logger.hpp
nodebuiltinedgeset.o: nodebuiltinedgeset.hpp general.hpp
nodebuiltinedgeset.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinedgeset.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinedgeset.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinedgeset.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinedgeset.o: callstackitem.hpp logger.hpp valueedgeset.hpp
nodebuiltinedgeset.o: valuegraph.hpp
nodebuiltinecho.o: nodebuiltinecho.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinecho.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinecho.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodebuiltinecho.o: valuenull.hpp context.hpp stringtable.hpp codeposition.hpp
nodebuiltinecho.o: callstackitem.hpp logger.hpp
nodebuiltinexit.o: nodebuiltinexit.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinexit.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinexit.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodebuiltinexit.o: valuenull.hpp context.hpp stringtable.hpp codeposition.hpp
nodebuiltinexit.o: callstackitem.hpp logger.hpp exitvalue.hpp
nodebuiltinfront.o: nodebuiltinfront.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinfront.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinfront.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodebuiltinfront.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinfront.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinfront.o: valuearray.hpp
nodebuiltingenerateedge.o: nodebuiltingenerateedge.hpp general.hpp
nodebuiltingenerateedge.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingenerateedge.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltingenerateedge.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltingenerateedge.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltingenerateedge.o: callstackitem.hpp logger.hpp valuegraph.hpp
nodebuiltingenerateedge.o: valuevertex.hpp valueedgeset.hpp valuestruct.hpp
nodebuiltingenerateedge.o: valueedge.hpp
nodebuiltingeneratevertex.o: nodebuiltingeneratevertex.hpp general.hpp
nodebuiltingeneratevertex.o: nodefunctionbuiltin.hpp nodefunction.hpp
nodebuiltingeneratevertex.o: node.hpp baseobject.hpp countptr.hpp
nodebuiltingeneratevertex.o: objectcreator.hpp mutexlocker.hpp mutex.hpp
nodebuiltingeneratevertex.o: value.hpp valuenull.hpp context.hpp
nodebuiltingeneratevertex.o: stringtable.hpp codeposition.hpp
nodebuiltingeneratevertex.o: callstackitem.hpp logger.hpp valuegraph.hpp
nodebuiltingeneratevertex.o: valuevertex.hpp valueedgeset.hpp valuestruct.hpp
nodebuiltingetbeginvertex.o: nodebuiltingetbeginvertex.hpp general.hpp
nodebuiltingetbeginvertex.o: nodefunctionbuiltin.hpp nodefunction.hpp
nodebuiltingetbeginvertex.o: node.hpp baseobject.hpp countptr.hpp
nodebuiltingetbeginvertex.o: objectcreator.hpp mutexlocker.hpp mutex.hpp
nodebuiltingetbeginvertex.o: value.hpp valuenull.hpp context.hpp
nodebuiltingetbeginvertex.o: stringtable.hpp codeposition.hpp
nodebuiltingetbeginvertex.o: callstackitem.hpp logger.hpp valueedge.hpp
nodebuiltingetbeginvertex.o: valuestruct.hpp valuegraph.hpp valuevertex.hpp
nodebuiltingetbeginvertex.o: valueedgeset.hpp
nodebuiltingetdegree.o: nodebuiltingetdegree.hpp general.hpp
nodebuiltingetdegree.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetdegree.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltingetdegree.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltingetdegree.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltingetdegree.o: callstackitem.hpp logger.hpp valuevertex.hpp
nodebuiltingetdegree.o: valueedgeset.hpp valuegraph.hpp valuestruct.hpp
nodebuiltingetdegree.o: valueint.hpp
nodebuiltingetedges.o: nodebuiltingetedges.hpp general.hpp
nodebuiltingetedges.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetedges.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltingetedges.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltingetedges.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltingetedges.o: callstackitem.hpp logger.hpp valuegraph.hpp
nodebuiltingetendvertex.o: nodebuiltingetendvertex.hpp general.hpp
nodebuiltingetendvertex.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetendvertex.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltingetendvertex.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltingetendvertex.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltingetendvertex.o: callstackitem.hpp logger.hpp valueedge.hpp
nodebuiltingetendvertex.o: valuestruct.hpp valuegraph.hpp valuevertex.hpp
nodebuiltingetendvertex.o: valueedgeset.hpp
nodebuiltingetneighbors.o: nodebuiltingetneighbors.hpp general.hpp
nodebuiltingetneighbors.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetneighbors.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltingetneighbors.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltingetneighbors.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltingetneighbors.o: callstackitem.hpp logger.hpp valuevertex.hpp
nodebuiltingetneighbors.o: valueedgeset.hpp valuegraph.hpp valuestruct.hpp
nodebuiltingetneighbors.o: valuevertexset.hpp
nodebuiltingetnumedges.o: nodebuiltingetnumedges.hpp general.hpp
nodebuiltingetnumedges.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetnumedges.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltingetnumedges.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltingetnumedges.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltingetnumedges.o: callstackitem.hpp logger.hpp valuegraph.hpp
nodebuiltingetnumedges.o: valueedgeset.hpp valueint.hpp
nodebuiltingetnumvertices.o: nodebuiltingetnumvertices.hpp general.hpp
nodebuiltingetnumvertices.o: nodefunctionbuiltin.hpp nodefunction.hpp
nodebuiltingetnumvertices.o: node.hpp baseobject.hpp countptr.hpp
nodebuiltingetnumvertices.o: objectcreator.hpp mutexlocker.hpp mutex.hpp
nodebuiltingetnumvertices.o: value.hpp valuenull.hpp context.hpp
nodebuiltingetnumvertices.o: stringtable.hpp codeposition.hpp
nodebuiltingetnumvertices.o: callstackitem.hpp logger.hpp valuegraph.hpp
nodebuiltingetnumvertices.o: valuevertexset.hpp valueint.hpp
nodebuiltingetvertices.o: nodebuiltingetvertices.hpp general.hpp
nodebuiltingetvertices.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetvertices.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltingetvertices.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltingetvertices.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltingetvertices.o: callstackitem.hpp logger.hpp valuegraph.hpp
nodebuiltingraph.o: nodebuiltingraph.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltingraph.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltingraph.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodebuiltingraph.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltingraph.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltingraph.o: valuegraph.hpp
nodebuiltinhasnext.o: nodebuiltinhasnext.hpp general.hpp
nodebuiltinhasnext.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinhasnext.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinhasnext.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinhasnext.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinhasnext.o: callstackitem.hpp logger.hpp
nodebuiltin_inst.o: general.hpp context.hpp baseobject.hpp countptr.hpp
nodebuiltin_inst.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodebuiltin_inst.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltin_inst.o: nodebuiltinecho.hpp nodefunctionbuiltin.hpp
nodebuiltin_inst.o: nodefunction.hpp node.hpp nodebuiltindump.hpp
nodebuiltin_inst.o: nodebuiltinexit.hpp nodebuiltinassert.hpp
nodebuiltin_inst.o: nodebuiltinverify.hpp nodebuiltinbreakpoint.hpp
nodebuiltin_inst.o: nodebuiltinisnull.hpp nodebuiltinisbool.hpp
nodebuiltin_inst.o: nodebuiltinisint.hpp nodebuiltinisfloat.hpp
nodebuiltin_inst.o: nodebuiltinisstring.hpp nodebuiltinisstruct.hpp
nodebuiltin_inst.o: nodebuiltinisarray.hpp nodebuiltinisgraph.hpp
nodebuiltin_inst.o: nodebuiltinisvertex.hpp nodebuiltinisedge.hpp
nodebuiltin_inst.o: nodebuiltinisvertexset.hpp nodebuiltinisedgeset.hpp
nodebuiltin_inst.o: nodebuiltinprintstacktrace.hpp nodebuiltiniterator.hpp
nodebuiltin_inst.o: nodebuiltinhasnext.hpp nodebuiltinnext.hpp
nodebuiltin_inst.o: nodebuiltinresetiterator.hpp nodebuiltinarray.hpp
nodebuiltin_inst.o: nodebuiltinstruct.hpp nodebuiltinsize.hpp
nodebuiltin_inst.o: nodebuiltinpushfront.hpp nodebuiltinpushback.hpp
nodebuiltin_inst.o: nodebuiltinpopfront.hpp nodebuiltinpopback.hpp
nodebuiltin_inst.o: nodebuiltinback.hpp nodebuiltinfront.hpp
nodebuiltin_inst.o: nodebuiltingraph.hpp nodebuiltinloadfromfile.hpp
nodebuiltin_inst.o: nodebuiltinvertexset.hpp nodebuiltinedgeset.hpp
nodebuiltin_inst.o: nodebuiltinisoriented.hpp nodebuiltinsetoriented.hpp
nodebuiltin_inst.o: nodebuiltininvertedgesorientation.hpp
nodebuiltin_inst.o: nodebuiltingeneratevertex.hpp nodebuiltingenerateedge.hpp
nodebuiltin_inst.o: nodebuiltindeletevertex.hpp nodebuiltindeleteedge.hpp
nodebuiltin_inst.o: nodebuiltingetnumvertices.hpp nodebuiltingetnumedges.hpp
nodebuiltin_inst.o: nodebuiltingetvertices.hpp nodebuiltingetedges.hpp
nodebuiltin_inst.o: nodebuiltingetdegree.hpp nodebuiltingetneighbors.hpp
nodebuiltin_inst.o: nodebuiltingetbeginvertex.hpp nodebuiltingetendvertex.hpp
nodebuiltin_inst.o: nodebuiltinadd.hpp nodebuiltincontains.hpp
nodebuiltin_inst.o: nodebuiltinunion.hpp nodebuiltinintersection.hpp
nodebuiltin_inst.o: nodebuiltindifference.hpp
nodebuiltinintersection.o: nodebuiltinintersection.hpp general.hpp
nodebuiltinintersection.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinintersection.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinintersection.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinintersection.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinintersection.o: callstackitem.hpp logger.hpp valuevertexset.hpp
nodebuiltinintersection.o: valueedgeset.hpp
nodebuiltininvertedgesorientation.o: nodebuiltininvertedgesorientation.hpp
nodebuiltininvertedgesorientation.o: general.hpp nodefunctionbuiltin.hpp
nodebuiltininvertedgesorientation.o: nodefunction.hpp node.hpp baseobject.hpp
nodebuiltininvertedgesorientation.o: countptr.hpp objectcreator.hpp
nodebuiltininvertedgesorientation.o: mutexlocker.hpp mutex.hpp value.hpp
nodebuiltininvertedgesorientation.o: valuenull.hpp context.hpp
nodebuiltininvertedgesorientation.o: stringtable.hpp codeposition.hpp
nodebuiltininvertedgesorientation.o: callstackitem.hpp logger.hpp
nodebuiltininvertedgesorientation.o: valuegraph.hpp
nodebuiltinisarray.o: nodebuiltinisarray.hpp general.hpp
nodebuiltinisarray.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisarray.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinisarray.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinisarray.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisarray.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltinisbool.o: nodebuiltinisbool.hpp general.hpp
nodebuiltinisbool.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisbool.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinisbool.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinisbool.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisbool.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltinisedge.o: nodebuiltinisedge.hpp general.hpp
nodebuiltinisedge.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisedge.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinisedge.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinisedge.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisedge.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltinisedgeset.o: nodebuiltinisedgeset.hpp general.hpp
nodebuiltinisedgeset.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisedgeset.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinisedgeset.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinisedgeset.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisedgeset.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltinisfloat.o: nodebuiltinisfloat.hpp general.hpp
nodebuiltinisfloat.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisfloat.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinisfloat.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinisfloat.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisfloat.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltinisgraph.o: nodebuiltinisgraph.hpp general.hpp
nodebuiltinisgraph.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisgraph.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinisgraph.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinisgraph.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisgraph.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltinisint.o: nodebuiltinisint.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinisint.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinisint.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodebuiltinisint.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinisint.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinisint.o: valuebool.hpp
nodebuiltinisnull.o: nodebuiltinisnull.hpp general.hpp
nodebuiltinisnull.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisnull.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinisnull.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinisnull.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisnull.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltinisoriented.o: nodebuiltinisoriented.hpp general.hpp
nodebuiltinisoriented.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisoriented.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinisoriented.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinisoriented.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisoriented.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltinisoriented.o: valuegraph.hpp
nodebuiltinisstring.o: nodebuiltinisstring.hpp general.hpp
nodebuiltinisstring.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisstring.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinisstring.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinisstring.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisstring.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltinisstruct.o: nodebuiltinisstruct.hpp general.hpp
nodebuiltinisstruct.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisstruct.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinisstruct.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinisstruct.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisstruct.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltinisvertex.o: nodebuiltinisvertex.hpp general.hpp
nodebuiltinisvertex.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisvertex.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinisvertex.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinisvertex.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisvertex.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltinisvertexset.o: nodebuiltinisvertexset.hpp general.hpp
nodebuiltinisvertexset.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisvertexset.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinisvertexset.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinisvertexset.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisvertexset.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltiniterator.o: nodebuiltiniterator.hpp general.hpp
nodebuiltiniterator.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltiniterator.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltiniterator.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltiniterator.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltiniterator.o: callstackitem.hpp logger.hpp
nodebuiltinloadfromfile.o: nodebuiltinloadfromfile.hpp general.hpp
nodebuiltinloadfromfile.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinloadfromfile.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinloadfromfile.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinloadfromfile.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinloadfromfile.o: callstackitem.hpp logger.hpp valuegraph.hpp
nodebuiltinloadfromfile.o: valuestring.hpp valuebool.hpp
nodebuiltinnext.o: nodebuiltinnext.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinnext.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinnext.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodebuiltinnext.o: valuenull.hpp context.hpp stringtable.hpp codeposition.hpp
nodebuiltinnext.o: callstackitem.hpp logger.hpp
nodebuiltinpopback.o: nodebuiltinpopback.hpp general.hpp
nodebuiltinpopback.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinpopback.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinpopback.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinpopback.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinpopback.o: callstackitem.hpp logger.hpp valuearray.hpp
nodebuiltinpopfront.o: nodebuiltinpopfront.hpp general.hpp
nodebuiltinpopfront.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinpopfront.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinpopfront.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinpopfront.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinpopfront.o: callstackitem.hpp logger.hpp valuearray.hpp
nodebuiltinprintstacktrace.o: nodebuiltinprintstacktrace.hpp general.hpp
nodebuiltinprintstacktrace.o: nodefunctionbuiltin.hpp nodefunction.hpp
nodebuiltinprintstacktrace.o: node.hpp baseobject.hpp countptr.hpp
nodebuiltinprintstacktrace.o: objectcreator.hpp mutexlocker.hpp mutex.hpp
nodebuiltinprintstacktrace.o: value.hpp valuenull.hpp context.hpp
nodebuiltinprintstacktrace.o: stringtable.hpp codeposition.hpp
nodebuiltinprintstacktrace.o: callstackitem.hpp logger.hpp
nodebuiltinpushback.o: nodebuiltinpushback.hpp general.hpp
nodebuiltinpushback.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinpushback.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinpushback.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinpushback.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinpushback.o: callstackitem.hpp logger.hpp valuearray.hpp
nodebuiltinpushfront.o: nodebuiltinpushfront.hpp general.hpp
nodebuiltinpushfront.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinpushfront.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinpushfront.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinpushfront.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinpushfront.o: callstackitem.hpp logger.hpp valuearray.hpp
nodebuiltinresetiterator.o: nodebuiltinresetiterator.hpp general.hpp
nodebuiltinresetiterator.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinresetiterator.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinresetiterator.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinresetiterator.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinresetiterator.o: callstackitem.hpp logger.hpp
nodebuiltinsetoriented.o: nodebuiltinsetoriented.hpp general.hpp
nodebuiltinsetoriented.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinsetoriented.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinsetoriented.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinsetoriented.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinsetoriented.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltinsetoriented.o: valueint.hpp valuegraph.hpp
nodebuiltinsize.o: nodebuiltinsize.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinsize.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinsize.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodebuiltinsize.o: valuenull.hpp context.hpp stringtable.hpp codeposition.hpp
nodebuiltinsize.o: callstackitem.hpp logger.hpp valuearray.hpp
nodebuiltinsize.o: valuestring.hpp valueint.hpp
nodebuiltinstruct.o: nodebuiltinstruct.hpp general.hpp
nodebuiltinstruct.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinstruct.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinstruct.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinstruct.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinstruct.o: callstackitem.hpp logger.hpp valuestruct.hpp
nodebuiltinunion.o: nodebuiltinunion.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinunion.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinunion.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodebuiltinunion.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinunion.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinunion.o: valuevertexset.hpp valueedgeset.hpp
nodebuiltinverify.o: nodebuiltinverify.hpp general.hpp
nodebuiltinverify.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinverify.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinverify.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinverify.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinverify.o: callstackitem.hpp logger.hpp valuebool.hpp
nodebuiltinvertexset.o: nodebuiltinvertexset.hpp general.hpp
nodebuiltinvertexset.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinvertexset.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodebuiltinvertexset.o: mutexlocker.hpp mutex.hpp value.hpp valuenull.hpp
nodebuiltinvertexset.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinvertexset.o: callstackitem.hpp logger.hpp valuevertexset.hpp
nodebuiltinvertexset.o: valuegraph.hpp
nodecondition.o: nodecondition.hpp general.hpp node.hpp baseobject.hpp
nodecondition.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
nodecondition.o: value.hpp valuenull.hpp nodeemptycommand.hpp
node.o: node.hpp general.hpp baseobject.hpp countptr.hpp objectcreator.hpp
node.o: mutexlocker.hpp mutex.hpp value.hpp
nodeemptycommand.o: nodeemptycommand.hpp general.hpp node.hpp baseobject.hpp
nodeemptycommand.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
nodeemptycommand.o: value.hpp valuenull.hpp
nodeforeach.o: nodeforeach.hpp general.hpp node.hpp baseobject.hpp
nodeforeach.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
nodeforeach.o: value.hpp context.hpp stringtable.hpp codeposition.hpp
nodeforeach.o: callstackitem.hpp nodeemptycommand.hpp nodejumpbreak.hpp
nodeforeach.o: nodejumpcontinue.hpp valuenull.hpp
nodefunctionbuiltin.o: nodefunctionbuiltin.hpp general.hpp nodefunction.hpp
nodefunctionbuiltin.o: node.hpp baseobject.hpp countptr.hpp objectcreator.hpp
nodefunctionbuiltin.o: mutexlocker.hpp mutex.hpp value.hpp context.hpp
nodefunctionbuiltin.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodefunctionbuiltin.o: logger.hpp
nodefunctioncall.o: nodefunctioncall.hpp general.hpp node.hpp baseobject.hpp
nodefunctioncall.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
nodefunctioncall.o: value.hpp codeposition.hpp nodefunction.hpp nodeblock.hpp
nodefunctioncall.o: valuenull.hpp logger.hpp context.hpp stringtable.hpp
nodefunctioncall.o: callstackitem.hpp
nodefunction.o: nodefunction.hpp general.hpp node.hpp baseobject.hpp
nodefunction.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
nodefunction.o: value.hpp context.hpp stringtable.hpp codeposition.hpp
nodefunction.o: callstackitem.hpp
nodefunctionscript.o: nodefunctionscript.hpp general.hpp nodefunction.hpp
nodefunctionscript.o: node.hpp baseobject.hpp countptr.hpp objectcreator.hpp
nodefunctionscript.o: mutexlocker.hpp mutex.hpp value.hpp codeposition.hpp
nodefunctionscript.o: nodeemptycommand.hpp nodejumpcontinue.hpp
nodefunctionscript.o: nodejumpbreak.hpp valuenull.hpp context.hpp
nodefunctionscript.o: stringtable.hpp callstackitem.hpp logger.hpp
nodeglobal.o: nodeglobal.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodeglobal.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodeglobal.o: context.hpp stringtable.hpp codeposition.hpp callstackitem.hpp
nodejumpbreak.o: nodejumpbreak.hpp general.hpp node.hpp baseobject.hpp
nodejumpbreak.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
nodejumpbreak.o: value.hpp valuenull.hpp
nodejumpcontinue.o: nodejumpcontinue.hpp general.hpp node.hpp baseobject.hpp
nodejumpcontinue.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
nodejumpcontinue.o: value.hpp valuenull.hpp
nodeloop.o: nodeloop.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodeloop.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodeloop.o: valuenull.hpp valuebool.hpp nodeemptycommand.hpp nodevalue.hpp
nodeloop.o: nodejumpbreak.hpp nodejumpcontinue.hpp
nodeposition.o: nodeposition.hpp general.hpp node.hpp baseobject.hpp
nodeposition.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
nodeposition.o: value.hpp codeposition.hpp context.hpp stringtable.hpp
nodeposition.o: callstackitem.hpp
nodeunary.o: nodeunary.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodeunary.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
nodeunarydecpost.o: valuebool.hpp general.hpp value.hpp baseobject.hpp
nodeunarydecpost.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
nodeunarydecpost.o: nodeunarydecpost.hpp nodeunary.hpp node.hpp
nodeunarydecpre.o: valuebool.hpp general.hpp value.hpp baseobject.hpp
nodeunarydecpre.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
nodeunarydecpre.o: nodeunarydecpre.hpp nodeunary.hpp node.hpp
nodeunaryincpost.o: valuebool.hpp general.hpp value.hpp baseobject.hpp
nodeunaryincpost.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
nodeunaryincpost.o: nodeunaryincpost.hpp nodeunary.hpp node.hpp
nodeunaryincpre.o: valuebool.hpp general.hpp value.hpp baseobject.hpp
nodeunaryincpre.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
nodeunaryincpre.o: nodeunaryincpre.hpp nodeunary.hpp node.hpp
nodeunarynot.o: nodeunarynot.hpp general.hpp nodeunary.hpp node.hpp
nodeunarynot.o: baseobject.hpp countptr.hpp objectcreator.hpp mutexlocker.hpp
nodeunarynot.o: mutex.hpp value.hpp
nodeunaryreturn.o: nodeunaryreturn.hpp general.hpp nodeunary.hpp node.hpp
nodeunaryreturn.o: baseobject.hpp countptr.hpp objectcreator.hpp
nodeunaryreturn.o: mutexlocker.hpp mutex.hpp value.hpp
nodeunarysub.o: nodeunarysub.hpp general.hpp nodeunary.hpp node.hpp
nodeunarysub.o: baseobject.hpp countptr.hpp objectcreator.hpp mutexlocker.hpp
nodeunarysub.o: mutex.hpp value.hpp
nodevalue.o: nodevalue.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodevalue.o: objectcreator.hpp mutexlocker.hpp mutex.hpp value.hpp
objectcreator.o: objectcreator.hpp general.hpp mutexlocker.hpp mutex.hpp
objectcreator.o: objectfactory.hpp baseobject.hpp logger.hpp context.hpp
objectcreator.o: countptr.hpp value.hpp stringtable.hpp codeposition.hpp
objectcreator.o: callstackitem.hpp
objectfactory.o: objectfactory.hpp general.hpp baseobject.hpp
parser.o: general.hpp lexan.hpp baseobject.hpp lexaniterator.hpp
parser.o: lexantokens.hpp node.hpp countptr.hpp objectcreator.hpp
parser.o: mutexlocker.hpp mutex.hpp value.hpp nodeblock.hpp
parser.o: nodefunctioncall.hpp codeposition.hpp parser.hpp context.hpp
parser.o: stringtable.hpp callstackitem.hpp nodebinaryadd.hpp nodebinary.hpp
parser.o: nodebinaryand.hpp nodebinaryass.hpp nodebinaryassadd.hpp
parser.o: nodebinaryasssub.hpp nodebinaryassmult.hpp nodebinaryassdiv.hpp
parser.o: nodebinaryassmod.hpp nodebinaryassref.hpp nodebinarydiv.hpp
parser.o: nodebinaryeq.hpp nodebinaryge.hpp nodebinarygt.hpp nodebinaryle.hpp
parser.o: nodebinarylt.hpp nodebinarymod.hpp nodebinarymult.hpp
parser.o: nodebinaryne.hpp nodebinaryor.hpp nodebinarysub.hpp
parser.o: nodebinaryindex.hpp nodebinarymember.hpp nodecondition.hpp
parser.o: nodeemptycommand.hpp nodefunctionscript.hpp nodefunction.hpp
parser.o: nodeloop.hpp nodeforeach.hpp nodeunarynot.hpp nodeunary.hpp
parser.o: nodeunaryreturn.hpp nodeunarysub.hpp nodeunaryincpre.hpp
parser.o: nodeunaryincpost.hpp nodeunarydecpre.hpp nodeunarydecpost.hpp
parser.o: nodevalue.hpp nodejumpbreak.hpp nodejumpcontinue.hpp nodeglobal.hpp
parser.o: valuebool.hpp valueedge.hpp valuestruct.hpp valuenull.hpp
parser.o: valuegraph.hpp valueedgeset.hpp valuefloat.hpp valueint.hpp
parser.o: valuestring.hpp valuevertex.hpp valuevertexset.hpp
parser.o: valueidentifier.hpp logger.hpp nodeposition.hpp
stringtable.o: stringtable.hpp general.hpp baseobject.hpp objectcreator.hpp
stringtable.o: mutexlocker.hpp mutex.hpp
tests.o: tests.hpp general.hpp baseobject.hpp logger.hpp objectcreator.hpp
tests.o: mutexlocker.hpp mutex.hpp valueint.hpp value.hpp countptr.hpp
tests.o: valuefloat.hpp valuebool.hpp valuestring.hpp valuestruct.hpp
tests.o: valuenull.hpp valuereference.hpp valueidentifier.hpp context.hpp
tests.o: stringtable.hpp codeposition.hpp callstackitem.hpp valuegraph.hpp
tests.o: valuevertex.hpp valueedgeset.hpp valueedge.hpp valuevertexset.hpp
tests.o: lexan.hpp lexaniterator.hpp lexantokens.hpp node.hpp nodeblock.hpp
tests.o: nodefunctioncall.hpp parser.hpp nodeunarysub.hpp nodeunary.hpp
tests.o: nodeunarynot.hpp nodebinaryadd.hpp nodebinary.hpp nodebinarysub.hpp
tests.o: nodecondition.hpp nodeemptycommand.hpp nodefunctionscript.hpp
tests.o: nodefunction.hpp nodebinaryass.hpp nodevalue.hpp nodebinarylt.hpp
tests.o: nodeunaryreturn.hpp nodebinarymult.hpp valuearray.hpp
valuearray.o: valuearray.hpp general.hpp value.hpp baseobject.hpp
valuearray.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
valuearray.o: valuenull.hpp valuebool.hpp valuereference.hpp valueint.hpp
valuearray.o: valuefloat.hpp logger.hpp
valuebool.o: value.hpp general.hpp baseobject.hpp countptr.hpp
valuebool.o: objectcreator.hpp mutexlocker.hpp mutex.hpp valuenull.hpp
valuebool.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuebool.o: valuestruct.hpp valuearray.hpp logger.hpp
value.o: value.hpp general.hpp baseobject.hpp countptr.hpp objectcreator.hpp
value.o: mutexlocker.hpp mutex.hpp valuenull.hpp valuebool.hpp valueint.hpp
value.o: valuefloat.hpp valuestring.hpp valuestruct.hpp valuearray.hpp
value.o: valuereference.hpp valueidentifier.hpp context.hpp stringtable.hpp
value.o: codeposition.hpp callstackitem.hpp valuegraph.hpp valuevertex.hpp
value.o: valueedgeset.hpp valueedge.hpp logger.hpp
valueedge.o: valueedge.hpp general.hpp valuestruct.hpp value.hpp
valueedge.o: baseobject.hpp countptr.hpp objectcreator.hpp mutexlocker.hpp
valueedge.o: mutex.hpp valuenull.hpp valuegraph.hpp valuebool.hpp
valueedge.o: valuevertex.hpp valueedgeset.hpp
valueedgeset.o: valueedgeset.hpp general.hpp value.hpp baseobject.hpp
valueedgeset.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
valueedgeset.o: logger.hpp valuebool.hpp valueedge.hpp valuestruct.hpp
valueedgeset.o: valuenull.hpp valuegraph.hpp
valuefloat.o: value.hpp general.hpp baseobject.hpp countptr.hpp
valuefloat.o: objectcreator.hpp mutexlocker.hpp mutex.hpp valuenull.hpp
valuefloat.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuefloat.o: valuestruct.hpp valuearray.hpp logger.hpp
valuegraph.o: valuegraph.hpp general.hpp value.hpp baseobject.hpp
valuegraph.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
valuegraph.o: logger.hpp valuebool.hpp valuevertex.hpp valueedgeset.hpp
valuegraph.o: valuestruct.hpp valuenull.hpp valueedge.hpp valuevertexset.hpp
valuegraph.o: context.hpp stringtable.hpp codeposition.hpp callstackitem.hpp
valuegraph.o: valueint.hpp valuefloat.hpp
valueidentifier.o: valueidentifier.hpp general.hpp value.hpp baseobject.hpp
valueidentifier.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
valueidentifier.o: context.hpp stringtable.hpp codeposition.hpp
valueidentifier.o: callstackitem.hpp valuenull.hpp valuebool.hpp valueint.hpp
valueidentifier.o: valuefloat.hpp valuestring.hpp valuestruct.hpp
valueidentifier.o: valuereference.hpp valuegraph.hpp valuevertex.hpp
valueidentifier.o: valueedgeset.hpp valueedge.hpp valuevertexset.hpp
valueidentifier.o: logger.hpp
valueint.o: value.hpp general.hpp baseobject.hpp countptr.hpp
valueint.o: objectcreator.hpp mutexlocker.hpp mutex.hpp valuenull.hpp
valueint.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valueint.o: valuestruct.hpp valuearray.hpp logger.hpp
valuenull.o: value.hpp general.hpp baseobject.hpp countptr.hpp
valuenull.o: objectcreator.hpp mutexlocker.hpp mutex.hpp valuenull.hpp
valuenull.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuenull.o: valuestruct.hpp
valuereference.o: valuereference.hpp general.hpp value.hpp baseobject.hpp
valuereference.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
valuereference.o: valuenull.hpp valuebool.hpp valueint.hpp valuefloat.hpp
valuereference.o: valuestring.hpp valuestruct.hpp valueidentifier.hpp
valuereference.o: context.hpp stringtable.hpp codeposition.hpp
valuereference.o: callstackitem.hpp valuegraph.hpp valuevertex.hpp
valuereference.o: valueedgeset.hpp valueedge.hpp valuevertexset.hpp
valuestring.o: value.hpp general.hpp baseobject.hpp countptr.hpp
valuestring.o: objectcreator.hpp mutexlocker.hpp mutex.hpp valuenull.hpp
valuestring.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuestring.o: valuestruct.hpp
valuestruct.o: valuestruct.hpp general.hpp value.hpp baseobject.hpp
valuestruct.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
valuestruct.o: valuenull.hpp valuebool.hpp valuereference.hpp context.hpp
valuestruct.o: stringtable.hpp codeposition.hpp callstackitem.hpp
valuevertex.o: valuevertex.hpp general.hpp value.hpp baseobject.hpp
valuevertex.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
valuevertex.o: valueedgeset.hpp valuegraph.hpp valuestruct.hpp valuenull.hpp
valuevertex.o: valuebool.hpp valueedge.hpp valuevertexset.hpp context.hpp
valuevertex.o: stringtable.hpp codeposition.hpp callstackitem.hpp
valuevertexset.o: valuevertexset.hpp general.hpp value.hpp baseobject.hpp
valuevertexset.o: countptr.hpp objectcreator.hpp mutexlocker.hpp mutex.hpp
valuevertexset.o: valuebool.hpp valuevertex.hpp valueedgeset.hpp
valuevertexset.o: valuegraph.hpp valuestruct.hpp valuenull.hpp logger.hpp
valuevertexset.o: context.hpp stringtable.hpp codeposition.hpp
valuevertexset.o: callstackitem.hpp
