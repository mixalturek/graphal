#!/usr/bin/perl -w

$fileheader = <<END_OF_HEADER;
/*
 *      Copyright 2009 Michal Turek <http://woq.nipax.cz/>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

/****************************************************************************
 *                                                                          *
 *                This class was generated by gen_builtin.pl                *
 *                           Don't update directly                          *
 *                                                                          *
 ****************************************************************************/

END_OF_HEADER


$instantiate_inc = "#include <list>\n#include \"general.hpp\"\n#include \"context.hpp\"\n\n";
$instantiate = <<END_OF_CODE;
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

END_OF_CODE


sub genBFClass
{
	my ($funcname, $classname, $numberofparameters, $operation, $include) = @_;
	$include = '' if(!defined $include);

	my $hpp_filename = lc($classname).'.hpp';
	my $cpp_filename = lc($classname).'.cpp';
	my $hpp_define = uc($classname).'_HPP';

	my $hpp_code = <<END_OF_HPP;
$fileheader

#ifndef $hpp_define
#define $hpp_define

#include "general.hpp"
#include "nodefunctionbuiltin.hpp"

class $classname : public NodeFunctionBuiltin
{
public:
	$classname(identifier name, list<identifier>* parameters);
	virtual ~$classname(void);

	virtual CountPtr<Value> execute(void);

private:
	$classname(void);
	$classname(const $classname& object);
	$classname& operator=(const $classname& object);
};

ostream& operator<<(ostream& os, const $classname& node);

#endif /* $hpp_define */

END_OF_HPP


	my $cpp_code = <<END_OF_CPP;
$fileheader

#include <cassert>
#include "$hpp_filename"
#include "valuenull.hpp"
#include "context.hpp"
#include "logger.hpp"
$include

/////////////////////////////////////////////////////////////////////////////
////

$classname\::$classname(identifier name, list<identifier>* parameters)
	: NodeFunctionBuiltin(name, parameters)
{

}

$classname\::~$classname(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////


CountPtr<Value> $classname\::execute(void)
{
END_OF_CPP

	if($numberofparameters > 0)
	{
		$cpp_code .= <<END_OF_CPP;
	vector< CountPtr<Value> > par = getParametersValues();
	assert(par.size() == $numberofparameters);

END_OF_CPP
	}

$cpp_code .= <<END_OF_CPP;
$operation
}

ostream& operator<<(ostream& os, const $classname& node)
{
	node.dump(os, 0);
	return os;
}

END_OF_CPP


#	if( -e $hpp_filename || -e $cpp_filename)
#	{
#		warn("$classname already defined!");
#		return;
#	}

	print "Generating $classname\n";

	open(FILE_HPP, ">$hpp_filename") or die "Cannot open output file: $hpp_filename\n";
	print FILE_HPP $hpp_code;
	close FILE_HPP;

	open(FILE_CPP, ">$cpp_filename") or die "Cannot open output file: $cpp_filename\n";
	print FILE_CPP $cpp_code;
	close FILE_CPP;


	$instantiate_inc .= "#include \"$hpp_filename\"\n";
	$instantiate .= "\tCONTEXT.addFunction(new $classname(STR2ID(\"$funcname\"), new list<identifier>(p0, p$numberofparameters)));\n";
}


my $code;
my $include;
my $funcdecl;



#############################################################################
####

$funcdecl = 'echo(object) : object';

$code = <<END_OF_CODE;
	SCRIPT_STDOUT(par[0]->toString());
	return par[0];
END_OF_CODE
genBFClass('echo', 'NodeBuiltinEcho', 1, $code);


#############################################################################
####

$funcdecl = 'dump(object) : object';

$code = <<END_OF_CODE;
	ostringstream os;
	par[0]->dump(os, 0);
	SCRIPT_STDOUT(os.str());

	return par[0];
END_OF_CODE
genBFClass('dump', 'NodeBuiltinDump', 1, $code);


#############################################################################
####

$funcdecl = 'exit(object) : null';

$include = <<END_OF_CODE;
#include "exitvalue.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	throw new ExitValue(par[0]);

	// It will never be called
	return VALUENULL;
END_OF_CODE
genBFClass('exit', 'NodeBuiltinExit', 1, $code, $include);


#############################################################################
####

$funcdecl = 'assert(object) : object';

$include = <<END_OF_CODE;
#include <stdexcept>
END_OF_CODE

$code = <<END_OF_CODE;
	if(!par[0]->toBool())
		throw runtime_error(_("Assertion failed"));

	return par[0];
END_OF_CODE
genBFClass('assert', 'NodeBuiltinAssert', 1, $code, $include);


#############################################################################
####

$funcdecl = 'verify(object) : bool';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	if(!par[0]->toBool())
	{
		WARN_P(_("Verify: Operation was not successful"));
		return VALUEBOOL_FALSE;
	}

	return VALUEBOOL_TRUE;
END_OF_CODE
genBFClass('verify', 'NodeBuiltinVerify', 1, $code, $include);


#############################################################################
####

$funcdecl = 'breakpoint(object) : null';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	if(par[0]->toBool())
		CONTEXT.breakpoint();

	return VALUENULL;
END_OF_CODE
genBFClass('breakpoint', 'NodeBuiltinBreakpoint', 1, $code, $include);


#############################################################################
####

$funcdecl = 'isNull(object) : bool';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	return (par[0]->isNull()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
END_OF_CODE
genBFClass('isNull', 'NodeBuiltinIsNull', 1, $code, $include);


#############################################################################
####

$funcdecl = 'isBool(object) : bool';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	return (par[0]->toValueBool() != NULL) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
END_OF_CODE
genBFClass('isBool', 'NodeBuiltinIsBool', 1, $code, $include);


#############################################################################
####

$funcdecl = 'isInt(object) : bool';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	return (par[0]->toValueInt() != NULL) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
END_OF_CODE
genBFClass('isInt', 'NodeBuiltinIsInt', 1, $code, $include);


#############################################################################
####

$funcdecl = 'isFloat(object) : bool';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	return (par[0]->toValueFloat() != NULL) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
END_OF_CODE
genBFClass('isFloat', 'NodeBuiltinIsFloat', 1, $code, $include);


#############################################################################
####

$funcdecl = 'isString(object) : bool';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	return (par[0]->toValueString() != NULL) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
END_OF_CODE
genBFClass('isString', 'NodeBuiltinIsString', 1, $code, $include);


#############################################################################
####

$funcdecl = 'isStruct(object) : bool';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	return (par[0]->toValueStruct() != NULL) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
END_OF_CODE
genBFClass('isStruct', 'NodeBuiltinIsStruct', 1, $code, $include);


#############################################################################
####

$funcdecl = 'isArray(object) : bool';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	return (par[0]->toValueArray() != NULL) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
END_OF_CODE
genBFClass('isArray', 'NodeBuiltinIsArray', 1, $code, $include);


#############################################################################
####

$funcdecl = 'isGraph(object) : bool';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	return (par[0]->toValueGraph() != NULL) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
END_OF_CODE
genBFClass('isGraph', 'NodeBuiltinIsGraph', 1, $code, $include);


#############################################################################
####

$funcdecl = 'isVertex(object) : bool';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	return (par[0]->toValueVertex() != NULL) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
END_OF_CODE
genBFClass('isVertex', 'NodeBuiltinIsVertex', 1, $code, $include);


#############################################################################
####

$funcdecl = 'isEdge(object) : bool';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	return (par[0]->toValueEdge() != NULL) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
END_OF_CODE
genBFClass('isEdge', 'NodeBuiltinIsEdge', 1, $code, $include);


#############################################################################
####

$funcdecl = 'isVertexSet(object) : bool';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	return (par[0]->toValueVertexSet() != NULL) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
END_OF_CODE
genBFClass('isVertexSet', 'NodeBuiltinIsVertexSet', 1, $code, $include);


#############################################################################
####

$funcdecl = 'isEdgeSet(object) : bool';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	return (par[0]->toValueEdgeSet() != NULL) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
END_OF_CODE
genBFClass('isEdgeSet', 'NodeBuiltinIsEdgeSet', 1, $code, $include);


#############################################################################
####

$funcdecl = 'printStackTrace() : null';

$include = <<END_OF_CODE;
END_OF_CODE

$code = <<END_OF_CODE;
	CONTEXT.printStackTrace();
	return VALUENULL;
END_OF_CODE
genBFClass('printStackTrace', 'NodeBuiltinPrintStackTrace', 0, $code, $include);


#############################################################################
####

$funcdecl = 'iterator(object) : object';

$include = <<END_OF_CODE;
END_OF_CODE

$code = <<END_OF_CODE;
	return par[0]->iterator();
END_OF_CODE
genBFClass('iterator', 'NodeBuiltinIterator', 1, $code, $include);


#############################################################################
####

$funcdecl = 'hasNext(object) : bool';

$include = <<END_OF_CODE;
END_OF_CODE

$code = <<END_OF_CODE;
	return par[0]->hasNext();
END_OF_CODE
genBFClass('hasNext', 'NodeBuiltinHasNext', 1, $code, $include);


#############################################################################
####

$funcdecl = 'next(object) : object';

$include = <<END_OF_CODE;
END_OF_CODE

$code = <<END_OF_CODE;
	return par[0]->next();
END_OF_CODE
genBFClass('next', 'NodeBuiltinNext', 1, $code, $include);


#############################################################################
####

$funcdecl = 'resetIterator(object) : object';

$include = <<END_OF_CODE;
END_OF_CODE

$code = <<END_OF_CODE;
	par[0]->resetIterator();
	return par[0];
END_OF_CODE
genBFClass('resetIterator', 'NodeBuiltinResetIterator', 1, $code, $include);


#############################################################################
####

$funcdecl = 'array(int|bool|float) : array|null';

$include = <<END_OF_CODE;
#include "valuearray.hpp"
#include "valuebool.hpp"
#include "valueint.hpp"
#include "valuefloat.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueBool* b = NULL;
	ValueInt* i = NULL;
	ValueFloat* f = NULL;

	if((b = par[0]->toValueBool()) != NULL)
		return CountPtr<Value>(new ValueArray(b->getVal()));
	if((i = par[0]->toValueInt()) != NULL)
		return CountPtr<Value>(new ValueArray(i->getVal()));
	if((f = par[0]->toValueFloat()) != NULL)
		return CountPtr<Value>(new ValueArray((uint)f->getVal()));
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('array', 'NodeBuiltinArray', 1, $code, $include);


#############################################################################
####

$funcdecl = 'struct() : struct';

genBFClass('struct', 'NodeBuiltinStruct', 0, "\treturn CountPtr<Value>(new ValueStruct);", "#include \"valuestruct.hpp\"");


#############################################################################
####

$funcdecl = 'size(array|string) : int|null';

$include = <<END_OF_CODE;
#include "valuearray.hpp"
#include "valuestring.hpp"
#include "valueint.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueArray* a = NULL;
	ValueString* s = NULL;

	if((a = par[0]->toValueArray()) != NULL)
		return CountPtr<Value>(new ValueInt(a->getSize()));
	if((s = par[0]->toValueString()) != NULL)
		return CountPtr<Value>(new ValueInt(s->getSize()));
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('size', 'NodeBuiltinSize', 1, $code, $include);


#############################################################################
####

$funcdecl = 'pushFront(array, object) : null';

$include = <<END_OF_CODE;
#include "valuearray.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueArray* a = NULL;

	if((a = par[0]->toValueArray()) != NULL)
	{
		a->pushFront(par[1]);
		return VALUENULL;
	}
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('pushFront', 'NodeBuiltinPushFront', 2, $code, $include);


#############################################################################
####

$funcdecl = 'pushBack(array, object) : null';

$include = <<END_OF_CODE;
#include "valuearray.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueArray* a = NULL;

	if((a = par[0]->toValueArray()) != NULL)
	{
		a->pushBack(par[1]);
		return VALUENULL;
	}
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('pushBack', 'NodeBuiltinPushBack', 2, $code, $include);


#############################################################################
####

$funcdecl = 'popFront(array) : null';

$include = <<END_OF_CODE;
#include "valuearray.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueArray* a = NULL;

	if((a = par[0]->toValueArray()) != NULL)
	{
		a->popFront();
		return VALUENULL;
	}
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('popFront', 'NodeBuiltinPopFront', 1, $code, $include);


#############################################################################
####

$funcdecl = 'popBack(array) : null';

$include = <<END_OF_CODE;
#include "valuearray.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueArray* a = NULL;

	if((a = par[0]->toValueArray()) != NULL)
	{
		a->popBack();
		return VALUENULL;
	}
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('popBack', 'NodeBuiltinPopBack', 1, $code, $include);


#############################################################################
####

$funcdecl = 'back(array) : object|null';

$include = <<END_OF_CODE;
#include "valuearray.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueArray* a = NULL;

	if((a = par[0]->toValueArray()) != NULL)
		return a->back();
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('back', 'NodeBuiltinBack', 1, $code, $include);


#############################################################################
####

$funcdecl = 'front(array) : object|null';

$include = <<END_OF_CODE;
#include "valuearray.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueArray* a = NULL;

	if((a = par[0]->toValueArray()) != NULL)
		return a->front();
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('front', 'NodeBuiltinFront', 1, $code, $include);


#############################################################################
####

$funcdecl = 'graph() : graph';

genBFClass('graph', 'NodeBuiltinGraph', 0, "\treturn CountPtr<Value>(new ValueGraph);", "#include \"valuegraph.hpp\"");


#############################################################################
####

$funcdecl = 'loadFromFile(graph, string) : bool';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
#include "valuestring.hpp"
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;
	ValueString* path = NULL;

	if((g = par[0]->toValueGraph()) != NULL && (path = par[1]->toValueString()) != NULL)
		return g->loadFromFile(path->getVal()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUEBOOL_FALSE;
	}
END_OF_CODE
genBFClass('loadFromFile', 'NodeBuiltinLoadFromFile', 2, $code, $include);


#############################################################################
####

$funcdecl = 'vertexset(graph) : vertexset|null';

$include = <<END_OF_CODE;
#include "valuevertexset.hpp"
#include "valuegraph.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
		return CountPtr<Value>(new ValueVertexSet(g));
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('vertexset', 'NodeBuiltinVertexSet', 1, $code, $include);


#############################################################################
####

$funcdecl = 'edgeset(graph) : edgeset|null';

$include = <<END_OF_CODE;
#include "valueedgeset.hpp"
#include "valuegraph.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
		return CountPtr<Value>(new ValueEdgeSet(g));
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('edgeset', 'NodeBuiltinEdgeSet', 1, $code, $include);


#############################################################################
####

$funcdecl = 'isOriented(graph) : bool|null';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
#include "valuegraph.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
		return CountPtr<Value>((g->isOriented()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE);
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('isOriented', 'NodeBuiltinIsOriented', 1, $code, $include);


#############################################################################
####

$funcdecl = 'setOriented(graph, bool|int) : bool|null';

$include = <<END_OF_CODE;
#include "valuebool.hpp"
#include "valueint.hpp"
#include "valuegraph.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;
	ValueBool* b = NULL;
	ValueInt* i = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
	{
		if((b = par[1]->toValueBool()) != NULL)
			return CountPtr<Value>((g->setOriented(b->getVal())) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE);
		if((i = par[1]->toValueInt()) != NULL)
			return CountPtr<Value>((g->setOriented(i->getVal())) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE);
		else
		{
			WARN_P(_("Bad parameters type: $funcdecl"));
			return VALUENULL;
		}
	}
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('setOriented', 'NodeBuiltinSetOriented', 2, $code, $include);


#############################################################################
####

$funcdecl = 'invertEdgesOrientation(graph) : null';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
	{
		g->invertEdgesOrientation();
		return VALUENULL;
	}
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('invertEdgesOrientation', 'NodeBuiltinInvertEdgesOrientation', 1, $code, $include);


#############################################################################
####

$funcdecl = 'generateVertex(graph) : vertex|null';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
#include "valuevertex.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
	{
		CountPtr<Value> ret(g->generateVertex());
		ret.dontDeleteAutomatically();
		return ret;
	}
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('generateVertex', 'NodeBuiltinGenerateVertex', 1, $code, $include);


#############################################################################
####

$funcdecl = 'generateEdge(graph, vertex, vertex) : edge|null';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
#include "valuevertex.hpp"
#include "valueedge.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;
	ValueVertex* v1 = NULL;
	ValueVertex* v2 = NULL;

	if((g = par[0]->toValueGraph()) != NULL && (v1 = par[1]->toValueVertex()) != NULL && (v2 = par[2]->toValueVertex()) != NULL)
	{
		ValueEdge* tmp = g->generateEdge(v1, v2);
		if(tmp == NULL)
			return VALUENULL;

		CountPtr<Value> ret(tmp);
		ret.dontDeleteAutomatically();
		return ret;
	}
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('generateEdge', 'NodeBuiltinGenerateEdge', 3, $code, $include);


#############################################################################
####

$funcdecl = 'deleteVertex(graph|vertexset, vertex) : null';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
#include "valuevertex.hpp"
#include "valuevertexset.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;
	ValueVertex* v = NULL;
	ValueVertexSet* vs = NULL;

	if((g = par[0]->toValueGraph()) != NULL && (v = par[1]->toValueVertex()) != NULL)
	{
		g->deleteVertex(v);
		return VALUENULL;
	}
	else if((vs = par[0]->toValueVertexSet()) != NULL && (v = par[1]->toValueVertex()) != NULL)
	{
		vs->deleteVertex(v);
		return VALUENULL;
	}
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('deleteVertex', 'NodeBuiltinDeleteVertex', 2, $code, $include);


#############################################################################
####

$funcdecl = 'deleteEdge(graph|edgeset, edge) : null';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
#include "valueedge.hpp"
#include "valueedgeset.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;
	ValueEdge* e = NULL;
	ValueEdgeSet* es = NULL;

	if((g = par[0]->toValueGraph()) != NULL && (e = par[1]->toValueEdge()) != NULL)
	{
		g->deleteEdge(e);
		return VALUENULL;
	}
	else if((es = par[0]->toValueEdgeSet()) != NULL && (e = par[1]->toValueEdge()) != NULL)
	{
		es->deleteEdge(e);
		return VALUENULL;
	}
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('deleteEdge', 'NodeBuiltinDeleteEdge', 2, $code, $include);


#############################################################################
####

$funcdecl = 'getNumVertices(graph|vertexset) : int|null';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
#include "valuevertexset.hpp"
#include "valueint.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;
	ValueVertexSet* vs = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
		return CountPtr<Value>(new ValueInt(g->getNumVertices()));
	else if((vs = par[0]->toValueVertexSet()) != NULL)
		return CountPtr<Value>(new ValueInt(vs->getNumVertices()));
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('getNumVertices', 'NodeBuiltinGetNumVertices', 1, $code, $include);


#############################################################################
####

$funcdecl = 'getNumEdges(graph|edgeset) : int|null';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
#include "valueedgeset.hpp"
#include "valueint.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;
	ValueEdgeSet* es = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
		return CountPtr<Value>(new ValueInt(g->getNumEdges()));
	else if((es = par[0]->toValueEdgeSet()) != NULL)
		return CountPtr<Value>(new ValueInt(es->getNumEdges()));
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('getNumEdges', 'NodeBuiltinGetNumEdges', 1, $code, $include);


#############################################################################
####

$funcdecl = 'getVertices(graph) : vertexset|null';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
		return g->getVertices();
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('getVertices', 'NodeBuiltinGetVertices', 1, $code, $include);


#############################################################################
####

$funcdecl = 'getEdges(graph) : edgeset|null';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
		return g->getEdges();
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('getEdges', 'NodeBuiltinGetEdges', 1, $code, $include);


#############################################################################
####

$funcdecl = 'getDegree(vertex) : int|null';

$include = <<END_OF_CODE;
#include "valuevertex.hpp"
#include "valueint.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueVertex* v = NULL;

	if((v = par[0]->toValueVertex()) != NULL)
		return CountPtr<Value>(new ValueInt(v->getDegree()));
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('getDegree', 'NodeBuiltinGetDegree', 1, $code, $include);


#############################################################################
####

$funcdecl = 'getNeighbors(vertex) : vertexset|null';

$include = <<END_OF_CODE;
#include "valuevertex.hpp"
#include "valuevertexset.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueVertex* v = NULL;

	if((v = par[0]->toValueVertex()) != NULL)
		return CountPtr<Value>(v->getNeighbors());
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('getNeighbors', 'NodeBuiltinGetNeighbors', 1, $code, $include);


#############################################################################
####

$funcdecl = 'getBeginVertex(edge) : vertex|null';

$include = <<END_OF_CODE;
#include "valueedge.hpp"
#include "valuevertex.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueEdge* e = NULL;

	if((e = par[0]->toValueEdge()) != NULL)
	{
		CountPtr<Value> ret(e->getBeginVertex());
		ret.dontDeleteAutomatically();
		return ret;
	}
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('getBeginVertex', 'NodeBuiltinGetBeginVertex', 1, $code, $include);


#############################################################################
####

$funcdecl = 'getEndVertex(edge) : vertex|null';

$include = <<END_OF_CODE;
#include "valueedge.hpp"
#include "valuevertex.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueEdge* e = NULL;

	if((e = par[0]->toValueEdge()) != NULL)
	{
		CountPtr<Value> ret(e->getEndVertex());
		ret.dontDeleteAutomatically();
		return ret;
	}
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('getEndVertex', 'NodeBuiltinGetEndVertex', 1, $code, $include);


#############################################################################
####

$funcdecl = 'add(vertexset|edgeset, vertex|edge) : null';

$include = <<END_OF_CODE;
#include "valuevertexset.hpp"
#include "valuevertex.hpp"
#include "valueedgeset.hpp"
#include "valueedge.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueVertexSet* vs = NULL;
	ValueVertex* v = NULL;
	ValueEdgeSet* es = NULL;
	ValueEdge* e = NULL;

	if((vs = par[0]->toValueVertexSet()) != NULL && (v = par[1]->toValueVertex()) != NULL)
	{
		vs->addVertex(v);
		return VALUENULL;
	}
	else if((es = par[0]->toValueEdgeSet()) != NULL && (e = par[1]->toValueEdge()) != NULL)
	{
		es->addEdge(e);
		return VALUENULL;
	}
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('add', 'NodeBuiltinAdd', 2, $code, $include);


#############################################################################
####

$funcdecl = 'contains(graph|vertexset|edgeset, vertex|edge) : bool|null';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
#include "valuevertexset.hpp"
#include "valueedgeset.hpp"
#include "valuevertex.hpp"
#include "valueedge.hpp"
#include "valuebool.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;
	ValueVertex* v = NULL;
	ValueEdge* e = NULL;
	ValueVertexSet* vs = NULL;
	ValueEdgeSet* es = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
	{
		if((v = par[1]->toValueVertex()) != NULL)
			return CountPtr<Value>((g->contains(v)) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE);
		else if((e = par[1]->toValueEdge()) != NULL)
			return CountPtr<Value>((g->contains(e)) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE);
		else
		{
			WARN_P(_("Bad parameters type: $funcdecl"));
			return VALUENULL;
		}
	}
	else if((vs = par[0]->toValueVertexSet()) != NULL && (v = par[1]->toValueVertex()) != NULL)
		return CountPtr<Value>((vs->contains(v)) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE);
	else if((es = par[0]->toValueEdgeSet()) != NULL && (e = par[1]->toValueEdge()) != NULL)
		return CountPtr<Value>((es->contains(e)) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE);
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('contains', 'NodeBuiltinContains', 2, $code, $include);


#############################################################################
####

$funcdecl = 'union(vertexset|edgeset, vertexset|edgeset) : vertexset|edgeset|null';

$include = <<END_OF_CODE;
#include "valuevertexset.hpp"
#include "valueedgeset.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueVertexSet* vs1 = NULL;
	ValueVertexSet* vs2 = NULL;
	ValueEdgeSet* es1 = NULL;
	ValueEdgeSet* es2 = NULL;

	if((vs1 = par[0]->toValueVertexSet()) != NULL && (vs2 = par[1]->toValueVertexSet()) != NULL)
		return vs1->getUnion(*vs2);
	else if((es1 = par[0]->toValueEdgeSet()) != NULL && (es2 = par[1]->toValueEdgeSet()) != NULL)
		return es1->getUnion(*es2);
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('union', 'NodeBuiltinUnion', 2, $code, $include);


#############################################################################
####

$funcdecl = 'intersection(vertexset|edgeset, vertexset|edgeset) : vertexset|edgeset|null';

$include = <<END_OF_CODE;
#include "valuevertexset.hpp"
#include "valueedgeset.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueVertexSet* vs1 = NULL;
	ValueVertexSet* vs2 = NULL;
	ValueEdgeSet* es1 = NULL;
	ValueEdgeSet* es2 = NULL;

	if((vs1 = par[0]->toValueVertexSet()) != NULL && (vs2 = par[1]->toValueVertexSet()) != NULL)
		return vs1->getIntersection(*vs2);
	else if((es1 = par[0]->toValueEdgeSet()) != NULL && (es2 = par[1]->toValueEdgeSet()) != NULL)
		return es1->getIntersection(*es2);
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('intersection', 'NodeBuiltinIntersection', 2, $code, $include);


#############################################################################
####

$funcdecl = 'difference(vertexset|edgeset, vertexset|edgeset) : vertexset|edgeset|null';

$include = <<END_OF_CODE;
#include "valuevertexset.hpp"
#include "valueedgeset.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueVertexSet* vs1 = NULL;
	ValueVertexSet* vs2 = NULL;
	ValueEdgeSet* es1 = NULL;
	ValueEdgeSet* es2 = NULL;

	if((vs1 = par[0]->toValueVertexSet()) != NULL && (vs2 = par[1]->toValueVertexSet()) != NULL)
		return vs1->getDifference(*vs2);
	else if((es1 = par[0]->toValueEdgeSet()) != NULL && (es2 = par[1]->toValueEdgeSet()) != NULL)
		return es1->getDifference(*es2);
	else
	{
		WARN_P(_("Bad parameters type: $funcdecl"));
		return VALUENULL;
	}
END_OF_CODE
genBFClass('difference', 'NodeBuiltinDifference', 2, $code, $include);


#############################################################################
####

$funcdecl = 'visRegister(vertexset|edgeset, string, number, number, number) : null';

$include = <<END_OF_CODE;
#include "objectcreator.hpp"
#include "visualizationconnector.hpp"
#include "valuestring.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueString* name = NULL;

	if((par[0]->toValueVertexSet() != NULL || par[0]->toValueEdgeSet() != NULL)
			&& (name = par[1]->toValueString()) != NULL
			&& par[2]->isNumeric()
			&& par[3]->isNumeric()
			&& par[4]->isNumeric())
		VISUALIZATION_CONNECTOR->visRegister(par[0], name->getVal(), par[2]->toInt(), par[3]->toInt(), par[4]->toInt());
	else
		WARN_P(_("Bad parameters type: $funcdecl"));

	return VALUENULL;
END_OF_CODE
genBFClass('visRegister', 'NodeBuiltinVisRegister', 5, $code, $include);


#############################################################################
####

$funcdecl = 'visSetPos(vertex, number, number, number) : null';

$include = <<END_OF_CODE;
#include "objectcreator.hpp"
#include "visualizationconnector.hpp"
#include "valuevertex.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueVertex* v = NULL;

	if((v = par[0]->toValueVertex()) != NULL
			&& par[1]->isNumeric()
			&& par[2]->isNumeric()
			&& par[3]->isNumeric())
	{
		v->setItem(STR2ID("__x"), par[1]);
		v->setItem(STR2ID("__y"), par[2]);
		v->setItem(STR2ID("__z"), par[3]);
		VISUALIZATION_CONNECTOR->repaintVisualization();
	}
	else
		WARN_P(_("Bad parameters type: $funcdecl"));

	return VALUENULL;
END_OF_CODE
genBFClass('visSetPos', 'NodeBuiltinVisSetPos', 4, $code, $include);


#############################################################################
####

$funcdecl = 'visSetColor(vertex|edge, number, number, number) : null';

$include = <<END_OF_CODE;
#include "objectcreator.hpp"
#include "visualizationconnector.hpp"
#include "valuevertex.hpp"
#include "valueedge.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueVertex* v = NULL;
	ValueEdge*   e = NULL;

	if((v = par[0]->toValueVertex()) != NULL
			&& par[1]->isNumeric()
			&& par[2]->isNumeric()
			&& par[3]->isNumeric())
	{
		v->setItem(STR2ID("__r"), par[1]);
		v->setItem(STR2ID("__g"), par[2]);
		v->setItem(STR2ID("__b"), par[3]);
		VISUALIZATION_CONNECTOR->repaintVisualization();
	}
	else if((e = par[0]->toValueEdge()) != NULL
			&& par[1]->isNumeric()
			&& par[2]->isNumeric()
			&& par[3]->isNumeric())
	{
		e->setItem(STR2ID("__r"), par[1]);
		e->setItem(STR2ID("__g"), par[2]);
		e->setItem(STR2ID("__b"), par[3]);
		VISUALIZATION_CONNECTOR->repaintVisualization();
	}
	else
		WARN_P(_("Bad parameters type: $funcdecl"));

	return VALUENULL;
END_OF_CODE
genBFClass('visSetColor', 'NodeBuiltinVisSetColor', 4, $code, $include);


#############################################################################
####

print "Generating generateBuiltinFunctions()\n";

open(FILE_HPP, ">nodebuiltin_inst.hpp") or die "Cannot open output file: nodebuiltin_inst.hpp\n";
print FILE_HPP "$fileheader\nvoid generateBuiltinFunctions(void);\n";
close FILE_HPP;

open(FILE_CPP, ">nodebuiltin_inst.cpp") or die "Cannot open output file: nodebuiltin_inst.cpp\n";
print FILE_CPP "$fileheader\n$instantiate_inc\n$instantiate}\n";
close FILE_CPP;

0;
