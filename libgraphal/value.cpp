/*
 * Copyright 2008 Michal Turek
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


#include <stdexcept>
#include "value.h"
#include "valuenull.h"
#include "valuebool.h"
#include "valueint.h"
#include "valuefloat.h"
#include "valuestring.h"
#include "valuestruct.h"
#include "valuearray.h"
#include "valuereference.h"
#include "valueidentifier.h"
#include "valuegraph.h"
#include "valuevertex.h"
#include "valueedge.h"
#include "logger.h"


/////////////////////////////////////////////////////////////////////////////
////

Value::Value()
	: BaseObject()
{

}


Value::~Value()
{

}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> Value::logAND(const Value& right) const
{
	return (this->toBool() && right.toBool()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
}

CountPtr<Value> Value::logOR(const Value& right) const
{
	return (this->toBool() || right.toBool()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> Value::assign(CountPtr<Value> /* val */)
{
	ERR_P(_("L-value is required as left operand of assignment: ") + toString());
	ostringstream os;
	this->dump(os, 1);
	SCRIPT_STDOUT(os.str());

	return VALUENULL;
}

CountPtr<Value> Value::assignRef(CountPtr<Value> /* val */)
{
	ERR_P(_("L-value is required as left operand of reference assignment: ") + toString());
	ostringstream os;
	this->dump(os, 1);
	SCRIPT_STDOUT(os.str());

	return VALUENULL;
}

