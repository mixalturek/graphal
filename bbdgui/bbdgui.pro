# -------------------------------------------------
# Project created by QtCreator 2009-04-24T18:59:48
# -------------------------------------------------
TARGET = bbdgui
TEMPLATE = app
RC_FILE = bbdgui.rc
ICON = images/toast/toast.icns
SOURCES += main.cpp \
    mainwindow.cpp \
    texteditor.cpp \
    settings.cpp \
    ../bbd/logger.cpp \
    ../bbd/lexaniteratorstring.cpp \
    ../bbd/lexaniteratorfile.cpp \
    ../bbd/lexaniterator.cpp \
    ../bbd/lexan.cpp \
    ../bbd/init_static_objects.cpp \
    ../bbd/valuevertexset.cpp \
    ../bbd/valuevertex.cpp \
    ../bbd/valuestruct.cpp \
    ../bbd/valuestring.cpp \
    ../bbd/valuereference.cpp \
    ../bbd/valuenull.cpp \
    ../bbd/valueint.cpp \
    ../bbd/valueidentifier.cpp \
    ../bbd/valuegraph.cpp \
    ../bbd/valuefloat.cpp \
    ../bbd/valueedgeset.cpp \
    ../bbd/valueedge.cpp \
    ../bbd/valuebool.cpp \
    ../bbd/valuearray.cpp \
    ../bbd/value.cpp \
    ../bbd/stringtable.cpp \
    ../bbd/parser.cpp \
    ../bbd/nodevalue.cpp \
    ../bbd/nodeunarysub.cpp \
    ../bbd/nodeunaryreturn.cpp \
    ../bbd/nodeunarynot.cpp \
    ../bbd/nodeunaryincpre.cpp \
    ../bbd/nodeunaryincpost.cpp \
    ../bbd/nodeunarydecpre.cpp \
    ../bbd/nodeunarydecpost.cpp \
    ../bbd/nodeunary.cpp \
    ../bbd/nodeposition.cpp \
    ../bbd/nodeloop.cpp \
    ../bbd/nodejumpcontinue.cpp \
    ../bbd/nodejumpbreak.cpp \
    ../bbd/nodeglobal.cpp \
    ../bbd/nodefunctionscript.cpp \
    ../bbd/nodefunctioncall.cpp \
    ../bbd/nodefunctionbuiltin.cpp \
    ../bbd/nodefunction.cpp \
    ../bbd/nodeforeach.cpp \
    ../bbd/nodeemptycommand.cpp \
    ../bbd/nodecondition.cpp \
    ../bbd/nodebuiltinvertexset.cpp \
    ../bbd/nodebuiltinverify.cpp \
    ../bbd/nodebuiltinunion.cpp \
    ../bbd/nodebuiltinstruct.cpp \
    ../bbd/nodebuiltinsize.cpp \
    ../bbd/nodebuiltinsetoriented.cpp \
    ../bbd/nodebuiltinresetiterator.cpp \
    ../bbd/nodebuiltinpushfront.cpp \
    ../bbd/nodebuiltinpushback.cpp \
    ../bbd/nodebuiltinprintstacktrace.cpp \
    ../bbd/nodebuiltinpopfront.cpp \
    ../bbd/nodebuiltinpopback.cpp \
    ../bbd/nodebuiltinnext.cpp \
    ../bbd/nodebuiltiniterator.cpp \
    ../bbd/nodebuiltinisvertexset.cpp \
    ../bbd/nodebuiltinisvertex.cpp \
    ../bbd/nodebuiltinisstruct.cpp \
    ../bbd/nodebuiltinisstring.cpp \
    ../bbd/nodebuiltinisoriented.cpp \
    ../bbd/nodebuiltinisnull.cpp \
    ../bbd/nodebuiltinisint.cpp \
    ../bbd/nodebuiltinisgraph.cpp \
    ../bbd/nodebuiltinisfloat.cpp \
    ../bbd/nodebuiltinisedgeset.cpp \
    ../bbd/nodebuiltinisedge.cpp \
    ../bbd/nodebuiltinisbool.cpp \
    ../bbd/nodebuiltinisarray.cpp \
    ../bbd/nodebuiltininvertedgesorientation.cpp \
    ../bbd/nodebuiltinintersection.cpp \
    ../bbd/nodebuiltinhasnext.cpp \
    ../bbd/nodebuiltingraph.cpp \
    ../bbd/nodebuiltingetvertices.cpp \
    ../bbd/nodebuiltingetnumvertices.cpp \
    ../bbd/nodebuiltingetnumedges.cpp \
    ../bbd/nodebuiltingetneighbors.cpp \
    ../bbd/nodebuiltingetendvertex.cpp \
    ../bbd/nodebuiltingetedges.cpp \
    ../bbd/nodebuiltingetdegree.cpp \
    ../bbd/nodebuiltingetbeginvertex.cpp \
    ../bbd/nodebuiltingeneratevertex.cpp \
    ../bbd/nodebuiltingenerateedge.cpp \
    ../bbd/nodebuiltinfront.cpp \
    ../bbd/nodebuiltinexit.cpp \
    ../bbd/nodebuiltinedgeset.cpp \
    ../bbd/nodebuiltinecho.cpp \
    ../bbd/nodebuiltindump.cpp \
    ../bbd/nodebuiltindifference.cpp \
    ../bbd/nodebuiltindeletevertex.cpp \
    ../bbd/nodebuiltindeleteedge.cpp \
    ../bbd/nodebuiltincontains.cpp \
    ../bbd/nodebuiltinbreakpoint.cpp \
    ../bbd/nodebuiltinback.cpp \
    ../bbd/nodebuiltinassert.cpp \
    ../bbd/nodebuiltinarray.cpp \
    ../bbd/nodebuiltinadd.cpp \
    ../bbd/nodebuiltin_inst.cpp \
    ../bbd/nodeblock.cpp \
    ../bbd/nodebinarysub.cpp \
    ../bbd/nodebinaryor.cpp \
    ../bbd/nodebinaryne.cpp \
    ../bbd/nodebinarymult.cpp \
    ../bbd/nodebinarymod.cpp \
    ../bbd/nodebinarymember.cpp \
    ../bbd/nodebinarylt.cpp \
    ../bbd/nodebinaryle.cpp \
    ../bbd/nodebinaryindex.cpp \
    ../bbd/nodebinarygt.cpp \
    ../bbd/nodebinaryge.cpp \
    ../bbd/nodebinaryeq.cpp \
    ../bbd/nodebinarydiv.cpp \
    ../bbd/nodebinaryasssub.cpp \
    ../bbd/nodebinaryassref.cpp \
    ../bbd/nodebinaryassmult.cpp \
    ../bbd/nodebinaryassmod.cpp \
    ../bbd/nodebinaryassdiv.cpp \
    ../bbd/nodebinaryassadd.cpp \
    ../bbd/nodebinaryass.cpp \
    ../bbd/nodebinaryand.cpp \
    ../bbd/nodebinaryadd.cpp \
    ../bbd/nodebinary.cpp \
    ../bbd/node.cpp \
    ../bbd/exitvalue.cpp \
    ../bbd/context.cpp \
    ../bbd/codeposition.cpp \
    ../bbd/baseobject.cpp
