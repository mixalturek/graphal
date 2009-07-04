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
callstackitem.o: callstackitem.hpp general.hpp baseobject.hpp countptr.hpp
callstackitem.o: value.hpp context.hpp stringtable.hpp codeposition.hpp
callstackitem.o: objectcreator.hpp valuenull.hpp valuereference.hpp
clifactory.o: clifactory.hpp general.hpp objectfactory.hpp baseobject.hpp
clifactory.o: clilogger.hpp logger.hpp objectcreator.hpp context.hpp
clifactory.o: countptr.hpp value.hpp stringtable.hpp codeposition.hpp
clifactory.o: callstackitem.hpp
clilogger.o: clilogger.hpp general.hpp logger.hpp baseobject.hpp
clilogger.o: objectcreator.hpp context.hpp countptr.hpp value.hpp
clilogger.o: stringtable.hpp codeposition.hpp callstackitem.hpp
codeposition.o: codeposition.hpp general.hpp baseobject.hpp context.hpp
codeposition.o: countptr.hpp value.hpp stringtable.hpp objectcreator.hpp
codeposition.o: callstackitem.hpp
context.o: context.hpp general.hpp baseobject.hpp countptr.hpp value.hpp
context.o: stringtable.hpp codeposition.hpp objectcreator.hpp
context.o: callstackitem.hpp valuenull.hpp nodefunction.hpp node.hpp
context.o: nodefunctioncall.hpp valuearray.hpp valuestring.hpp
context.o: valuereference.hpp nodevalue.hpp nodeblock.hpp logger.hpp
context.o: exitvalue.hpp
exitvalue.o: exitvalue.hpp general.hpp baseobject.hpp countptr.hpp value.hpp
init_static_objects.o: general.hpp baseobject.hpp valuenull.hpp value.hpp
init_static_objects.o: countptr.hpp valuebool.hpp objectcreator.hpp
lexan.o: lexan.hpp general.hpp baseobject.hpp lexaniterator.hpp
lexan.o: lexantokens.hpp node.hpp countptr.hpp value.hpp nodeblock.hpp
lexan.o: nodefunctioncall.hpp codeposition.hpp parser.hpp
lexan.o: lexaniteratorstring.hpp lexaniteratorfile.hpp logger.hpp
lexan.o: objectcreator.hpp context.hpp stringtable.hpp callstackitem.hpp
lexaniterator.o: lexaniterator.hpp general.hpp baseobject.hpp
lexaniteratorfile.o: lexaniteratorfile.hpp general.hpp lexaniterator.hpp
lexaniteratorfile.o: baseobject.hpp context.hpp countptr.hpp value.hpp
lexaniteratorfile.o: stringtable.hpp codeposition.hpp objectcreator.hpp
lexaniteratorfile.o: callstackitem.hpp
lexaniteratorstring.o: lexaniteratorstring.hpp general.hpp lexaniterator.hpp
lexaniteratorstring.o: baseobject.hpp context.hpp countptr.hpp value.hpp
lexaniteratorstring.o: stringtable.hpp codeposition.hpp objectcreator.hpp
lexaniteratorstring.o: callstackitem.hpp
logger.o: logger.hpp general.hpp baseobject.hpp objectcreator.hpp
main.o: general.hpp baseobject.hpp logger.hpp objectcreator.hpp tests.hpp
main.o: context.hpp countptr.hpp value.hpp stringtable.hpp codeposition.hpp
main.o: callstackitem.hpp nodebuiltin_inst.hpp version.hpp clifactory.hpp
main.o: objectfactory.hpp
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
nodebinaryassref.o: valueidentifier.hpp general.hpp value.hpp baseobject.hpp
nodebinaryassref.o: countptr.hpp context.hpp stringtable.hpp codeposition.hpp
nodebinaryassref.o: objectcreator.hpp callstackitem.hpp nodebinaryassref.hpp
nodebinaryassref.o: nodebinary.hpp node.hpp
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
nodeblock.o: value.hpp nodefunctioncall.hpp codeposition.hpp valuenull.hpp
nodebuiltinadd.o: nodebuiltinadd.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinadd.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinadd.o: value.hpp objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinadd.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinadd.o: logger.hpp valuevertexset.hpp valuevertex.hpp
nodebuiltinadd.o: valueedgeset.hpp valuegraph.hpp valuestruct.hpp
nodebuiltinadd.o: valueedge.hpp
nodebuiltinarray.o: nodebuiltinarray.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinarray.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinarray.o: value.hpp objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinarray.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinarray.o: logger.hpp valuearray.hpp valuebool.hpp valueint.hpp
nodebuiltinarray.o: valuefloat.hpp
nodebuiltinassert.o: nodebuiltinassert.hpp general.hpp
nodebuiltinassert.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinassert.o: baseobject.hpp countptr.hpp value.hpp objectcreator.hpp
nodebuiltinassert.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinassert.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinback.o: nodebuiltinback.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinback.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinback.o: value.hpp objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinback.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinback.o: logger.hpp valuearray.hpp
nodebuiltinbreakpoint.o: nodebuiltinbreakpoint.hpp general.hpp
nodebuiltinbreakpoint.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinbreakpoint.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinbreakpoint.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinbreakpoint.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinbreakpoint.o: logger.hpp valuebool.hpp
nodebuiltincontains.o: nodebuiltincontains.hpp general.hpp
nodebuiltincontains.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltincontains.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltincontains.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltincontains.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltincontains.o: logger.hpp valuegraph.hpp valuevertexset.hpp
nodebuiltincontains.o: valueedgeset.hpp valuevertex.hpp valuestruct.hpp
nodebuiltincontains.o: valueedge.hpp valuebool.hpp
nodebuiltindeleteedge.o: nodebuiltindeleteedge.hpp general.hpp
nodebuiltindeleteedge.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltindeleteedge.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltindeleteedge.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltindeleteedge.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltindeleteedge.o: logger.hpp valuegraph.hpp valueedge.hpp
nodebuiltindeleteedge.o: valuestruct.hpp valueedgeset.hpp
nodebuiltindeletevertex.o: nodebuiltindeletevertex.hpp general.hpp
nodebuiltindeletevertex.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltindeletevertex.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltindeletevertex.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltindeletevertex.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltindeletevertex.o: logger.hpp valuegraph.hpp valuevertex.hpp
nodebuiltindeletevertex.o: valueedgeset.hpp valuestruct.hpp
nodebuiltindeletevertex.o: valuevertexset.hpp
nodebuiltindifference.o: nodebuiltindifference.hpp general.hpp
nodebuiltindifference.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltindifference.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltindifference.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltindifference.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltindifference.o: logger.hpp valuevertexset.hpp valueedgeset.hpp
nodebuiltindump.o: nodebuiltindump.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltindump.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltindump.o: value.hpp objectcreator.hpp valuenull.hpp context.hpp
nodebuiltindump.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltindump.o: logger.hpp
nodebuiltinedgeset.o: nodebuiltinedgeset.hpp general.hpp
nodebuiltinedgeset.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinedgeset.o: baseobject.hpp countptr.hpp value.hpp objectcreator.hpp
nodebuiltinedgeset.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinedgeset.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinedgeset.o: valueedgeset.hpp valuegraph.hpp
nodebuiltinecho.o: nodebuiltinecho.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinecho.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinecho.o: value.hpp objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinecho.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinecho.o: logger.hpp
nodebuiltinexit.o: nodebuiltinexit.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinexit.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinexit.o: value.hpp objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinexit.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinexit.o: logger.hpp exitvalue.hpp
nodebuiltinfront.o: nodebuiltinfront.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinfront.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinfront.o: value.hpp objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinfront.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinfront.o: logger.hpp valuearray.hpp
nodebuiltingenerateedge.o: nodebuiltingenerateedge.hpp general.hpp
nodebuiltingenerateedge.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingenerateedge.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltingenerateedge.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltingenerateedge.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltingenerateedge.o: logger.hpp valuegraph.hpp valuevertex.hpp
nodebuiltingenerateedge.o: valueedgeset.hpp valuestruct.hpp valueedge.hpp
nodebuiltingeneratevertex.o: nodebuiltingeneratevertex.hpp general.hpp
nodebuiltingeneratevertex.o: nodefunctionbuiltin.hpp nodefunction.hpp
nodebuiltingeneratevertex.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodebuiltingeneratevertex.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltingeneratevertex.o: stringtable.hpp codeposition.hpp
nodebuiltingeneratevertex.o: callstackitem.hpp logger.hpp valuegraph.hpp
nodebuiltingeneratevertex.o: valuevertex.hpp valueedgeset.hpp valuestruct.hpp
nodebuiltingetbeginvertex.o: nodebuiltingetbeginvertex.hpp general.hpp
nodebuiltingetbeginvertex.o: nodefunctionbuiltin.hpp nodefunction.hpp
nodebuiltingetbeginvertex.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodebuiltingetbeginvertex.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltingetbeginvertex.o: stringtable.hpp codeposition.hpp
nodebuiltingetbeginvertex.o: callstackitem.hpp logger.hpp valueedge.hpp
nodebuiltingetbeginvertex.o: valuestruct.hpp valuegraph.hpp valuevertex.hpp
nodebuiltingetbeginvertex.o: valueedgeset.hpp
nodebuiltingetdegree.o: nodebuiltingetdegree.hpp general.hpp
nodebuiltingetdegree.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetdegree.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltingetdegree.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltingetdegree.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltingetdegree.o: logger.hpp valuevertex.hpp valueedgeset.hpp
nodebuiltingetdegree.o: valuegraph.hpp valuestruct.hpp valueint.hpp
nodebuiltingetedges.o: nodebuiltingetedges.hpp general.hpp
nodebuiltingetedges.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetedges.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltingetedges.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltingetedges.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltingetedges.o: logger.hpp valuegraph.hpp
nodebuiltingetendvertex.o: nodebuiltingetendvertex.hpp general.hpp
nodebuiltingetendvertex.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetendvertex.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltingetendvertex.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltingetendvertex.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltingetendvertex.o: logger.hpp valueedge.hpp valuestruct.hpp
nodebuiltingetendvertex.o: valuegraph.hpp valuevertex.hpp valueedgeset.hpp
nodebuiltingetneighbors.o: nodebuiltingetneighbors.hpp general.hpp
nodebuiltingetneighbors.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetneighbors.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltingetneighbors.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltingetneighbors.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltingetneighbors.o: logger.hpp valuevertex.hpp valueedgeset.hpp
nodebuiltingetneighbors.o: valuegraph.hpp valuestruct.hpp valuevertexset.hpp
nodebuiltingetnumedges.o: nodebuiltingetnumedges.hpp general.hpp
nodebuiltingetnumedges.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetnumedges.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltingetnumedges.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltingetnumedges.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltingetnumedges.o: logger.hpp valuegraph.hpp valueedgeset.hpp
nodebuiltingetnumedges.o: valueint.hpp
nodebuiltingetnumvertices.o: nodebuiltingetnumvertices.hpp general.hpp
nodebuiltingetnumvertices.o: nodefunctionbuiltin.hpp nodefunction.hpp
nodebuiltingetnumvertices.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodebuiltingetnumvertices.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltingetnumvertices.o: stringtable.hpp codeposition.hpp
nodebuiltingetnumvertices.o: callstackitem.hpp logger.hpp valuegraph.hpp
nodebuiltingetnumvertices.o: valuevertexset.hpp valueint.hpp
nodebuiltingetvertices.o: nodebuiltingetvertices.hpp general.hpp
nodebuiltingetvertices.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetvertices.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltingetvertices.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltingetvertices.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltingetvertices.o: logger.hpp valuegraph.hpp
nodebuiltingraph.o: nodebuiltingraph.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltingraph.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltingraph.o: value.hpp objectcreator.hpp valuenull.hpp context.hpp
nodebuiltingraph.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltingraph.o: logger.hpp valuegraph.hpp
nodebuiltinhasnext.o: nodebuiltinhasnext.hpp general.hpp
nodebuiltinhasnext.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinhasnext.o: baseobject.hpp countptr.hpp value.hpp objectcreator.hpp
nodebuiltinhasnext.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinhasnext.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltin_inst.o: general.hpp context.hpp baseobject.hpp countptr.hpp
nodebuiltin_inst.o: value.hpp stringtable.hpp codeposition.hpp
nodebuiltin_inst.o: objectcreator.hpp callstackitem.hpp nodebuiltinecho.hpp
nodebuiltin_inst.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltin_inst.o: nodebuiltindump.hpp nodebuiltinexit.hpp
nodebuiltin_inst.o: nodebuiltinassert.hpp nodebuiltinverify.hpp
nodebuiltin_inst.o: nodebuiltinbreakpoint.hpp nodebuiltinisnull.hpp
nodebuiltin_inst.o: nodebuiltinisbool.hpp nodebuiltinisint.hpp
nodebuiltin_inst.o: nodebuiltinisfloat.hpp nodebuiltinisstring.hpp
nodebuiltin_inst.o: nodebuiltinisstruct.hpp nodebuiltinisarray.hpp
nodebuiltin_inst.o: nodebuiltinisgraph.hpp nodebuiltinisvertex.hpp
nodebuiltin_inst.o: nodebuiltinisedge.hpp nodebuiltinisvertexset.hpp
nodebuiltin_inst.o: nodebuiltinisedgeset.hpp nodebuiltinprintstacktrace.hpp
nodebuiltin_inst.o: nodebuiltiniterator.hpp nodebuiltinhasnext.hpp
nodebuiltin_inst.o: nodebuiltinnext.hpp nodebuiltinresetiterator.hpp
nodebuiltin_inst.o: nodebuiltinarray.hpp nodebuiltinstruct.hpp
nodebuiltin_inst.o: nodebuiltinsize.hpp nodebuiltinpushfront.hpp
nodebuiltin_inst.o: nodebuiltinpushback.hpp nodebuiltinpopfront.hpp
nodebuiltin_inst.o: nodebuiltinpopback.hpp nodebuiltinback.hpp
nodebuiltin_inst.o: nodebuiltinfront.hpp nodebuiltingraph.hpp
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
nodebuiltinintersection.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinintersection.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinintersection.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinintersection.o: logger.hpp valuevertexset.hpp valueedgeset.hpp
nodebuiltininvertedgesorientation.o: nodebuiltininvertedgesorientation.hpp
nodebuiltininvertedgesorientation.o: general.hpp nodefunctionbuiltin.hpp
nodebuiltininvertedgesorientation.o: nodefunction.hpp node.hpp baseobject.hpp
nodebuiltininvertedgesorientation.o: countptr.hpp value.hpp objectcreator.hpp
nodebuiltininvertedgesorientation.o: valuenull.hpp context.hpp
nodebuiltininvertedgesorientation.o: stringtable.hpp codeposition.hpp
nodebuiltininvertedgesorientation.o: callstackitem.hpp logger.hpp
nodebuiltininvertedgesorientation.o: valuegraph.hpp
nodebuiltinisarray.o: nodebuiltinisarray.hpp general.hpp
nodebuiltinisarray.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisarray.o: baseobject.hpp countptr.hpp value.hpp objectcreator.hpp
nodebuiltinisarray.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinisarray.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinisarray.o: valuebool.hpp
nodebuiltinisbool.o: nodebuiltinisbool.hpp general.hpp
nodebuiltinisbool.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisbool.o: baseobject.hpp countptr.hpp value.hpp objectcreator.hpp
nodebuiltinisbool.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinisbool.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinisbool.o: valuebool.hpp
nodebuiltinisedge.o: nodebuiltinisedge.hpp general.hpp
nodebuiltinisedge.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisedge.o: baseobject.hpp countptr.hpp value.hpp objectcreator.hpp
nodebuiltinisedge.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinisedge.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinisedge.o: valuebool.hpp
nodebuiltinisedgeset.o: nodebuiltinisedgeset.hpp general.hpp
nodebuiltinisedgeset.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisedgeset.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinisedgeset.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinisedgeset.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinisedgeset.o: logger.hpp valuebool.hpp
nodebuiltinisfloat.o: nodebuiltinisfloat.hpp general.hpp
nodebuiltinisfloat.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisfloat.o: baseobject.hpp countptr.hpp value.hpp objectcreator.hpp
nodebuiltinisfloat.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinisfloat.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinisfloat.o: valuebool.hpp
nodebuiltinisgraph.o: nodebuiltinisgraph.hpp general.hpp
nodebuiltinisgraph.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisgraph.o: baseobject.hpp countptr.hpp value.hpp objectcreator.hpp
nodebuiltinisgraph.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinisgraph.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinisgraph.o: valuebool.hpp
nodebuiltinisint.o: nodebuiltinisint.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinisint.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinisint.o: value.hpp objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinisint.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinisint.o: logger.hpp valuebool.hpp
nodebuiltinisnull.o: nodebuiltinisnull.hpp general.hpp
nodebuiltinisnull.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisnull.o: baseobject.hpp countptr.hpp value.hpp objectcreator.hpp
nodebuiltinisnull.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinisnull.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinisnull.o: valuebool.hpp
nodebuiltinisoriented.o: nodebuiltinisoriented.hpp general.hpp
nodebuiltinisoriented.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisoriented.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinisoriented.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinisoriented.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinisoriented.o: logger.hpp valuebool.hpp valuegraph.hpp
nodebuiltinisstring.o: nodebuiltinisstring.hpp general.hpp
nodebuiltinisstring.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisstring.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinisstring.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinisstring.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinisstring.o: logger.hpp valuebool.hpp
nodebuiltinisstruct.o: nodebuiltinisstruct.hpp general.hpp
nodebuiltinisstruct.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisstruct.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinisstruct.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinisstruct.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinisstruct.o: logger.hpp valuebool.hpp
nodebuiltinisvertex.o: nodebuiltinisvertex.hpp general.hpp
nodebuiltinisvertex.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisvertex.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinisvertex.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinisvertex.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinisvertex.o: logger.hpp valuebool.hpp
nodebuiltinisvertexset.o: nodebuiltinisvertexset.hpp general.hpp
nodebuiltinisvertexset.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisvertexset.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinisvertexset.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinisvertexset.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinisvertexset.o: logger.hpp valuebool.hpp
nodebuiltiniterator.o: nodebuiltiniterator.hpp general.hpp
nodebuiltiniterator.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltiniterator.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltiniterator.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltiniterator.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltiniterator.o: logger.hpp
nodebuiltinnext.o: nodebuiltinnext.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinnext.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinnext.o: value.hpp objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinnext.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinnext.o: logger.hpp
nodebuiltinpopback.o: nodebuiltinpopback.hpp general.hpp
nodebuiltinpopback.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinpopback.o: baseobject.hpp countptr.hpp value.hpp objectcreator.hpp
nodebuiltinpopback.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinpopback.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinpopback.o: valuearray.hpp
nodebuiltinpopfront.o: nodebuiltinpopfront.hpp general.hpp
nodebuiltinpopfront.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinpopfront.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinpopfront.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinpopfront.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinpopfront.o: logger.hpp valuearray.hpp
nodebuiltinprintstacktrace.o: nodebuiltinprintstacktrace.hpp general.hpp
nodebuiltinprintstacktrace.o: nodefunctionbuiltin.hpp nodefunction.hpp
nodebuiltinprintstacktrace.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodebuiltinprintstacktrace.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinprintstacktrace.o: stringtable.hpp codeposition.hpp
nodebuiltinprintstacktrace.o: callstackitem.hpp logger.hpp
nodebuiltinpushback.o: nodebuiltinpushback.hpp general.hpp
nodebuiltinpushback.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinpushback.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinpushback.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinpushback.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinpushback.o: logger.hpp valuearray.hpp
nodebuiltinpushfront.o: nodebuiltinpushfront.hpp general.hpp
nodebuiltinpushfront.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinpushfront.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinpushfront.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinpushfront.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinpushfront.o: logger.hpp valuearray.hpp
nodebuiltinresetiterator.o: nodebuiltinresetiterator.hpp general.hpp
nodebuiltinresetiterator.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinresetiterator.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinresetiterator.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinresetiterator.o: stringtable.hpp codeposition.hpp
nodebuiltinresetiterator.o: callstackitem.hpp logger.hpp
nodebuiltinsetoriented.o: nodebuiltinsetoriented.hpp general.hpp
nodebuiltinsetoriented.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinsetoriented.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinsetoriented.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinsetoriented.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinsetoriented.o: logger.hpp valuebool.hpp valueint.hpp
nodebuiltinsetoriented.o: valuegraph.hpp
nodebuiltinsize.o: nodebuiltinsize.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinsize.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinsize.o: value.hpp objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinsize.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinsize.o: logger.hpp valuearray.hpp valuestring.hpp valueint.hpp
nodebuiltinstruct.o: nodebuiltinstruct.hpp general.hpp
nodebuiltinstruct.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinstruct.o: baseobject.hpp countptr.hpp value.hpp objectcreator.hpp
nodebuiltinstruct.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinstruct.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinstruct.o: valuestruct.hpp
nodebuiltinunion.o: nodebuiltinunion.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinunion.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinunion.o: value.hpp objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinunion.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinunion.o: logger.hpp valuevertexset.hpp valueedgeset.hpp
nodebuiltinverify.o: nodebuiltinverify.hpp general.hpp
nodebuiltinverify.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinverify.o: baseobject.hpp countptr.hpp value.hpp objectcreator.hpp
nodebuiltinverify.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinverify.o: codeposition.hpp callstackitem.hpp logger.hpp
nodebuiltinverify.o: valuebool.hpp
nodebuiltinvertexset.o: nodebuiltinvertexset.hpp general.hpp
nodebuiltinvertexset.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinvertexset.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinvertexset.o: objectcreator.hpp valuenull.hpp context.hpp
nodebuiltinvertexset.o: stringtable.hpp codeposition.hpp callstackitem.hpp
nodebuiltinvertexset.o: logger.hpp valuevertexset.hpp valuegraph.hpp
nodecondition.o: nodecondition.hpp general.hpp node.hpp baseobject.hpp
nodecondition.o: countptr.hpp value.hpp valuenull.hpp nodeemptycommand.hpp
node.o: node.hpp general.hpp baseobject.hpp countptr.hpp value.hpp
nodeemptycommand.o: nodeemptycommand.hpp general.hpp node.hpp baseobject.hpp
nodeemptycommand.o: countptr.hpp value.hpp valuenull.hpp
nodeforeach.o: nodeforeach.hpp general.hpp node.hpp baseobject.hpp
nodeforeach.o: countptr.hpp value.hpp context.hpp stringtable.hpp
nodeforeach.o: codeposition.hpp objectcreator.hpp callstackitem.hpp
nodeforeach.o: nodeemptycommand.hpp nodejumpbreak.hpp nodejumpcontinue.hpp
nodeforeach.o: valuenull.hpp
nodefunctionbuiltin.o: nodefunctionbuiltin.hpp general.hpp nodefunction.hpp
nodefunctionbuiltin.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodefunctionbuiltin.o: objectcreator.hpp context.hpp stringtable.hpp
nodefunctionbuiltin.o: codeposition.hpp callstackitem.hpp logger.hpp
nodefunctioncall.o: nodefunctioncall.hpp general.hpp node.hpp baseobject.hpp
nodefunctioncall.o: countptr.hpp value.hpp codeposition.hpp nodefunction.hpp
nodefunctioncall.o: nodeblock.hpp valuenull.hpp logger.hpp objectcreator.hpp
nodefunctioncall.o: context.hpp stringtable.hpp callstackitem.hpp
nodefunction.o: nodefunction.hpp general.hpp node.hpp baseobject.hpp
nodefunction.o: countptr.hpp value.hpp context.hpp stringtable.hpp
nodefunction.o: codeposition.hpp objectcreator.hpp callstackitem.hpp
nodefunctionscript.o: nodefunctionscript.hpp general.hpp nodefunction.hpp
nodefunctionscript.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodefunctionscript.o: codeposition.hpp nodeemptycommand.hpp
nodefunctionscript.o: nodejumpcontinue.hpp nodejumpbreak.hpp valuenull.hpp
nodefunctionscript.o: context.hpp stringtable.hpp objectcreator.hpp
nodefunctionscript.o: callstackitem.hpp logger.hpp
nodeglobal.o: nodeglobal.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodeglobal.o: value.hpp context.hpp stringtable.hpp codeposition.hpp
nodeglobal.o: objectcreator.hpp callstackitem.hpp
nodejumpbreak.o: nodejumpbreak.hpp general.hpp node.hpp baseobject.hpp
nodejumpbreak.o: countptr.hpp value.hpp valuenull.hpp
nodejumpcontinue.o: nodejumpcontinue.hpp general.hpp node.hpp baseobject.hpp
nodejumpcontinue.o: countptr.hpp value.hpp valuenull.hpp
nodeloop.o: nodeloop.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodeloop.o: value.hpp valuenull.hpp valuebool.hpp nodeemptycommand.hpp
nodeloop.o: nodevalue.hpp nodejumpbreak.hpp nodejumpcontinue.hpp
nodeposition.o: nodeposition.hpp general.hpp node.hpp baseobject.hpp
nodeposition.o: countptr.hpp value.hpp codeposition.hpp context.hpp
nodeposition.o: stringtable.hpp objectcreator.hpp callstackitem.hpp
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
objectcreator.o: objectcreator.hpp general.hpp objectfactory.hpp
objectcreator.o: baseobject.hpp logger.hpp context.hpp countptr.hpp value.hpp
objectcreator.o: stringtable.hpp codeposition.hpp callstackitem.hpp
objectfactory.o: objectfactory.hpp general.hpp baseobject.hpp
parser.o: general.hpp lexan.hpp baseobject.hpp lexaniterator.hpp
parser.o: lexantokens.hpp node.hpp countptr.hpp value.hpp nodeblock.hpp
parser.o: nodefunctioncall.hpp codeposition.hpp parser.hpp context.hpp
parser.o: stringtable.hpp objectcreator.hpp callstackitem.hpp
parser.o: nodebinaryadd.hpp nodebinary.hpp nodebinaryand.hpp
parser.o: nodebinaryass.hpp nodebinaryassadd.hpp nodebinaryasssub.hpp
parser.o: nodebinaryassmult.hpp nodebinaryassdiv.hpp nodebinaryassmod.hpp
parser.o: nodebinaryassref.hpp nodebinarydiv.hpp nodebinaryeq.hpp
parser.o: nodebinaryge.hpp nodebinarygt.hpp nodebinaryle.hpp nodebinarylt.hpp
parser.o: nodebinarymod.hpp nodebinarymult.hpp nodebinaryne.hpp
parser.o: nodebinaryor.hpp nodebinarysub.hpp nodebinaryindex.hpp
parser.o: nodebinarymember.hpp nodecondition.hpp nodeemptycommand.hpp
parser.o: nodefunctionscript.hpp nodefunction.hpp nodeloop.hpp
parser.o: nodeforeach.hpp nodeunarynot.hpp nodeunary.hpp nodeunaryreturn.hpp
parser.o: nodeunarysub.hpp nodeunaryincpre.hpp nodeunaryincpost.hpp
parser.o: nodeunarydecpre.hpp nodeunarydecpost.hpp nodevalue.hpp
parser.o: nodejumpbreak.hpp nodejumpcontinue.hpp nodeglobal.hpp valuebool.hpp
parser.o: valueedge.hpp valuestruct.hpp valuenull.hpp valuegraph.hpp
parser.o: valueedgeset.hpp valuefloat.hpp valueint.hpp valuestring.hpp
parser.o: valuevertex.hpp valuevertexset.hpp valueidentifier.hpp logger.hpp
parser.o: nodeposition.hpp
stringtable.o: stringtable.hpp general.hpp baseobject.hpp
tests.o: tests.hpp general.hpp baseobject.hpp logger.hpp objectcreator.hpp
tests.o: valueint.hpp value.hpp countptr.hpp valuefloat.hpp valuebool.hpp
tests.o: valuestring.hpp valuestruct.hpp valuenull.hpp valuereference.hpp
tests.o: valueidentifier.hpp context.hpp stringtable.hpp codeposition.hpp
tests.o: callstackitem.hpp valuegraph.hpp valuevertex.hpp valueedgeset.hpp
tests.o: valueedge.hpp valuevertexset.hpp lexan.hpp lexaniterator.hpp
tests.o: lexantokens.hpp node.hpp nodeblock.hpp nodefunctioncall.hpp
tests.o: parser.hpp nodeunarysub.hpp nodeunary.hpp nodeunarynot.hpp
tests.o: nodebinaryadd.hpp nodebinary.hpp nodebinarysub.hpp nodecondition.hpp
tests.o: nodeemptycommand.hpp nodefunctionscript.hpp nodefunction.hpp
tests.o: nodebinaryass.hpp nodevalue.hpp nodebinarylt.hpp nodeunaryreturn.hpp
tests.o: nodebinarymult.hpp valuearray.hpp
valuearray.o: valuearray.hpp general.hpp value.hpp baseobject.hpp
valuearray.o: countptr.hpp valuenull.hpp valuebool.hpp valuereference.hpp
valuearray.o: valueint.hpp valuefloat.hpp logger.hpp objectcreator.hpp
valuebool.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuebool.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuebool.o: valuestruct.hpp valuearray.hpp logger.hpp objectcreator.hpp
value.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
value.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
value.o: valuestruct.hpp valuearray.hpp valuereference.hpp
value.o: valueidentifier.hpp context.hpp stringtable.hpp codeposition.hpp
value.o: objectcreator.hpp callstackitem.hpp valuegraph.hpp valuevertex.hpp
value.o: valueedgeset.hpp valueedge.hpp logger.hpp
valueedge.o: valueedge.hpp general.hpp valuestruct.hpp value.hpp
valueedge.o: baseobject.hpp countptr.hpp valuenull.hpp valuegraph.hpp
valueedge.o: valuebool.hpp valuevertex.hpp valueedgeset.hpp
valueedgeset.o: valueedgeset.hpp general.hpp value.hpp baseobject.hpp
valueedgeset.o: countptr.hpp logger.hpp objectcreator.hpp valuebool.hpp
valueedgeset.o: valueedge.hpp valuestruct.hpp valuenull.hpp valuegraph.hpp
valuefloat.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuefloat.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuefloat.o: valuestruct.hpp valuearray.hpp logger.hpp objectcreator.hpp
valuegraph.o: valuegraph.hpp general.hpp value.hpp baseobject.hpp
valuegraph.o: countptr.hpp logger.hpp objectcreator.hpp valuebool.hpp
valuegraph.o: valuevertex.hpp valueedgeset.hpp valuestruct.hpp valuenull.hpp
valuegraph.o: valueedge.hpp valuevertexset.hpp
valueidentifier.o: valueidentifier.hpp general.hpp value.hpp baseobject.hpp
valueidentifier.o: countptr.hpp context.hpp stringtable.hpp codeposition.hpp
valueidentifier.o: objectcreator.hpp callstackitem.hpp valuenull.hpp
valueidentifier.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valueidentifier.o: valuestruct.hpp valuereference.hpp valuegraph.hpp
valueidentifier.o: valuevertex.hpp valueedgeset.hpp valueedge.hpp
valueidentifier.o: valuevertexset.hpp logger.hpp
valueint.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valueint.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valueint.o: valuestruct.hpp valuearray.hpp logger.hpp objectcreator.hpp
valuenull.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuenull.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuenull.o: valuestruct.hpp
valuereference.o: valuereference.hpp general.hpp value.hpp baseobject.hpp
valuereference.o: countptr.hpp valuenull.hpp valuebool.hpp valueint.hpp
valuereference.o: valuefloat.hpp valuestring.hpp valuestruct.hpp
valuereference.o: valueidentifier.hpp context.hpp stringtable.hpp
valuereference.o: codeposition.hpp objectcreator.hpp callstackitem.hpp
valuereference.o: valuegraph.hpp valuevertex.hpp valueedgeset.hpp
valuereference.o: valueedge.hpp valuevertexset.hpp
valuestring.o: value.hpp general.hpp baseobject.hpp countptr.hpp
valuestring.o: valuenull.hpp valuebool.hpp valueint.hpp valuefloat.hpp
valuestring.o: valuestring.hpp valuestruct.hpp
valuestruct.o: valuestruct.hpp general.hpp value.hpp baseobject.hpp
valuestruct.o: countptr.hpp valuenull.hpp valuebool.hpp valuereference.hpp
valuestruct.o: context.hpp stringtable.hpp codeposition.hpp objectcreator.hpp
valuestruct.o: callstackitem.hpp
valuevertex.o: valuevertex.hpp general.hpp value.hpp baseobject.hpp
valuevertex.o: countptr.hpp valueedgeset.hpp valuegraph.hpp valuestruct.hpp
valuevertex.o: valuenull.hpp valuebool.hpp valueedge.hpp valuevertexset.hpp
valuevertexset.o: valuevertexset.hpp general.hpp value.hpp baseobject.hpp
valuevertexset.o: countptr.hpp valuebool.hpp valuevertex.hpp valueedgeset.hpp
valuevertexset.o: valuegraph.hpp valuestruct.hpp valuenull.hpp logger.hpp
valuevertexset.o: objectcreator.hpp
