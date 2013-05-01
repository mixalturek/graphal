/*
 * Copyright 2009 Michal Turek
 *
 * This file is part of Graphal library.
 * http://graphal.sourceforge.net/
 *
 * Graphal library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Graphal library.  If not, see <http://www.gnu.org/licenses/>.
 */


/****************************************************************************
 *                                                                          *
 *             This file was generated by gen_builtin.pl script.            *
 *                        Don't update it manually!                         *
 *                                                                          *
 ****************************************************************************/

#include <list>
#include "general.h"
#include "context.h"

#include "generated/nodebuiltinecho.h"
#include "generated/nodebuiltinprint.h"
#include "generated/nodebuiltinprintln.h"
#include "generated/nodebuiltindump.h"
#include "generated/nodebuiltinexit.h"
#include "generated/nodebuiltinassert.h"
#include "generated/nodebuiltinverify.h"
#include "generated/nodebuiltinbreakpoint.h"
#include "generated/nodebuiltinisnull.h"
#include "generated/nodebuiltinisbool.h"
#include "generated/nodebuiltinisint.h"
#include "generated/nodebuiltinisfloat.h"
#include "generated/nodebuiltinisstring.h"
#include "generated/nodebuiltinisstruct.h"
#include "generated/nodebuiltinisarray.h"
#include "generated/nodebuiltinisset.h"
#include "generated/nodebuiltinisgraph.h"
#include "generated/nodebuiltinisvertex.h"
#include "generated/nodebuiltinisedge.h"
#include "generated/nodebuiltinprintstacktrace.h"
#include "generated/nodebuiltiniterator.h"
#include "generated/nodebuiltinhasnext.h"
#include "generated/nodebuiltinnext.h"
#include "generated/nodebuiltinresetiterator.h"
#include "generated/nodebuiltinarray.h"
#include "generated/nodebuiltinset.h"
#include "generated/nodebuiltinstruct.h"
#include "generated/nodebuiltinsize.h"
#include "generated/nodebuiltinpushfront.h"
#include "generated/nodebuiltinpushback.h"
#include "generated/nodebuiltinpopfront.h"
#include "generated/nodebuiltinpopback.h"
#include "generated/nodebuiltinback.h"
#include "generated/nodebuiltinfront.h"
#include "generated/nodebuiltingraph.h"
#include "generated/nodebuiltinloadfromfile.h"
#include "generated/nodebuiltinisdirected.h"
#include "generated/nodebuiltinsetdirected.h"
#include "generated/nodebuiltininvertedgesdirection.h"
#include "generated/nodebuiltingeneratevertex.h"
#include "generated/nodebuiltingenerateedge.h"
#include "generated/nodebuiltindeletevertex.h"
#include "generated/nodebuiltindeleteedge.h"
#include "generated/nodebuiltingetnumvertices.h"
#include "generated/nodebuiltingetnumedges.h"
#include "generated/nodebuiltingetvertices.h"
#include "generated/nodebuiltingetedges.h"
#include "generated/nodebuiltingetdegree.h"
#include "generated/nodebuiltingetneighbors.h"
#include "generated/nodebuiltingetbeginvertex.h"
#include "generated/nodebuiltingetendvertex.h"
#include "generated/nodebuiltininsert.h"
#include "generated/nodebuiltinremove.h"
#include "generated/nodebuiltincontains.h"
#include "generated/nodebuiltinunion.h"
#include "generated/nodebuiltinintersection.h"
#include "generated/nodebuiltindifference.h"
#include "generated/nodebuiltingetadjacencymatrix.h"
#include "generated/nodebuiltinsetpropertytoallvertices.h"
#include "generated/nodebuiltinsetpropertytoalledges.h"
#include "generated/nodebuiltinsetpropertytoallstructitems.h"
#include "generated/nodebuiltinvisregister.h"
#include "generated/nodebuiltinvissetpos.h"
#include "generated/nodebuiltinvissetcolor.h"
#include "generated/nodebuiltinvissetview.h"
#include "generated/nodebuiltinvisuseweightwhenpaintingedges.h"
#include "generated/nodebuiltinvisscreenshot.h"
#include "generated/nodebuiltinvisgetgraph.h"