HEADERS += mainwindow.h \
    texteditor.h \
    settings.h \
    ../bbd/logger.hpp \
    ../bbd/lexantokens.hpp \
    ../bbd/lexaniteratorstring.hpp \
    ../bbd/lexaniteratorfile.hpp \
    ../bbd/lexaniterator.hpp \
    ../bbd/lexan.hpp \
    ../bbd/general.hpp \
    ../bbd/version.hpp \
    ../bbd/valuevertexset.hpp \
    ../bbd/valuevertex.hpp \
    ../bbd/valuestruct.hpp \
    ../bbd/valuestring.hpp \
    ../bbd/valuereference.hpp \
    ../bbd/valuenull.hpp \
    ../bbd/valueint.hpp \
    ../bbd/valueidentifier.hpp \
    ../bbd/valuegraph.hpp \
    ../bbd/valuefloat.hpp \
    ../bbd/valueedgeset.hpp \
    ../bbd/valueedge.hpp \
    ../bbd/valuebool.hpp \
    ../bbd/valuearray.hpp \
    ../bbd/value.hpp \
    ../bbd/stringtable.hpp \
    ../bbd/parser.hpp \
    ../bbd/nodevalue.hpp \
    ../bbd/nodeunarysub.hpp \
    ../bbd/nodeunaryreturn.hpp \
    ../bbd/nodeunarynot.hpp \
    ../bbd/nodeunaryincpre.hpp \
    ../bbd/nodeunaryincpost.hpp \
    ../bbd/nodeunarydecpre.hpp \
    ../bbd/nodeunarydecpost.hpp \
    ../bbd/nodeunary.hpp \
    ../bbd/nodeposition.hpp \
    ../bbd/nodeloop.hpp \
    ../bbd/nodejumpcontinue.hpp \
    ../bbd/nodejumpbreak.hpp \
    ../bbd/nodeglobal.hpp \
    ../bbd/nodefunctionscript.hpp \
    ../bbd/nodefunctioncall.hpp \
    ../bbd/nodefunctionbuiltin.hpp \
    ../bbd/nodefunction.hpp \
    ../bbd/nodeforeach.hpp \
    ../bbd/nodeemptycommand.hpp \
    ../bbd/nodecondition.hpp \
    ../bbd/nodebuiltinvertexset.hpp \
    ../bbd/nodebuiltinverify.hpp \
    ../bbd/nodebuiltinunion.hpp \
    ../bbd/nodebuiltinstruct.hpp \
    ../bbd/nodebuiltinsize.hpp \
    ../bbd/nodebuiltinsetoriented.hpp \
    ../bbd/nodebuiltinresetiterator.hpp \
    ../bbd/nodebuiltinpushfront.hpp \
    ../bbd/nodebuiltinpushback.hpp \
    ../bbd/nodebuiltinprintstacktrace.hpp \
    ../bbd/nodebuiltinpopfront.hpp \
    ../bbd/nodebuiltinpopback.hpp \
    ../bbd/nodebuiltinnext.hpp \
    ../bbd/nodebuiltiniterator.hpp \
    ../bbd/nodebuiltinisvertexset.hpp \
    ../bbd/nodebuiltinisvertex.hpp \
    ../bbd/nodebuiltinisstruct.hpp \
    ../bbd/nodebuiltinisstring.hpp \
    ../bbd/nodebuiltinisoriented.hpp \
    ../bbd/nodebuiltinisnull.hpp \
    ../bbd/nodebuiltinisint.hpp \
    ../bbd/nodebuiltinisgraph.hpp \
    ../bbd/nodebuiltinisfloat.hpp \
    ../bbd/nodebuiltinisedgeset.hpp \
    ../bbd/nodebuiltinisedge.hpp \
    ../bbd/nodebuiltinisbool.hpp \
    ../bbd/nodebuiltinisarray.hpp \
    ../bbd/nodebuiltininvertedgesorientation.hpp \
    ../bbd/nodebuiltinintersection.hpp \
    ../bbd/nodebuiltinhasnext.hpp \
    ../bbd/nodebuiltingraph.hpp \
    ../bbd/nodebuiltingetvertices.hpp \
    ../bbd/nodebuiltingetnumvertices.hpp \
    ../bbd/nodebuiltingetnumedges.hpp \
    ../bbd/nodebuiltingetneighbors.hpp \
    ../bbd/nodebuiltingetendvertex.hpp \
    ../bbd/nodebuiltingetedges.hpp \
    ../bbd/nodebuiltingetdegree.hpp \
    ../bbd/nodebuiltingetbeginvertex.hpp \
    ../bbd/nodebuiltingeneratevertex.hpp \
    ../bbd/nodebuiltingenerateedge.hpp \
    ../bbd/nodebuiltinfront.hpp \
    ../bbd/nodebuiltinexit.hpp \
    ../bbd/nodebuiltinedgeset.hpp \
    ../bbd/nodebuiltinecho.hpp \
    ../bbd/nodebuiltindump.hpp \
    ../bbd/nodebuiltindifference.hpp \
    ../bbd/nodebuiltindeletevertex.hpp \
    ../bbd/nodebuiltindeleteedge.hpp \
    ../bbd/nodebuiltincontains.hpp \
    ../bbd/nodebuiltinbreakpoint.hpp \
    ../bbd/nodebuiltinback.hpp \
    ../bbd/nodebuiltinassert.hpp \
    ../bbd/nodebuiltinarray.hpp \
    ../bbd/nodebuiltinadd.hpp \
    ../bbd/nodebuiltin_inst.hpp \
    ../bbd/nodeblock.hpp \
    ../bbd/nodebinarysub.hpp \
    ../bbd/nodebinaryor.hpp \
    ../bbd/nodebinaryne.hpp \
    ../bbd/nodebinarymult.hpp \
    ../bbd/nodebinarymod.hpp \
    ../bbd/nodebinarymember.hpp \
    ../bbd/nodebinarylt.hpp \
    ../bbd/nodebinaryle.hpp \
    ../bbd/nodebinaryindex.hpp \
    ../bbd/nodebinarygt.hpp \
    ../bbd/nodebinaryge.hpp \
    ../bbd/nodebinaryeq.hpp \
    ../bbd/nodebinarydiv.hpp \
    ../bbd/nodebinaryasssub.hpp \
    ../bbd/nodebinaryassref.hpp \
    ../bbd/nodebinaryassmult.hpp \
    ../bbd/nodebinaryassmod.hpp \
    ../bbd/nodebinaryassdiv.hpp \
    ../bbd/nodebinaryassadd.hpp \
    ../bbd/nodebinaryass.hpp \
    ../bbd/nodebinaryand.hpp \
    ../bbd/nodebinaryadd.hpp \
    ../bbd/nodebinary.hpp \
    ../bbd/node.hpp \
    ../bbd/exitvalue.hpp \
    ../bbd/countptr.hpp \
    ../bbd/context.hpp \
    ../bbd/codeposition.hpp \
    ../bbd/baseobject.hpp
RESOURCES += resources.qrc
OTHER_FILES +=
