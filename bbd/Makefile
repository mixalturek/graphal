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
	echo '#define SVN_VERSION' $(shell svnversion | tr 'A-Z' ' ') > version.hpp

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

listbuiltin:
	grep '\$funcdecl =' gen_builtin.pl | sed "s/.*'\(.*\)'.*/\1/"

# DO NOT DELETE

baseobject.o: baseobject.hpp general.hpp logger.hpp context.hpp countptr.hpp
baseobject.o: value.hpp stringtable.hpp codeposition.hpp
codeposition.o: codeposition.hpp general.hpp baseobject.hpp context.hpp
codeposition.o: countptr.hpp value.hpp stringtable.hpp
context.o: context.hpp general.hpp baseobject.hpp countptr.hpp value.hpp
context.o: stringtable.hpp codeposition.hpp valuenull.hpp nodefunction.hpp
context.o: node.hpp nodefunctioncall.hpp valuearray.hpp valuestring.hpp
context.o: valuereference.hpp nodevalue.hpp nodeblock.hpp logger.hpp
context.o: exitvalue.hpp
exitvalue.o: exitvalue.hpp general.hpp baseobject.hpp countptr.hpp value.hpp
init_static_objects.o: general.hpp baseobject.hpp logger.hpp context.hpp
init_static_objects.o: countptr.hpp value.hpp stringtable.hpp
init_static_objects.o: codeposition.hpp valuenull.hpp valuebool.hpp
lexan.o: lexan.hpp general.hpp baseobject.hpp lexaniterator.hpp
lexan.o: lexantokens.hpp node.hpp countptr.hpp value.hpp nodeblock.hpp
lexan.o: nodefunctioncall.hpp codeposition.hpp parser.hpp
lexan.o: lexaniteratorstring.hpp lexaniteratorfile.hpp logger.hpp context.hpp
lexan.o: stringtable.hpp
lexaniterator.o: lexaniterator.hpp general.hpp baseobject.hpp
lexaniteratorfile.o: lexaniteratorfile.hpp general.hpp lexaniterator.hpp
lexaniteratorfile.o: baseobject.hpp context.hpp countptr.hpp value.hpp
lexaniteratorfile.o: stringtable.hpp codeposition.hpp
lexaniteratorstring.o: lexaniteratorstring.hpp general.hpp lexaniterator.hpp
lexaniteratorstring.o: baseobject.hpp context.hpp countptr.hpp value.hpp
lexaniteratorstring.o: stringtable.hpp codeposition.hpp
logger.o: logger.hpp general.hpp baseobject.hpp context.hpp countptr.hpp
logger.o: value.hpp stringtable.hpp codeposition.hpp
main.o: general.hpp baseobject.hpp logger.hpp context.hpp countptr.hpp
main.o: value.hpp stringtable.hpp codeposition.hpp tests.hpp
main.o: nodebuiltin_inst.hpp version.hpp
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
nodebinaryassref.o: nodebinaryassref.hpp nodebinary.hpp node.hpp
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
nodebuiltinadd.o: value.hpp valuenull.hpp context.hpp stringtable.hpp
nodebuiltinadd.o: codeposition.hpp logger.hpp valuevertexset.hpp
nodebuiltinadd.o: valuevertex.hpp valueedgeset.hpp valuegraph.hpp
nodebuiltinadd.o: valuestruct.hpp valueedge.hpp
nodebuiltinarray.o: nodebuiltinarray.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinarray.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinarray.o: value.hpp valuenull.hpp context.hpp stringtable.hpp
nodebuiltinarray.o: codeposition.hpp logger.hpp valuearray.hpp valuebool.hpp
nodebuiltinarray.o: valueint.hpp valuefloat.hpp
nodebuiltinassert.o: nodebuiltinassert.hpp general.hpp
nodebuiltinassert.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinassert.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinassert.o: context.hpp stringtable.hpp codeposition.hpp logger.hpp
nodebuiltinback.o: nodebuiltinback.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinback.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinback.o: value.hpp valuenull.hpp context.hpp stringtable.hpp
nodebuiltinback.o: codeposition.hpp logger.hpp valuearray.hpp
nodebuiltinbreakpoint.o: nodebuiltinbreakpoint.hpp general.hpp
nodebuiltinbreakpoint.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinbreakpoint.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinbreakpoint.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinbreakpoint.o: logger.hpp valuebool.hpp
nodebuiltincontains.o: nodebuiltincontains.hpp general.hpp
nodebuiltincontains.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltincontains.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltincontains.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltincontains.o: logger.hpp valuegraph.hpp valuevertexset.hpp
nodebuiltincontains.o: valueedgeset.hpp valuevertex.hpp valuestruct.hpp
nodebuiltincontains.o: valueedge.hpp valuebool.hpp
nodebuiltindeleteedge.o: nodebuiltindeleteedge.hpp general.hpp
nodebuiltindeleteedge.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltindeleteedge.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltindeleteedge.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltindeleteedge.o: logger.hpp valuegraph.hpp valueedge.hpp
nodebuiltindeleteedge.o: valuestruct.hpp valueedgeset.hpp
nodebuiltindeletevertex.o: nodebuiltindeletevertex.hpp general.hpp
nodebuiltindeletevertex.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltindeletevertex.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltindeletevertex.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltindeletevertex.o: codeposition.hpp logger.hpp valuegraph.hpp
nodebuiltindeletevertex.o: valuevertex.hpp valueedgeset.hpp valuestruct.hpp
nodebuiltindeletevertex.o: valuevertexset.hpp
nodebuiltindifference.o: nodebuiltindifference.hpp general.hpp
nodebuiltindifference.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltindifference.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltindifference.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltindifference.o: logger.hpp valuevertexset.hpp valueedgeset.hpp
nodebuiltindump.o: nodebuiltindump.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltindump.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltindump.o: value.hpp valuenull.hpp context.hpp stringtable.hpp
nodebuiltindump.o: codeposition.hpp logger.hpp
nodebuiltinedgeset.o: nodebuiltinedgeset.hpp general.hpp
nodebuiltinedgeset.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinedgeset.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinedgeset.o: context.hpp stringtable.hpp codeposition.hpp logger.hpp
nodebuiltinedgeset.o: valueedgeset.hpp valuegraph.hpp
nodebuiltinecho.o: nodebuiltinecho.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinecho.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinecho.o: value.hpp valuenull.hpp context.hpp stringtable.hpp
nodebuiltinecho.o: codeposition.hpp logger.hpp
nodebuiltinexit.o: nodebuiltinexit.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinexit.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinexit.o: value.hpp valuenull.hpp context.hpp stringtable.hpp
nodebuiltinexit.o: codeposition.hpp logger.hpp exitvalue.hpp
nodebuiltinfront.o: nodebuiltinfront.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinfront.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinfront.o: value.hpp valuenull.hpp context.hpp stringtable.hpp
nodebuiltinfront.o: codeposition.hpp logger.hpp valuearray.hpp
nodebuiltingenerateedge.o: nodebuiltingenerateedge.hpp general.hpp
nodebuiltingenerateedge.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingenerateedge.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltingenerateedge.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltingenerateedge.o: codeposition.hpp logger.hpp valuegraph.hpp
nodebuiltingenerateedge.o: valuevertex.hpp valueedgeset.hpp valuestruct.hpp
nodebuiltingenerateedge.o: valueedge.hpp
nodebuiltingeneratevertex.o: nodebuiltingeneratevertex.hpp general.hpp
nodebuiltingeneratevertex.o: nodefunctionbuiltin.hpp nodefunction.hpp
nodebuiltingeneratevertex.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodebuiltingeneratevertex.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltingeneratevertex.o: codeposition.hpp logger.hpp valuegraph.hpp
nodebuiltingeneratevertex.o: valuevertex.hpp valueedgeset.hpp valuestruct.hpp
nodebuiltingetbeginvertex.o: nodebuiltingetbeginvertex.hpp general.hpp
nodebuiltingetbeginvertex.o: nodefunctionbuiltin.hpp nodefunction.hpp
nodebuiltingetbeginvertex.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodebuiltingetbeginvertex.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltingetbeginvertex.o: codeposition.hpp logger.hpp valueedge.hpp
nodebuiltingetbeginvertex.o: valuestruct.hpp valuegraph.hpp valuevertex.hpp
nodebuiltingetbeginvertex.o: valueedgeset.hpp
nodebuiltingetdegree.o: nodebuiltingetdegree.hpp general.hpp
nodebuiltingetdegree.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetdegree.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltingetdegree.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltingetdegree.o: logger.hpp valuevertex.hpp valueedgeset.hpp
nodebuiltingetdegree.o: valuegraph.hpp valuestruct.hpp valueint.hpp
nodebuiltingetedges.o: nodebuiltingetedges.hpp general.hpp
nodebuiltingetedges.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetedges.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltingetedges.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltingetedges.o: logger.hpp valuegraph.hpp
nodebuiltingetendvertex.o: nodebuiltingetendvertex.hpp general.hpp
nodebuiltingetendvertex.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetendvertex.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltingetendvertex.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltingetendvertex.o: codeposition.hpp logger.hpp valueedge.hpp
nodebuiltingetendvertex.o: valuestruct.hpp valuegraph.hpp valuevertex.hpp
nodebuiltingetendvertex.o: valueedgeset.hpp
nodebuiltingetneighbors.o: nodebuiltingetneighbors.hpp general.hpp
nodebuiltingetneighbors.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetneighbors.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltingetneighbors.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltingetneighbors.o: codeposition.hpp logger.hpp valuevertex.hpp
nodebuiltingetneighbors.o: valueedgeset.hpp valuegraph.hpp valuestruct.hpp
nodebuiltingetneighbors.o: valuevertexset.hpp
nodebuiltingetnumedges.o: nodebuiltingetnumedges.hpp general.hpp
nodebuiltingetnumedges.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetnumedges.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltingetnumedges.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltingetnumedges.o: logger.hpp valuegraph.hpp valueedgeset.hpp
nodebuiltingetnumedges.o: valueint.hpp
nodebuiltingetnumvertices.o: nodebuiltingetnumvertices.hpp general.hpp
nodebuiltingetnumvertices.o: nodefunctionbuiltin.hpp nodefunction.hpp
nodebuiltingetnumvertices.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodebuiltingetnumvertices.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltingetnumvertices.o: codeposition.hpp logger.hpp valuegraph.hpp
nodebuiltingetnumvertices.o: valuevertexset.hpp valueint.hpp
nodebuiltingetvertices.o: nodebuiltingetvertices.hpp general.hpp
nodebuiltingetvertices.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltingetvertices.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltingetvertices.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltingetvertices.o: logger.hpp valuegraph.hpp
nodebuiltingraph.o: nodebuiltingraph.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltingraph.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltingraph.o: value.hpp valuenull.hpp context.hpp stringtable.hpp
nodebuiltingraph.o: codeposition.hpp logger.hpp valuegraph.hpp
nodebuiltinhasnext.o: nodebuiltinhasnext.hpp general.hpp
nodebuiltinhasnext.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinhasnext.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinhasnext.o: context.hpp stringtable.hpp codeposition.hpp logger.hpp
nodebuiltin_inst.o: general.hpp context.hpp baseobject.hpp countptr.hpp
nodebuiltin_inst.o: value.hpp stringtable.hpp codeposition.hpp
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
nodebuiltin_inst.o: nodebuiltingraph.hpp nodebuiltinvertexset.hpp
nodebuiltin_inst.o: nodebuiltinedgeset.hpp nodebuiltinisoriented.hpp
nodebuiltin_inst.o: nodebuiltinsetoriented.hpp
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
nodebuiltinintersection.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinintersection.o: codeposition.hpp logger.hpp valuevertexset.hpp
nodebuiltinintersection.o: valueedgeset.hpp
nodebuiltininvertedgesorientation.o: nodebuiltininvertedgesorientation.hpp
nodebuiltininvertedgesorientation.o: general.hpp nodefunctionbuiltin.hpp
nodebuiltininvertedgesorientation.o: nodefunction.hpp node.hpp baseobject.hpp
nodebuiltininvertedgesorientation.o: countptr.hpp value.hpp valuenull.hpp
nodebuiltininvertedgesorientation.o: context.hpp stringtable.hpp
nodebuiltininvertedgesorientation.o: codeposition.hpp logger.hpp
nodebuiltininvertedgesorientation.o: valuegraph.hpp
nodebuiltinisarray.o: nodebuiltinisarray.hpp general.hpp
nodebuiltinisarray.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisarray.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinisarray.o: context.hpp stringtable.hpp codeposition.hpp logger.hpp
nodebuiltinisarray.o: valuebool.hpp
nodebuiltinisbool.o: nodebuiltinisbool.hpp general.hpp
nodebuiltinisbool.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisbool.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinisbool.o: context.hpp stringtable.hpp codeposition.hpp logger.hpp
nodebuiltinisbool.o: valuebool.hpp
nodebuiltinisedge.o: nodebuiltinisedge.hpp general.hpp
nodebuiltinisedge.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisedge.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinisedge.o: context.hpp stringtable.hpp codeposition.hpp logger.hpp
nodebuiltinisedge.o: valuebool.hpp
nodebuiltinisedgeset.o: nodebuiltinisedgeset.hpp general.hpp
nodebuiltinisedgeset.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisedgeset.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinisedgeset.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisedgeset.o: logger.hpp valuebool.hpp
nodebuiltinisfloat.o: nodebuiltinisfloat.hpp general.hpp
nodebuiltinisfloat.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisfloat.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinisfloat.o: context.hpp stringtable.hpp codeposition.hpp logger.hpp
nodebuiltinisfloat.o: valuebool.hpp
nodebuiltinisgraph.o: nodebuiltinisgraph.hpp general.hpp
nodebuiltinisgraph.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisgraph.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinisgraph.o: context.hpp stringtable.hpp codeposition.hpp logger.hpp
nodebuiltinisgraph.o: valuebool.hpp
nodebuiltinisint.o: nodebuiltinisint.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinisint.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinisint.o: value.hpp valuenull.hpp context.hpp stringtable.hpp
nodebuiltinisint.o: codeposition.hpp logger.hpp valuebool.hpp
nodebuiltinisnull.o: nodebuiltinisnull.hpp general.hpp
nodebuiltinisnull.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisnull.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinisnull.o: context.hpp stringtable.hpp codeposition.hpp logger.hpp
nodebuiltinisnull.o: valuebool.hpp
nodebuiltinisoriented.o: nodebuiltinisoriented.hpp general.hpp
nodebuiltinisoriented.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisoriented.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinisoriented.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisoriented.o: logger.hpp valuebool.hpp valuegraph.hpp
nodebuiltinisstring.o: nodebuiltinisstring.hpp general.hpp
nodebuiltinisstring.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisstring.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinisstring.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisstring.o: logger.hpp valuebool.hpp
nodebuiltinisstruct.o: nodebuiltinisstruct.hpp general.hpp
nodebuiltinisstruct.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisstruct.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinisstruct.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisstruct.o: logger.hpp valuebool.hpp
nodebuiltinisvertex.o: nodebuiltinisvertex.hpp general.hpp
nodebuiltinisvertex.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisvertex.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinisvertex.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisvertex.o: logger.hpp valuebool.hpp
nodebuiltinisvertexset.o: nodebuiltinisvertexset.hpp general.hpp
nodebuiltinisvertexset.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinisvertexset.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinisvertexset.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinisvertexset.o: logger.hpp valuebool.hpp
nodebuiltiniterator.o: nodebuiltiniterator.hpp general.hpp
nodebuiltiniterator.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltiniterator.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltiniterator.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltiniterator.o: logger.hpp
nodebuiltinnext.o: nodebuiltinnext.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinnext.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinnext.o: value.hpp valuenull.hpp context.hpp stringtable.hpp
nodebuiltinnext.o: codeposition.hpp logger.hpp
nodebuiltinpopback.o: nodebuiltinpopback.hpp general.hpp
nodebuiltinpopback.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinpopback.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinpopback.o: context.hpp stringtable.hpp codeposition.hpp logger.hpp
nodebuiltinpopback.o: valuearray.hpp
nodebuiltinpopfront.o: nodebuiltinpopfront.hpp general.hpp
nodebuiltinpopfront.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinpopfront.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinpopfront.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinpopfront.o: logger.hpp valuearray.hpp
nodebuiltinprintstacktrace.o: nodebuiltinprintstacktrace.hpp general.hpp
nodebuiltinprintstacktrace.o: nodefunctionbuiltin.hpp nodefunction.hpp
nodebuiltinprintstacktrace.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodebuiltinprintstacktrace.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinprintstacktrace.o: codeposition.hpp logger.hpp
nodebuiltinpushback.o: nodebuiltinpushback.hpp general.hpp
nodebuiltinpushback.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinpushback.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinpushback.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinpushback.o: logger.hpp valuearray.hpp
nodebuiltinpushfront.o: nodebuiltinpushfront.hpp general.hpp
nodebuiltinpushfront.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinpushfront.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinpushfront.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinpushfront.o: logger.hpp valuearray.hpp
nodebuiltinresetiterator.o: nodebuiltinresetiterator.hpp general.hpp
nodebuiltinresetiterator.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinresetiterator.o: baseobject.hpp countptr.hpp value.hpp
nodebuiltinresetiterator.o: valuenull.hpp context.hpp stringtable.hpp
nodebuiltinresetiterator.o: codeposition.hpp logger.hpp
nodebuiltinsetoriented.o: nodebuiltinsetoriented.hpp general.hpp
nodebuiltinsetoriented.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinsetoriented.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinsetoriented.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinsetoriented.o: logger.hpp valuebool.hpp valueint.hpp
nodebuiltinsetoriented.o: valuegraph.hpp
nodebuiltinsize.o: nodebuiltinsize.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinsize.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinsize.o: value.hpp valuenull.hpp context.hpp stringtable.hpp
nodebuiltinsize.o: codeposition.hpp logger.hpp valuearray.hpp valuestring.hpp
nodebuiltinsize.o: valueint.hpp
nodebuiltinstruct.o: nodebuiltinstruct.hpp general.hpp
nodebuiltinstruct.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinstruct.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinstruct.o: context.hpp stringtable.hpp codeposition.hpp logger.hpp
nodebuiltinstruct.o: valuestruct.hpp
nodebuiltinunion.o: nodebuiltinunion.hpp general.hpp nodefunctionbuiltin.hpp
nodebuiltinunion.o: nodefunction.hpp node.hpp baseobject.hpp countptr.hpp
nodebuiltinunion.o: value.hpp valuenull.hpp context.hpp stringtable.hpp
nodebuiltinunion.o: codeposition.hpp logger.hpp valuevertexset.hpp
nodebuiltinunion.o: valueedgeset.hpp
nodebuiltinverify.o: nodebuiltinverify.hpp general.hpp
nodebuiltinverify.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinverify.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinverify.o: context.hpp stringtable.hpp codeposition.hpp logger.hpp
nodebuiltinverify.o: valuebool.hpp
nodebuiltinvertexset.o: nodebuiltinvertexset.hpp general.hpp
nodebuiltinvertexset.o: nodefunctionbuiltin.hpp nodefunction.hpp node.hpp
nodebuiltinvertexset.o: baseobject.hpp countptr.hpp value.hpp valuenull.hpp
nodebuiltinvertexset.o: context.hpp stringtable.hpp codeposition.hpp
nodebuiltinvertexset.o: logger.hpp valuevertexset.hpp valuegraph.hpp
nodecondition.o: nodecondition.hpp general.hpp node.hpp baseobject.hpp
nodecondition.o: countptr.hpp value.hpp valuenull.hpp nodeemptycommand.hpp
node.o: node.hpp general.hpp baseobject.hpp countptr.hpp value.hpp
nodeemptycommand.o: nodeemptycommand.hpp general.hpp node.hpp baseobject.hpp
nodeemptycommand.o: countptr.hpp value.hpp valuenull.hpp
nodeforeach.o: nodeforeach.hpp general.hpp node.hpp baseobject.hpp
nodeforeach.o: countptr.hpp value.hpp context.hpp stringtable.hpp
nodeforeach.o: codeposition.hpp nodeemptycommand.hpp nodejumpbreak.hpp
nodeforeach.o: nodejumpcontinue.hpp valuenull.hpp
nodefunctionbuiltin.o: nodefunctionbuiltin.hpp general.hpp nodefunction.hpp
nodefunctionbuiltin.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodefunctionbuiltin.o: context.hpp stringtable.hpp codeposition.hpp
nodefunctionbuiltin.o: logger.hpp
nodefunctioncall.o: nodefunctioncall.hpp general.hpp node.hpp baseobject.hpp
nodefunctioncall.o: countptr.hpp value.hpp codeposition.hpp nodefunction.hpp
nodefunctioncall.o: nodeblock.hpp valuenull.hpp logger.hpp context.hpp
nodefunctioncall.o: stringtable.hpp
nodefunction.o: nodefunction.hpp general.hpp node.hpp baseobject.hpp
nodefunction.o: countptr.hpp value.hpp context.hpp stringtable.hpp
nodefunction.o: codeposition.hpp
nodefunctionscript.o: nodefunctionscript.hpp general.hpp nodefunction.hpp
nodefunctionscript.o: node.hpp baseobject.hpp countptr.hpp value.hpp
nodefunctionscript.o: codeposition.hpp nodeemptycommand.hpp
nodefunctionscript.o: nodejumpcontinue.hpp nodejumpbreak.hpp valuenull.hpp
nodefunctionscript.o: context.hpp stringtable.hpp logger.hpp
nodeglobal.o: nodeglobal.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodeglobal.o: value.hpp context.hpp stringtable.hpp codeposition.hpp
nodejumpbreak.o: nodejumpbreak.hpp general.hpp node.hpp baseobject.hpp
nodejumpbreak.o: countptr.hpp value.hpp valuenull.hpp
nodejumpcontinue.o: nodejumpcontinue.hpp general.hpp node.hpp baseobject.hpp
nodejumpcontinue.o: countptr.hpp value.hpp valuenull.hpp
nodeloop.o: nodeloop.hpp general.hpp node.hpp baseobject.hpp countptr.hpp
nodeloop.o: value.hpp valuenull.hpp valuebool.hpp nodeemptycommand.hpp
nodeloop.o: nodevalue.hpp nodejumpbreak.hpp nodejumpcontinue.hpp
nodeposition.o: nodeposition.hpp general.hpp node.hpp baseobject.hpp
nodeposition.o: countptr.hpp value.hpp codeposition.hpp context.hpp
nodeposition.o: stringtable.hpp
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
parser.o: nodefunctioncall.hpp codeposition.hpp parser.hpp context.hpp
parser.o: stringtable.hpp nodebinaryadd.hpp nodebinary.hpp nodebinaryand.hpp
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
tests.o: tests.hpp general.hpp baseobject.hpp logger.hpp context.hpp
tests.o: countptr.hpp value.hpp stringtable.hpp codeposition.hpp valueint.hpp
tests.o: valuefloat.hpp valuebool.hpp valuestring.hpp valuestruct.hpp
tests.o: valuenull.hpp valuereference.hpp valueidentifier.hpp valuegraph.hpp
tests.o: valuevertex.hpp valueedgeset.hpp valueedge.hpp valuevertexset.hpp
tests.o: lexan.hpp lexaniterator.hpp lexantokens.hpp node.hpp nodeblock.hpp
tests.o: nodefunctioncall.hpp parser.hpp nodeunarysub.hpp nodeunary.hpp
tests.o: nodeunarynot.hpp nodebinaryadd.hpp nodebinary.hpp nodebinarysub.hpp
tests.o: nodecondition.hpp nodeemptycommand.hpp nodefunctionscript.hpp
tests.o: nodefunction.hpp nodebinaryass.hpp nodevalue.hpp nodebinarylt.hpp
tests.o: nodeunaryreturn.hpp nodebinarymult.hpp valuearray.hpp
valuearray.o: valuearray.hpp general.hpp value.hpp baseobject.hpp
valuearray.o: countptr.hpp valuenull.hpp valuebool.hpp valuereference.hpp
valuearray.o: valueint.hpp valuefloat.hpp logger.hpp context.hpp
valuearray.o: stringtable.hpp codeposition.hpp
valuebool.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuebool.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuebool.o: valuestruct.hpp valuearray.hpp logger.hpp context.hpp
valuebool.o: stringtable.hpp codeposition.hpp
value.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
value.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
value.o: valuestruct.hpp valuearray.hpp valuereference.hpp
value.o: valueidentifier.hpp context.hpp stringtable.hpp codeposition.hpp
value.o: valuegraph.hpp valuevertex.hpp valueedgeset.hpp valueedge.hpp
value.o: logger.hpp
valueedge.o: valueedge.hpp general.hpp valuestruct.hpp value.hpp
valueedge.o: baseobject.hpp countptr.hpp valuenull.hpp valuegraph.hpp
valueedge.o: valuebool.hpp valuevertex.hpp valueedgeset.hpp
valueedgeset.o: valueedgeset.hpp general.hpp value.hpp baseobject.hpp
valueedgeset.o: countptr.hpp logger.hpp context.hpp stringtable.hpp
valueedgeset.o: codeposition.hpp valuebool.hpp valueedge.hpp valuestruct.hpp
valueedgeset.o: valuenull.hpp valuegraph.hpp
valuefloat.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuefloat.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuefloat.o: valuestruct.hpp valuearray.hpp logger.hpp context.hpp
valuefloat.o: stringtable.hpp codeposition.hpp
valuegraph.o: valuegraph.hpp general.hpp value.hpp baseobject.hpp
valuegraph.o: countptr.hpp logger.hpp context.hpp stringtable.hpp
valuegraph.o: codeposition.hpp valuebool.hpp valuevertex.hpp valueedgeset.hpp
valuegraph.o: valuestruct.hpp valuenull.hpp valueedge.hpp valuevertexset.hpp
valueidentifier.o: valueidentifier.hpp general.hpp value.hpp baseobject.hpp
valueidentifier.o: countptr.hpp context.hpp stringtable.hpp codeposition.hpp
valueidentifier.o: valuenull.hpp valuebool.hpp valueint.hpp valuefloat.hpp
valueidentifier.o: valuestring.hpp valuestruct.hpp valuereference.hpp
valueidentifier.o: valuegraph.hpp valuevertex.hpp valueedgeset.hpp
valueidentifier.o: valueedge.hpp valuevertexset.hpp logger.hpp
valueint.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valueint.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valueint.o: valuestruct.hpp valuearray.hpp logger.hpp context.hpp
valueint.o: stringtable.hpp codeposition.hpp
valuenull.o: value.hpp general.hpp baseobject.hpp countptr.hpp valuenull.hpp
valuenull.o: valuebool.hpp valueint.hpp valuefloat.hpp valuestring.hpp
valuenull.o: valuestruct.hpp
valuereference.o: valuereference.hpp general.hpp value.hpp baseobject.hpp
valuereference.o: countptr.hpp valuenull.hpp valuebool.hpp valueint.hpp
valuereference.o: valuefloat.hpp valuestring.hpp valuestruct.hpp
valuereference.o: valueidentifier.hpp context.hpp stringtable.hpp
valuereference.o: codeposition.hpp valuegraph.hpp valuevertex.hpp
valuereference.o: valueedgeset.hpp valueedge.hpp valuevertexset.hpp
valuestring.o: value.hpp general.hpp baseobject.hpp countptr.hpp
valuestring.o: valuenull.hpp valuebool.hpp valueint.hpp valuefloat.hpp
valuestring.o: valuestring.hpp valuestruct.hpp
valuestruct.o: valuestruct.hpp general.hpp value.hpp baseobject.hpp
valuestruct.o: countptr.hpp valuenull.hpp valuebool.hpp valuereference.hpp
valuestruct.o: context.hpp stringtable.hpp codeposition.hpp
valuevertex.o: valuevertex.hpp general.hpp value.hpp baseobject.hpp
valuevertex.o: countptr.hpp valueedgeset.hpp valuegraph.hpp valuestruct.hpp
valuevertex.o: valuenull.hpp valuebool.hpp valueedge.hpp valuevertexset.hpp
valuevertexset.o: valuevertexset.hpp general.hpp value.hpp baseobject.hpp
valuevertexset.o: countptr.hpp valuebool.hpp valuevertex.hpp valueedgeset.hpp
valuevertexset.o: valuegraph.hpp valuestruct.hpp valuenull.hpp logger.hpp
valuevertexset.o: context.hpp stringtable.hpp codeposition.hpp
