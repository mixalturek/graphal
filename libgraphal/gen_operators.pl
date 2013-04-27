#!/usr/bin/perl -w

sub generateUnaryOperatorClass
{
	my ($classname, $operation, $include) = @_;
	$include = '' if(!defined $include);

	my $hpp_filename = 'generated/'.lc($classname).'.h';
	my $cpp_filename = 'generated/'.lc($classname).'.cpp';
	my $hpp_define = uc($classname).'_H';

	my $hpp_code = <<END_OF_H;
/*
 *      Copyright 2008 Michal Turek <http://woq.nipax.cz/>
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
 *           This file was generated by gen_operators.pl script.            *
 *                        Don't update it manually!                         *
 *                                                                          *
 ****************************************************************************/

#ifndef $hpp_define
#define $hpp_define

#include "general.h"
#include "nodeunary.h"

class $classname : public NodeUnary
{
public:
	$classname(Node* next);
	virtual ~$classname(void);

	virtual CountPtr<Value> execute(void);
	virtual void dump(ostream& os, uint indent) const;

private:
	$classname(void);
	$classname(const $classname& object);
	$classname& operator=(const $classname& object);
};

ostream& operator<<(ostream& os, const $classname& node);

#endif /* $hpp_define */

END_OF_H


	my $cpp_code = <<END_OF_CPP;
/*
 *      Copyright 2008 Michal Turek <http://woq.nipax.cz/>
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
 *           This file was generated by gen_operators.pl script.            *
 *                        Don't update it manually!                         *
 *                                                                          *
 ****************************************************************************/
$include
#include "$hpp_filename"
#include "value.h"


/////////////////////////////////////////////////////////////////////////////
////

$classname\::$classname(Node* next)
	: NodeUnary(next)
{

}

$classname\::~$classname(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////


CountPtr<Value> $classname\::execute(void)
{
	$operation
}

void $classname\::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<$classname>" << endl;

	m_next->dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</$classname>" << endl;
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

	open(FILE_H, ">$hpp_filename") or die "Cannot open output file: $hpp_filename\n";
	print FILE_H $hpp_code;
	close FILE_H;

	open(FILE_CPP, ">$cpp_filename") or die "Cannot open output file: $cpp_filename\n";
	print FILE_CPP $cpp_code;
	close FILE_CPP;
}


sub generateBinaryOperatorClass
{
	my ($classname, $operation, $include) = @_;
	$include = '' if(!defined $include);

	my $hpp_filename = 'generated/'.lc($classname).'.h';
	my $cpp_filename = 'generated/'.lc($classname).'.cpp';
	my $hpp_define = uc($classname).'_H';

	my $hpp_code = <<END_OF_H;
/*
 *      Copyright 2008 Michal Turek <http://woq.nipax.cz/>
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
 *           This file was generated by gen_operators.pl script.            *
 *                        Don't update it manually!                         *
 *                                                                          *
 ****************************************************************************/

#ifndef $hpp_define
#define $hpp_define

#include "general.h"
#include "nodebinary.h"

class $classname : public NodeBinary
{
public:
	$classname(Node* left, Node* right);
	virtual ~$classname(void);

	virtual CountPtr<Value> execute(void);
	virtual void dump(ostream& os, uint indent) const;

private:
	$classname(void);
	$classname(const $classname& object);
	$classname& operator=(const $classname& object);
};

ostream& operator<<(ostream& os, const $classname& node);

#endif /* $hpp_define */

END_OF_H


	my $cpp_code = <<END_OF_CPP;
/*
 *      Copyright 2008 Michal Turek <http://woq.nipax.cz/>
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
 *           This file was generated by gen_operators.pl script.            *
 *                        Don't update it manually!                         *
 *                                                                          *
 ****************************************************************************/
$include
#include "$hpp_filename"
#include "value.h"


/////////////////////////////////////////////////////////////////////////////
////

$classname\::$classname(Node* left, Node* right)
	: NodeBinary(left, right)
{

}

$classname\::~$classname(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> $classname\::execute(void)
{
	$operation
}

void $classname\::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<$classname>" << endl;

	m_left->dump(os, indent+1);
	m_right->dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</$classname>" << endl;
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

	open(FILE_H, ">$hpp_filename") or die "Cannot open output file: $hpp_filename\n";
	print FILE_H $hpp_code;
	close FILE_H;

	open(FILE_CPP, ">$cpp_filename") or die "Cannot open output file: $cpp_filename\n";
	print FILE_CPP $cpp_code;
	close FILE_CPP;
}


generateUnaryOperatorClass('NodeUnarySub', 'return m_next->execute()->subUn();');
generateUnaryOperatorClass('NodeUnaryNot', 'return m_next->execute()->logNOT();');
generateUnaryOperatorClass('NodeUnaryReturn', 'throw m_next->execute();');

generateUnaryOperatorClass('NodeUnaryIncPre', "CountPtr<Value> tmp(m_next->execute());\n\treturn tmp->assign(tmp->add(*VALUEBOOL_TRUE));", "\n#include \"valuebool.h\"");
generateUnaryOperatorClass('NodeUnaryIncPost', "CountPtr<Value> tmp(m_next->execute());\n\tCountPtr<Value> ret(tmp->getReferredValue());\n\ttmp->assign(tmp->add(*VALUEBOOL_TRUE));\n\treturn ret;", "\n#include \"valuebool.h\"");
generateUnaryOperatorClass('NodeUnaryDecPre', "CountPtr<Value> tmp(m_next->execute());\n\treturn tmp->assign(tmp->sub(*VALUEBOOL_TRUE));", "\n#include \"valuebool.h\"");
generateUnaryOperatorClass('NodeUnaryDecPost', "CountPtr<Value> tmp(m_next->execute());\n\tCountPtr<Value> ret(tmp->getReferredValue());\n\ttmp->assign(tmp->sub(*VALUEBOOL_TRUE));\n\treturn ret;", "\n#include \"valuebool.h\"");

generateBinaryOperatorClass('NodeBinaryAdd', 'return m_left->execute()->add(*(m_right->execute()));');
generateBinaryOperatorClass('NodeBinarySub', 'return m_left->execute()->sub(*(m_right->execute()));');
generateBinaryOperatorClass('NodeBinaryMult', 'return m_left->execute()->mult(*(m_right->execute()));');
generateBinaryOperatorClass('NodeBinaryDiv', 'return m_left->execute()->div(*(m_right->execute()));');
generateBinaryOperatorClass('NodeBinaryMod', 'return m_left->execute()->mod(*(m_right->execute()));');
generateBinaryOperatorClass('NodeBinaryEq', 'return m_left->execute()->eq(*(m_right->execute()));');
generateBinaryOperatorClass('NodeBinaryNe', 'return m_left->execute()->ne(*(m_right->execute()));');
generateBinaryOperatorClass('NodeBinaryLe', 'return m_left->execute()->le(*(m_right->execute()));');
generateBinaryOperatorClass('NodeBinaryGe', 'return m_left->execute()->ge(*(m_right->execute()));');
generateBinaryOperatorClass('NodeBinaryLt', 'return m_left->execute()->lt(*(m_right->execute()));');
generateBinaryOperatorClass('NodeBinaryGt', 'return m_left->execute()->gt(*(m_right->execute()));');
generateBinaryOperatorClass('NodeBinaryAnd', 'return m_left->execute()->logAND(*(m_right->execute()));');
generateBinaryOperatorClass('NodeBinaryOr', 'return m_left->execute()->logOR(*(m_right->execute()));');
generateBinaryOperatorClass('NodeBinaryMember', 'return m_left->execute()->member(*(m_right->execute()));');
generateBinaryOperatorClass('NodeBinaryIndex', 'return m_left->execute()->index(*(m_right->execute()));');

generateBinaryOperatorClass('NodeBinaryAss', 'return m_left->execute()->assign(m_right->execute());');
generateBinaryOperatorClass('NodeBinaryAssAdd', "CountPtr<Value> tmp(m_left->execute());\n\treturn tmp->assign(tmp->add(*(m_right->execute())));");
generateBinaryOperatorClass('NodeBinaryAssSub', "CountPtr<Value> tmp(m_left->execute());\n\treturn tmp->assign(tmp->sub(*(m_right->execute())));");
generateBinaryOperatorClass('NodeBinaryAssMult', "CountPtr<Value> tmp(m_left->execute());\n\treturn tmp->assign(tmp->mult(*(m_right->execute())));");
generateBinaryOperatorClass('NodeBinaryAssDiv', "CountPtr<Value> tmp(m_left->execute());\n\treturn tmp->assign(tmp->div(*(m_right->execute())));");
generateBinaryOperatorClass('NodeBinaryAssMod', "CountPtr<Value> tmp(m_left->execute());\n\treturn tmp->assign(tmp->mod(*(m_right->execute())));");

$code = <<END_OF_CODE;
	CountPtr<Value> tmp(m_right->execute());
	ValueIdentifier* ident = tmp->toValueIdentifier();
	return m_left->execute()->assignRef((ident == NULL) ? tmp : ident->getVal());
END_OF_CODE
generateBinaryOperatorClass('NodeBinaryAssRef', $code, "\n#include \"valueidentifier.h\"");

0;