CountPtr<Value> Value::getReferredValue(void) const
{
	ERR_P(_("Attemp to get referred value, but the value is not reference: ") + toString());
	ostringstream os;
	this->dump(os, 1);
	SCRIPT_STDOUT(os.str());

	return VALUENULL;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> Value::iterator(void) const
{
	WARN_P(_("The value is not iterable: ") + toString());
	return VALUENULL;
}

CountPtr<Value> Value::hasNext(void) const
{
	WARN_P(_("The value is not iterable: ") + toString());
	return VALUEBOOL_FALSE;
}

CountPtr<Value> Value::next(void)
{
	WARN_P(_("The value is not iterable: ") + toString());
	return VALUENULL;
}

void Value::resetIterator(void)
{
	WARN_P(_("The value is not iterable: ") + toString());
}


/////////////////////////////////////////////////////////////////////////////
////

// +
CountPtr<Value> Value::add(const ValueNull& /* left */)       const { return VALUENULL; }
CountPtr<Value> Value::add(const ValueBool& /* left */)       const { return VALUENULL; }
CountPtr<Value> Value::add(const ValueInt& /* left */)        const { return VALUENULL; }
CountPtr<Value> Value::add(const ValueFloat& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::add(const ValueString& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::add(const ValueStruct& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::add(const ValueReference& /* left */)  const { return VALUENULL; }
CountPtr<Value> Value::add(const ValueIdentifier& /* left */) const { return VALUENULL; }
CountPtr<Value> Value::add(const ValueGraph& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::add(const ValueVertex& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::add(const ValueEdge& /* left */)       const { return VALUENULL; }
CountPtr<Value> Value::add(const ValueSet& /* left */)        const { return VALUENULL; }

// -
CountPtr<Value> Value::sub(const ValueNull& /* left */)       const { return VALUENULL; }
CountPtr<Value> Value::sub(const ValueBool& /* left */)       const { return VALUENULL; }
CountPtr<Value> Value::sub(const ValueInt& /* left */)        const { return VALUENULL; }
CountPtr<Value> Value::sub(const ValueFloat& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::sub(const ValueString& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::sub(const ValueStruct& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::sub(const ValueReference& /* left */)  const { return VALUENULL; }
CountPtr<Value> Value::sub(const ValueIdentifier& /* left */) const { return VALUENULL; }
CountPtr<Value> Value::sub(const ValueGraph& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::sub(const ValueVertex& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::sub(const ValueEdge& /* left */)       const { return VALUENULL; }
CountPtr<Value> Value::sub(const ValueSet& /* left */)        const { return VALUENULL; }

// *
CountPtr<Value> Value::mult(const ValueNull& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::mult(const ValueBool& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::mult(const ValueInt& /* left */)       const { return VALUENULL; }
CountPtr<Value> Value::mult(const ValueFloat& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::mult(const ValueString& /* left */)    const { return VALUENULL; }
CountPtr<Value> Value::mult(const ValueStruct& /* left */)    const { return VALUENULL; }
CountPtr<Value> Value::mult(const ValueReference& /* left */) const { return VALUENULL; }
CountPtr<Value> Value::mult(const ValueIdentifier& /* left */)const { return VALUENULL; }
CountPtr<Value> Value::mult(const ValueGraph& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::mult(const ValueVertex& /* left */)    const { return VALUENULL; }
CountPtr<Value> Value::mult(const ValueEdge& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::mult(const ValueSet& /* left */)       const { return VALUENULL; }

// /
CountPtr<Value> Value::div(const ValueNull& /* left */)       const { return VALUENULL; }
CountPtr<Value> Value::div(const ValueBool& /* left */)       const { return VALUENULL; }
CountPtr<Value> Value::div(const ValueInt& /* left */)        const { return VALUENULL; }
CountPtr<Value> Value::div(const ValueFloat& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::div(const ValueString& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::div(const ValueStruct& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::div(const ValueReference& /* left */)  const { return VALUENULL; }
CountPtr<Value> Value::div(const ValueIdentifier& /* left */) const { return VALUENULL; }
CountPtr<Value> Value::div(const ValueGraph& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::div(const ValueVertex& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::div(const ValueEdge& /* left */)       const { return VALUENULL; }
CountPtr<Value> Value::div(const ValueSet& /* left */)        const { return VALUENULL; }

// %
CountPtr<Value> Value::mod(const ValueNull& /* left */)       const { return VALUENULL; }
CountPtr<Value> Value::mod(const ValueBool& /* left */)       const { return VALUENULL; }
CountPtr<Value> Value::mod(const ValueInt& /* left */)        const { return VALUENULL; }
CountPtr<Value> Value::mod(const ValueFloat& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::mod(const ValueString& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::mod(const ValueStruct& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::mod(const ValueReference& /* left */)  const { return VALUENULL; }
CountPtr<Value> Value::mod(const ValueIdentifier& /* left */) const { return VALUENULL; }
CountPtr<Value> Value::mod(const ValueGraph& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::mod(const ValueVertex& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::mod(const ValueEdge& /* left */)       const { return VALUENULL; }
CountPtr<Value> Value::mod(const ValueSet& /* left */)        const { return VALUENULL; }

// ==
CountPtr<Value> Value::eq(const ValueNull& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::eq(const ValueBool& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::eq(const ValueInt& /* left */)         const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::eq(const ValueFloat& /* left */)       const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::eq(const ValueString& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::eq(const ValueStruct& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::eq(const ValueReference& /* left */)   const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::eq(const ValueIdentifier& /* left */)  const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::eq(const ValueGraph& /* left */)       const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::eq(const ValueVertex& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::eq(const ValueEdge& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::eq(const ValueSet& /* left */)         const { return VALUEBOOL_FALSE; }

// !=
CountPtr<Value> Value::ne(const ValueNull& /* left */)        const { return VALUEBOOL_TRUE; }
CountPtr<Value> Value::ne(const ValueBool& /* left */)        const { return VALUEBOOL_TRUE; }
CountPtr<Value> Value::ne(const ValueInt& /* left */)         const { return VALUEBOOL_TRUE; }
CountPtr<Value> Value::ne(const ValueFloat& /* left */)       const { return VALUEBOOL_TRUE; }
CountPtr<Value> Value::ne(const ValueString& /* left */)      const { return VALUEBOOL_TRUE; }
CountPtr<Value> Value::ne(const ValueStruct& /* left */)      const { return VALUEBOOL_TRUE; }
CountPtr<Value> Value::ne(const ValueReference& /* left */)   const { return VALUEBOOL_TRUE; }
CountPtr<Value> Value::ne(const ValueIdentifier& /* left */)  const { return VALUEBOOL_TRUE; }
CountPtr<Value> Value::ne(const ValueGraph& /* left */)       const { return VALUEBOOL_TRUE; }
CountPtr<Value> Value::ne(const ValueVertex& /* left */)      const { return VALUEBOOL_TRUE; }
CountPtr<Value> Value::ne(const ValueEdge& /* left */)        const { return VALUEBOOL_TRUE; }
CountPtr<Value> Value::ne(const ValueSet& /* left */)         const { return VALUEBOOL_TRUE; }

// <=
CountPtr<Value> Value::le(const ValueNull& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::le(const ValueBool& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::le(const ValueInt& /* left */)         const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::le(const ValueFloat& /* left */)       const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::le(const ValueString& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::le(const ValueStruct& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::le(const ValueReference& /* left */)   const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::le(const ValueIdentifier& /* left */)  const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::le(const ValueGraph& /* left */)       const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::le(const ValueVertex& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::le(const ValueEdge& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::le(const ValueSet& /* left */)         const { return VALUEBOOL_FALSE; }

// >=
CountPtr<Value> Value::ge(const ValueNull& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::ge(const ValueBool& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::ge(const ValueInt& /* left */)         const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::ge(const ValueFloat& /* left */)       const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::ge(const ValueString& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::ge(const ValueStruct& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::ge(const ValueReference& /* left */)   const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::ge(const ValueIdentifier& /* left */)  const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::ge(const ValueGraph& /* left */)       const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::ge(const ValueVertex& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::ge(const ValueEdge& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::ge(const ValueSet& /* left */)         const { return VALUEBOOL_FALSE; }

// <
CountPtr<Value> Value::lt(const ValueNull& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::lt(const ValueBool& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::lt(const ValueInt& /* left */)         const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::lt(const ValueFloat& /* left */)       const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::lt(const ValueString& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::lt(const ValueStruct& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::lt(const ValueReference& /* left */)   const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::lt(const ValueIdentifier& /* left */)  const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::lt(const ValueGraph& /* left */)       const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::lt(const ValueVertex& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::lt(const ValueEdge& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::lt(const ValueSet& /* left */)         const { return VALUEBOOL_FALSE; }

// >
CountPtr<Value> Value::gt(const ValueNull& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::gt(const ValueBool& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::gt(const ValueInt& /* left */)         const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::gt(const ValueFloat& /* left */)       const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::gt(const ValueString& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::gt(const ValueStruct& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::gt(const ValueReference& /* left */)   const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::gt(const ValueIdentifier& /* left */)  const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::gt(const ValueGraph& /* left */)       const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::gt(const ValueVertex& /* left */)      const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::gt(const ValueEdge& /* left */)        const { return VALUEBOOL_FALSE; }
CountPtr<Value> Value::gt(const ValueSet& /* left */)         const { return VALUEBOOL_FALSE; }

// . (member access)
CountPtr<Value> Value::member(const ValueNull& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::member(const ValueBool& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::member(const ValueInt& /* left */)       const { return VALUENULL; }
CountPtr<Value> Value::member(const ValueFloat& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::member(const ValueString& /* left */)    const { return VALUENULL; }
CountPtr<Value> Value::member(const ValueStruct& /* left */)    const { return VALUENULL; }
CountPtr<Value> Value::member(const ValueReference& /* left */) const { return VALUENULL; }
CountPtr<Value> Value::member(const ValueIdentifier& /* left */)const { return VALUENULL; }
CountPtr<Value> Value::member(const ValueGraph& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::member(const ValueVertex& /* left */)    const { return VALUENULL; }
CountPtr<Value> Value::member(const ValueEdge& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::member(const ValueSet& /* left */)       const { return VALUENULL; }

// [] index

/*
TODO: ??? gcc bug ???
Tests::testValueArray()

right.index(*this) in ValueArray::index(const Value& right) calls
ValueInt::index(const Value& right)
ValueFloat::index(const Value& right)
etc.

instead of
ValueInt::index(const ValueArray& left)
ValueFloat::index(const ValueArray& left)
etc.

There is no problem with indexing of ValueString, why? It is the same!

Temporary fixed in Value::index() by dynamic_cast
*/
CountPtr<Value> Value::index(const ValueNull& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::index(const ValueBool& left)      const // { return VALUENULL; }
{
	ACCESS_MUTEX_LOCKER;

	const ValueArray* tmp = dynamic_cast<const ValueArray*>(this);
	if(tmp != NULL)
		return tmp->getItem(left.getVal());
	else
		return VALUENULL;
}

CountPtr<Value> Value::index(const ValueInt& left)       const // { return VALUENULL; }
{
	ACCESS_MUTEX_LOCKER;

	const ValueArray* tmp = dynamic_cast<const ValueArray*>(this);
	if(tmp != NULL)
		return tmp->getItem(left.getVal());
	else
		return VALUENULL;
}

CountPtr<Value> Value::index(const ValueFloat& left)     const // { return VALUENULL; }
{
	ACCESS_MUTEX_LOCKER;

	const ValueArray* tmp = dynamic_cast<const ValueArray*>(this);
	if(tmp != NULL)
		return tmp->getItem((uint)left.getVal());
	else
		return VALUENULL;
}

CountPtr<Value> Value::index(const ValueString& /* left */)    const { return VALUENULL; }
CountPtr<Value> Value::index(const ValueStruct& /* left */)    const { return VALUENULL; }
CountPtr<Value> Value::index(const ValueReference& /* left */) const { return VALUENULL; }
CountPtr<Value> Value::index(const ValueIdentifier& /* left */)const { return VALUENULL; }
CountPtr<Value> Value::index(const ValueGraph& /* left */)     const { return VALUENULL; }
CountPtr<Value> Value::index(const ValueVertex& /* left */)    const { return VALUENULL; }
CountPtr<Value> Value::index(const ValueEdge& /* left */)      const { return VALUENULL; }
CountPtr<Value> Value::index(const ValueSet& /* left */)       const { return VALUENULL; }

// - (unary)
CountPtr<Value> Value::subUn(void)   const { return VALUENULL; }