void generateBuiltinFunctions(void)
{
	list<identifier> params;
	params.push_back(STR2ID("a"));
	params.push_back(STR2ID("b"));
	params.push_back(STR2ID("c"));
	params.push_back(STR2ID("d"));
	params.push_back(STR2ID("e"));
	params.push_back(STR2ID("f"));

	list<identifier>::iterator p0 = params.begin();
	list<identifier>::iterator p1 = ++p0;
	list<identifier>::iterator p2 = ++p0;
	list<identifier>::iterator p3 = ++p0;
	list<identifier>::iterator p4 = ++p0;
	list<identifier>::iterator p5 = ++p0;
	p0 = params.begin();

	CONTEXT.addFunction(new NodeBuiltinEcho(STR2ID("echo"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinPrint(STR2ID("print"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinPrintln(STR2ID("println"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinDump(STR2ID("dump"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinExit(STR2ID("exit"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinAssert(STR2ID("assert"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinVerify(STR2ID("verify"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinBreakpoint(STR2ID("breakpoint"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinIsNull(STR2ID("isNull"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinIsBool(STR2ID("isBool"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinIsInt(STR2ID("isInt"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinIsFloat(STR2ID("isFloat"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinIsString(STR2ID("isString"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinIsStruct(STR2ID("isStruct"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinIsArray(STR2ID("isArray"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinIsSet(STR2ID("isSet"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinIsGraph(STR2ID("isGraph"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinIsVertex(STR2ID("isVertex"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinIsEdge(STR2ID("isEdge"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinPrintStackTrace(STR2ID("printStackTrace"), new list<identifier>(p0, p0)));
	CONTEXT.addFunction(new NodeBuiltinIterator(STR2ID("iterator"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinHasNext(STR2ID("hasNext"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinNext(STR2ID("next"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinResetIterator(STR2ID("resetIterator"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinArray(STR2ID("array"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinSet(STR2ID("set"), new list<identifier>(p0, p0)));
	CONTEXT.addFunction(new NodeBuiltinStruct(STR2ID("struct"), new list<identifier>(p0, p0)));
	CONTEXT.addFunction(new NodeBuiltinSize(STR2ID("size"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinPushFront(STR2ID("pushFront"), new list<identifier>(p0, p2)));
	CONTEXT.addFunction(new NodeBuiltinPushBack(STR2ID("pushBack"), new list<identifier>(p0, p2)));
	CONTEXT.addFunction(new NodeBuiltinPopFront(STR2ID("popFront"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinPopBack(STR2ID("popBack"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinBack(STR2ID("back"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinFront(STR2ID("front"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinGraph(STR2ID("graph"), new list<identifier>(p0, p0)));
	CONTEXT.addFunction(new NodeBuiltinLoadFromFile(STR2ID("loadFromFile"), new list<identifier>(p0, p2)));
	CONTEXT.addFunction(new NodeBuiltinIsDirected(STR2ID("isDirected"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinSetDirected(STR2ID("setDirected"), new list<identifier>(p0, p2)));
	CONTEXT.addFunction(new NodeBuiltinInvertEdgesDirection(STR2ID("invertEdgesDirection"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinGenerateVertex(STR2ID("generateVertex"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinGenerateEdge(STR2ID("generateEdge"), new list<identifier>(p0, p3)));
	CONTEXT.addFunction(new NodeBuiltinDeleteVertex(STR2ID("deleteVertex"), new list<identifier>(p0, p2)));
	CONTEXT.addFunction(new NodeBuiltinDeleteEdge(STR2ID("deleteEdge"), new list<identifier>(p0, p2)));
	CONTEXT.addFunction(new NodeBuiltinGetNumVertices(STR2ID("getNumVertices"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinGetNumEdges(STR2ID("getNumEdges"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinGetVertices(STR2ID("getVertices"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinGetEdges(STR2ID("getEdges"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinGetDegree(STR2ID("getDegree"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinGetNeighbors(STR2ID("getNeighbors"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinGetBeginVertex(STR2ID("getBeginVertex"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinGetEndVertex(STR2ID("getEndVertex"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinInsert(STR2ID("insert"), new list<identifier>(p0, p2)));
	CONTEXT.addFunction(new NodeBuiltinRemove(STR2ID("remove"), new list<identifier>(p0, p2)));
	CONTEXT.addFunction(new NodeBuiltinContains(STR2ID("contains"), new list<identifier>(p0, p2)));
	CONTEXT.addFunction(new NodeBuiltinUnion(STR2ID("union"), new list<identifier>(p0, p2)));
	CONTEXT.addFunction(new NodeBuiltinIntersection(STR2ID("intersection"), new list<identifier>(p0, p2)));
	CONTEXT.addFunction(new NodeBuiltinDifference(STR2ID("difference"), new list<identifier>(p0, p2)));
	CONTEXT.addFunction(new NodeBuiltinGetAdjacencyMatrix(STR2ID("getAdjacencyMatrix"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinSetPropertyToAllVertices(STR2ID("setPropertyToAllVertices"), new list<identifier>(p0, p3)));
	CONTEXT.addFunction(new NodeBuiltinSetPropertyToAllEdges(STR2ID("setPropertyToAllEdges"), new list<identifier>(p0, p3)));
	CONTEXT.addFunction(new NodeBuiltinSetPropertyToAllStructItems(STR2ID("setPropertyToAllStructItems"), new list<identifier>(p0, p3)));
	CONTEXT.addFunction(new NodeBuiltinVisRegister(STR2ID("visRegister"), new list<identifier>(p0, p5)));
	CONTEXT.addFunction(new NodeBuiltinVisSetPos(STR2ID("visSetPos"), new list<identifier>(p0, p4)));
	CONTEXT.addFunction(new NodeBuiltinVisSetColor(STR2ID("visSetColor"), new list<identifier>(p0, p4)));
	CONTEXT.addFunction(new NodeBuiltinVisSetView(STR2ID("visSetView"), new list<identifier>(p0, p5)));
	CONTEXT.addFunction(new NodeBuiltinVisUseWeightWhenPaintingEdges(STR2ID("visUseWeightWhenPaintingEdges"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinVisScreenshot(STR2ID("visScreenshot"), new list<identifier>(p0, p1)));
	CONTEXT.addFunction(new NodeBuiltinVisGetGraph(STR2ID("visGetGraph"), new list<identifier>(p0, p0)));
}
