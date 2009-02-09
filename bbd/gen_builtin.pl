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

	list<identifier>::iterator p0 = params.begin();
	list<identifier>::iterator p1 = ++p0;
	list<identifier>::iterator p2 = ++p0;
	list<identifier>::iterator p3 = ++p0;
	list<identifier>::iterator p4 = ++p0;
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

$funcdecl = 'echo(object)';

$code = <<END_OF_CODE;
	SCRIPT_STDOUT << par[0]->toString();
	return par[0];
END_OF_CODE
genBFClass('echo', 'NodeBuiltinEcho', 1, $code);


#############################################################################
####

$funcdecl = 'dump(object)';

$code = <<END_OF_CODE;
	par[0]->dump(SCRIPT_STDOUT, 0);
	return par[0];
END_OF_CODE
genBFClass('dump', 'NodeBuiltinDump', 1, $code);


#############################################################################
####

$funcdecl = 'exit(object)';

$include = <<END_OF_CODE;
#include "exitvalue.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	throw ExitValue(par[0]);

	// It will never be called
	return VALUENULL;
END_OF_CODE
genBFClass('exit', 'NodeBuiltinExit', 1, $code, $include);


#############################################################################
####

$funcdecl = 'assert(object)';

$include = <<END_OF_CODE;
#include <stdexcept>
END_OF_CODE

$code = <<END_OF_CODE;
	if(!par[0]->toBool())
		throw runtime_error(_("Assertion failed"));

	// It will never be called
	return VALUENULL;
END_OF_CODE
genBFClass('assert', 'NodeBuiltinAssert', 1, $code, $include);


#############################################################################
####

$funcdecl = 'verify(object)';

$include = <<END_OF_CODE;
#include <stdexcept>
END_OF_CODE

$code = <<END_OF_CODE;
	if(!par[0]->toBool())
		WARN << _("Verify: Operation was not successful") << endl;

	// It will never be called
	return VALUENULL;
END_OF_CODE
genBFClass('verify', 'NodeBuiltinVerify', 1, $code, $include);


#############################################################################
####

$funcdecl = 'array(int|bool|float)';

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
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return VALUENULL;
	}
END_OF_CODE
genBFClass('array', 'NodeBuiltinArray', 1, $code, $include);


#############################################################################
####

$funcdecl = 'struct()';

genBFClass('struct', 'NodeBuiltinStruct', 0, "\treturn CountPtr<Value>(new ValueStruct());", "#include \"valuestruct.hpp\"");


#############################################################################
####

$funcdecl = 'size(array|string)';

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
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return CountPtr<Value>(VALUENULL);
	}
END_OF_CODE
genBFClass('size', 'NodeBuiltinSize', 1, $code, $include);


#############################################################################
####

$funcdecl = 'graph()';

genBFClass('graph', 'NodeBuiltinGraph', 0, "\treturn CountPtr<Value>(new ValueGraph());", "#include \"valuegraph.hpp\"");


#############################################################################
####

$funcdecl = 'isOriented(graph)';

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
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return CountPtr<Value>(VALUENULL);
	}
END_OF_CODE
genBFClass('isOriented', 'NodeBuiltinIsOriented', 1, $code, $include);


#############################################################################
####

$funcdecl = 'setOriented(graph, bool|int)';

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
			WARN << _("Bad parameters type: $funcdecl") << endl;
			return CountPtr<Value>(VALUENULL);
		}
	}
	else
	{
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return CountPtr<Value>(VALUENULL);
	}
END_OF_CODE
genBFClass('setOriented', 'NodeBuiltinSetOriented', 2, $code, $include);


#############################################################################
####

$funcdecl = 'invertEdgesOrientation(graph)';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
	{
		g->invertEdgesOrientation();
		return CountPtr<Value>(VALUENULL);
	}
	else
	{
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return CountPtr<Value>(VALUENULL);
	}
END_OF_CODE
genBFClass('invertEdgesOrientation', 'NodeBuiltinInvertEdgesOrientation', 1, $code, $include);


#############################################################################
####

$funcdecl = 'addVertex(graph)';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
#include "valuevertex.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
	{
		CountPtr<Value> ret(g->addVertex());
		ret.dontDeleteAutomatically();
		return ret;
	}
	else
	{
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return CountPtr<Value>(VALUENULL);
	}
END_OF_CODE
genBFClass('addVertex', 'NodeBuiltinAddVertex', 1, $code, $include);


#############################################################################
####

$funcdecl = 'addEdge(graph, vertex, vertex)';

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
		ValueEdge* tmp = g->addEdge(v1, v2);
		if(tmp == NULL)
			return CountPtr<Value>(VALUENULL);

		CountPtr<Value> ret(tmp);
		ret.dontDeleteAutomatically();
		return ret;
	}
	else
	{
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return CountPtr<Value>(VALUENULL);
	}
