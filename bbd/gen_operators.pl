#!/usr/bin/perl -w

sub generateUnaryOperatorClass
{
	my ($classname, $operation) = @_;

	my $hpp_filename = lc($classname).'.hpp';
	my $cpp_filename = lc($classname).'.cpp';
	my $hpp_define = uc($classname).'_HPP';

	my $hpp_code = <<END_OF_HPP;
/*
 *      $hpp_filename
 *
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
 *               This class was generated by gen_operators.pl               *
 *                           Don't update directly                          *
 *                                                                          *
 ****************************************************************************/

#ifndef $hpp_define
#define $hpp_define

#include "general.hpp"
#include "nodeunary.hpp"

class $classname : public NodeUnary
{
public:
	$classname(Node* next);
	virtual ~$classname(void);

	virtual string toString(void) const { return "$classname"; }

	virtual PTR_Value execute(Context& context);
	virtual void dump(ostream& os, uint indent) const;

private:
	$classname(void);
	$classname(const $classname& object);
	$classname& operator=(const $classname& object);
};

ostream& operator<<(ostream& os, const $classname& node);

#endif /* $hpp_define */

END_OF_HPP


	my $cpp_code = <<END_OF_CPP;
/*
 *      $cpp_filename
 *
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
 *               This class was generated by gen_operators.pl               *
 *                           Don't update directly                          *
 *                                                                          *
 ****************************************************************************/

#include "$hpp_filename"
#include "context.hpp"
#include "value.hpp"


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


PTR_Value $classname\::execute(Context& context)
{
	$operation
}


/////////////////////////////////////////////////////////////////////////////
////

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

	open(FILE_HPP, ">$hpp_filename") or die "Cannot open output file: $hpp_filename\n";
	print FILE_HPP $hpp_code;
	close FILE_HPP;

	open(FILE_CPP, ">$cpp_filename") or die "Cannot open output file: $cpp_filename\n";
	print FILE_CPP $cpp_code;
	close FILE_CPP;
}


sub generateBinaryOperatorClass
{
	my ($classname, $operation) = @_;

	my $hpp_filename = lc($classname).'.hpp';
	my $cpp_filename = lc($classname).'.cpp';
	my $hpp_define = uc($classname).'_HPP';

	my $hpp_code = <<END_OF_HPP;
/*
 *      $hpp_filename
 *
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
 *               This class was generated by gen_operators.pl               *
 *                           Don't update directly                          *
 *                                                                          *
 ****************************************************************************/

#ifndef $hpp_define
#define $hpp_define

#include "general.hpp"
#include "nodebinary.hpp"

class $classname : public NodeBinary
{
public:
	$classname(Node* left, Node* right);
	virtual ~$classname(void);

	virtual string toString(void) const { return "$classname"; }

	virtual PTR_Value execute(Context& context);
	virtual void dump(ostream& os, uint indent) const;

private:
	$classname(void);
	$classname(const $classname& object);
	$classname& operator=(const $classname& object);
};

ostream& operator<<(ostream& os, const $classname& node);

#endif /* $hpp_define */

END_OF_HPP


	my $cpp_code = <<END_OF_CPP;
/*
 *      $cpp_filename
 *
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
 *               This class was generated by gen_operators.pl               *
 *                           Don't update directly                          *
 *                                                                          *
 ****************************************************************************/

#include "$hpp_filename"
#include "context.hpp"
#include "value.hpp"


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


PTR_Value $classname\::execute(Context& context)
{
	$operation
}


/////////////////////////////////////////////////////////////////////////////
////

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

	open(FILE_HPP, ">$hpp_filename") or die "Cannot open output file: $hpp_filename\n";
	print FILE_HPP $hpp_code;
	close FILE_HPP;

	open(FILE_CPP, ">$cpp_filename") or die "Cannot open output file: $cpp_filename\n";
	print FILE_CPP $cpp_code;
	close FILE_CPP;
}


generateUnaryOperatorClass('NodeUnarySub', 'return m_next->execute(context)->subUn();');
generateUnaryOperatorClass('NodeUnaryNot', 'return m_next->execute(context)->logNOT();');

generateBinaryOperatorClass('NodeBinaryAdd', 'return m_left->execute(context)->add(*(m_right->execute(context)));');
generateBinaryOperatorClass('NodeBinarySub', 'return m_left->execute(context)->sub(*(m_right->execute(context)));');
generateBinaryOperatorClass('NodeBinaryMult', 'return m_left->execute(context)->mult(*(m_right->execute(context)));');
generateBinaryOperatorClass('NodeBinaryDiv', 'return m_left->execute(context)->div(*(m_right->execute(context)));');
generateBinaryOperatorClass('NodeBinaryMod', 'return m_left->execute(context)->mod(*(m_right->execute(context)));');
generateBinaryOperatorClass('NodeBinaryEq', 'return m_left->execute(context)->eq(*(m_right->execute(context)));');
generateBinaryOperatorClass('NodeBinaryNe', 'return m_left->execute(context)->ne(*(m_right->execute(context)));');
generateBinaryOperatorClass('NodeBinaryLe', 'return m_left->execute(context)->le(*(m_right->execute(context)));');
generateBinaryOperatorClass('NodeBinaryGe', 'return m_left->execute(context)->ge(*(m_right->execute(context)));');
generateBinaryOperatorClass('NodeBinaryLt', 'return m_left->execute(context)->lt(*(m_right->execute(context)));');
generateBinaryOperatorClass('NodeBinaryGt', 'return m_left->execute(context)->gt(*(m_right->execute(context)));');
generateBinaryOperatorClass('NodeBinaryAnd', 'return m_left->execute(context)->logAND(*(m_right->execute(context)));');
generateBinaryOperatorClass('NodeBinaryOr', 'return m_left->execute(context)->logOR(*(m_right->execute(context)));');

0;