END_OF_CODE
genBFClass('addEdge', 'NodeBuiltinAddEdge', 3, $code, $include);


#############################################################################
####

$funcdecl = 'deleteVertex(graph, vertex)';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
#include "valuevertex.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;
	ValueVertex* v = NULL;

	if((g = par[0]->toValueGraph()) != NULL && (v = par[1]->toValueVertex()) != NULL)
	{
		g->deleteVertex(v);
		return CountPtr<Value>(VALUENULL);
	}
	else
	{
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return CountPtr<Value>(VALUENULL);
	}
END_OF_CODE
genBFClass('deleteVertex', 'NodeBuiltinDeleteVertex', 2, $code, $include);


#############################################################################
####

$funcdecl = 'deleteEdge(graph, edge)';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
#include "valueedge.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;
	ValueEdge* e = NULL;

	if((g = par[0]->toValueGraph()) != NULL && (e = par[1]->toValueEdge()) != NULL)
	{
		g->deleteEdge(e);
		return CountPtr<Value>(VALUENULL);
	}
	else
	{
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return CountPtr<Value>(VALUENULL);
	}
END_OF_CODE
genBFClass('deleteEdge', 'NodeBuiltinDeleteEdge', 2, $code, $include);


#############################################################################
####

$funcdecl = 'getNumVertices(graph)';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
#include "valueint.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
	{
		return CountPtr<Value>(new ValueInt(g->getNumVertices()));
	}
	else
	{
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return CountPtr<Value>(VALUENULL);
	}
END_OF_CODE
genBFClass('getNumVertices', 'NodeBuiltinGetNumVertices', 1, $code, $include);


#############################################################################
####

$funcdecl = 'getNumEdges(graph)';

$include = <<END_OF_CODE;
#include "valuegraph.hpp"
#include "valueint.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueGraph* g = NULL;

	if((g = par[0]->toValueGraph()) != NULL)
	{
		return CountPtr<Value>(new ValueInt(g->getNumEdges()));
	}
	else
	{
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return CountPtr<Value>(VALUENULL);
	}
END_OF_CODE
genBFClass('getNumEdges', 'NodeBuiltinGetNumEdges', 1, $code, $include);


#############################################################################
####

$funcdecl = 'getDegree(vertex)';

$include = <<END_OF_CODE;
#include "valuevertex.hpp"
#include "valueint.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueVertex* v = NULL;

	if((v = par[0]->toValueVertex()) != NULL)
	{
		return CountPtr<Value>(new ValueInt(v->getDegree()));
	}
	else
	{
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return CountPtr<Value>(VALUENULL);
	}
END_OF_CODE
genBFClass('getDegree', 'NodeBuiltinGetDegree', 1, $code, $include);


#############################################################################
####

$funcdecl = 'getNeighbors(vertex)';

$include = <<END_OF_CODE;
#include "valuevertex.hpp"
#include "valuevertexset.hpp"
END_OF_CODE

$code = <<END_OF_CODE;
	ValueVertex* v = NULL;

	if((v = par[0]->toValueVertex()) != NULL)
	{
		return CountPtr<Value>(v->getNeighbors());
	}
	else
	{
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return CountPtr<Value>(VALUENULL);
	}
END_OF_CODE
genBFClass('getNeighbors', 'NodeBuiltinGetNeighbors', 1, $code, $include);


#############################################################################
####

$funcdecl = 'getBeginVertex(edge)';

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
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return CountPtr<Value>(VALUENULL);
	}
END_OF_CODE
genBFClass('getBeginVertex', 'NodeBuiltinGetBeginVertex', 1, $code, $include);


#############################################################################
####

$funcdecl = 'getEndVertex(edge)';

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
		WARN << _("Bad parameters type: $funcdecl") << endl;
		return CountPtr<Value>(VALUENULL);
	}
END_OF_CODE
genBFClass('getEndVertex', 'NodeBuiltinGetEndVertex', 1, $code, $include);


#############################################################################

print "Generating generateBuiltinFunctions()\n";

open(FILE_HPP, ">nodebuiltin_inst.hpp") or die "Cannot open output file: nodebuiltin_inst.hpp\n";
print FILE_HPP "$fileheader\nvoid generateBuiltinFunctions(void);\n";
close FILE_HPP;

open(FILE_CPP, ">nodebuiltin_inst.cpp") or die "Cannot open output file: nodebuiltin_inst.cpp\n";
print FILE_CPP "$fileheader\n$instantiate_inc\n$instantiate}\n";
close FILE_CPP;

0;
