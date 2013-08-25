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


#ifndef VALUEREFERENCE_HPP
#define VALUEREFERENCE_HPP

#include <cassert>
#include "general.h"
#include "value.h"
#include "countptr.h"

class ValueReference : public Value
{
public:
	ValueReference(CountPtr<Value> val);
	virtual ~ValueReference();

public:
	CountPtr<Value>   getVal(void) const { return m_val; }
	virtual bool      toBool(void) const { return m_val->toBool(); }
	virtual bool      isNull(void) const { return m_val->isNull(); }
	virtual bool    isLValue(void) const { return true; }
	virtual string  toString(void) const { return m_val->toString(); }
	virtual bool   isNumeric(void) const { return m_val->isNumeric(); }
	virtual int        toInt(void) const { return m_val->toInt(); }
	virtual float    toFloat(void) const { return m_val->toFloat(); }

	virtual ValueBool*           toValueBool(void) { return m_val->toValueBool(); }
	virtual ValueInt*             toValueInt(void) { return m_val->toValueInt(); }
	virtual ValueFloat*         toValueFloat(void) { return m_val->toValueFloat(); }
	virtual ValueString*       toValueString(void) { return m_val->toValueString(); }
	virtual ValueStruct*       toValueStruct(void) { return m_val->toValueStruct(); }
	virtual ValueArray*         toValueArray(void) { return m_val->toValueArray(); }
	virtual ValueGraph*         toValueGraph(void) { return m_val->toValueGraph(); }
	virtual ValueVertex*       toValueVertex(void) { return m_val->toValueVertex(); }
	virtual ValueEdge*           toValueEdge(void) { return m_val->toValueEdge(); }
	virtual ValueSet*             toValueSet(void) { return m_val->toValueSet(); }
	virtual ValueReference* toValueReference(void) { return this; }

	virtual CountPtr<Value> assign(CountPtr<Value> val);
	virtual CountPtr<Value> assignRef(CountPtr<Value> val);
	virtual CountPtr<Value> getReferredValue(void) const;

	virtual CountPtr<Value> iterator(void) const;
	virtual CountPtr<Value> hasNext(void) const;
	virtual CountPtr<Value> next(void);
	virtual void resetIterator(void);

	virtual void dump(ostream& os, uint indent) const;

	// +
	virtual CountPtr<Value> add(const Value&         right) const;
	virtual CountPtr<Value> add(const ValueNull&      left) const;
	virtual CountPtr<Value> add(const ValueBool&      left) const;
	virtual CountPtr<Value> add(const ValueInt&       left) const;
	virtual CountPtr<Value> add(const ValueFloat&     left) const;
	virtual CountPtr<Value> add(const ValueString&    left) const;
	virtual CountPtr<Value> add(const ValueStruct&    left) const;
	virtual CountPtr<Value> add(const ValueReference& left) const;
	virtual CountPtr<Value> add(const ValueIdentifier& left) const;
	virtual CountPtr<Value> add(const ValueGraph&     left) const;
	virtual CountPtr<Value> add(const ValueVertex&    left) const;
	virtual CountPtr<Value> add(const ValueEdge&      left) const;
	virtual CountPtr<Value> add(const ValueSet&       left) const;

	// -
	virtual CountPtr<Value> sub(const Value&         right) const;
	virtual CountPtr<Value> sub(const ValueNull&      left) const;
	virtual CountPtr<Value> sub(const ValueBool&      left) const;
	virtual CountPtr<Value> sub(const ValueInt&       left) const;
	virtual CountPtr<Value> sub(const ValueFloat&     left) const;
	virtual CountPtr<Value> sub(const ValueString&    left) const;
	virtual CountPtr<Value> sub(const ValueStruct&    left) const;
	virtual CountPtr<Value> sub(const ValueReference& left) const;
	virtual CountPtr<Value> sub(const ValueIdentifier& left) const;
	virtual CountPtr<Value> sub(const ValueGraph&     left) const;
	virtual CountPtr<Value> sub(const ValueVertex&    left) const;
	virtual CountPtr<Value> sub(const ValueEdge&      left) const;
	virtual CountPtr<Value> sub(const ValueSet&       left) const;

	// *
	virtual CountPtr<Value> mult(const Value&         right) const;
	virtual CountPtr<Value> mult(const ValueNull&      left) const;
	virtual CountPtr<Value> mult(const ValueBool&      left) const;
	virtual CountPtr<Value> mult(const ValueInt&       left) const;
	virtual CountPtr<Value> mult(const ValueFloat&     left) const;
	virtual CountPtr<Value> mult(const ValueString&    left) const;
	virtual CountPtr<Value> mult(const ValueStruct&    left) const;
	virtual CountPtr<Value> mult(const ValueReference& left) const;
	virtual CountPtr<Value> mult(const ValueIdentifier& left) const;
	virtual CountPtr<Value> mult(const ValueGraph&     left) const;
	virtual CountPtr<Value> mult(const ValueVertex&    left) const;
	virtual CountPtr<Value> mult(const ValueEdge&      left) const;
	virtual CountPtr<Value> mult(const ValueSet&       left) const;

	// /
	virtual CountPtr<Value> div(const Value&         right) const;
	virtual CountPtr<Value> div(const ValueNull&      left) const;
	virtual CountPtr<Value> div(const ValueBool&      left) const;
	virtual CountPtr<Value> div(const ValueInt&       left) const;
	virtual CountPtr<Value> div(const ValueFloat&     left) const;
	virtual CountPtr<Value> div(const ValueString&    left) const;
	virtual CountPtr<Value> div(const ValueStruct&    left) const;
	virtual CountPtr<Value> div(const ValueReference& left) const;
	virtual CountPtr<Value> div(const ValueIdentifier& left) const;
	virtual CountPtr<Value> div(const ValueGraph&     left) const;
	virtual CountPtr<Value> div(const ValueVertex&    left) const;
	virtual CountPtr<Value> div(const ValueEdge&      left) const;
	virtual CountPtr<Value> div(const ValueSet&       left) const;

	// %
	virtual CountPtr<Value> mod(const Value&         right) const;
	virtual CountPtr<Value> mod(const ValueNull&      left) const;
	virtual CountPtr<Value> mod(const ValueBool&      left) const;
	virtual CountPtr<Value> mod(const ValueInt&       left) const;
	virtual CountPtr<Value> mod(const ValueFloat&     left) const;
	virtual CountPtr<Value> mod(const ValueString&    left) const;
	virtual CountPtr<Value> mod(const ValueStruct&    left) const;
	virtual CountPtr<Value> mod(const ValueReference& left) const;
	virtual CountPtr<Value> mod(const ValueIdentifier& left) const;
	virtual CountPtr<Value> mod(const ValueGraph&     left) const;
	virtual CountPtr<Value> mod(const ValueVertex&    left) const;
	virtual CountPtr<Value> mod(const ValueEdge&      left) const;
	virtual CountPtr<Value> mod(const ValueSet&       left) const;

	// ==
	virtual CountPtr<Value> eq(const Value&         right) const;
	virtual CountPtr<Value> eq(const ValueNull&      left) const;
	virtual CountPtr<Value> eq(const ValueBool&      left) const;
	virtual CountPtr<Value> eq(const ValueInt&       left) const;
	virtual CountPtr<Value> eq(const ValueFloat&     left) const;
	virtual CountPtr<Value> eq(const ValueString&    left) const;
	virtual CountPtr<Value> eq(const ValueStruct&    left) const;
	virtual CountPtr<Value> eq(const ValueReference& left) const;
	virtual CountPtr<Value> eq(const ValueIdentifier& left) const;
	virtual CountPtr<Value> eq(const ValueGraph&     left) const;
	virtual CountPtr<Value> eq(const ValueVertex&    left) const;
	virtual CountPtr<Value> eq(const ValueEdge&      left) const;
	virtual CountPtr<Value> eq(const ValueSet&       left) const;

	// !=
	virtual CountPtr<Value> ne(const Value&         right) const;
	virtual CountPtr<Value> ne(const ValueNull&      left) const;
	virtual CountPtr<Value> ne(const ValueBool&      left) const;
	virtual CountPtr<Value> ne(const ValueInt&       left) const;
	virtual CountPtr<Value> ne(const ValueFloat&     left) const;
	virtual CountPtr<Value> ne(const ValueString&    left) const;
	virtual CountPtr<Value> ne(const ValueStruct&    left) const;
	virtual CountPtr<Value> ne(const ValueReference& left) const;
	virtual CountPtr<Value> ne(const ValueIdentifier& left) const;
	virtual CountPtr<Value> ne(const ValueGraph&     left) const;
	virtual CountPtr<Value> ne(const ValueVertex&    left) const;
	virtual CountPtr<Value> ne(const ValueEdge&      left) const;
	virtual CountPtr<Value> ne(const ValueSet&       left) const;

	// <=
	virtual CountPtr<Value> le(const Value&         right) const;
	virtual CountPtr<Value> le(const ValueNull&      left) const;
	virtual CountPtr<Value> le(const ValueBool&      left) const;
	virtual CountPtr<Value> le(const ValueInt&       left) const;
	virtual CountPtr<Value> le(const ValueFloat&     left) const;
	virtual CountPtr<Value> le(const ValueString&    left) const;
	virtual CountPtr<Value> le(const ValueStruct&    left) const;
	virtual CountPtr<Value> le(const ValueReference& left) const;
	virtual CountPtr<Value> le(const ValueIdentifier& left) const;
	virtual CountPtr<Value> le(const ValueGraph&     left) const;
	virtual CountPtr<Value> le(const ValueVertex&    left) const;
	virtual CountPtr<Value> le(const ValueEdge&      left) const;
	virtual CountPtr<Value> le(const ValueSet&       left) const;

	// >=
	virtual CountPtr<Value> ge(const Value&         right) const;
	virtual CountPtr<Value> ge(const ValueNull&      left) const;
	virtual CountPtr<Value> ge(const ValueBool&      left) const;
	virtual CountPtr<Value> ge(const ValueInt&       left) const;
	virtual CountPtr<Value> ge(const ValueFloat&     left) const;
	virtual CountPtr<Value> ge(const ValueString&    left) const;
	virtual CountPtr<Value> ge(const ValueStruct&    left) const;
	virtual CountPtr<Value> ge(const ValueReference& left) const;
	virtual CountPtr<Value> ge(const ValueIdentifier& left) const;
	virtual CountPtr<Value> ge(const ValueGraph&     left) const;
	virtual CountPtr<Value> ge(const ValueVertex&    left) const;
	virtual CountPtr<Value> ge(const ValueEdge&      left) const;
	virtual CountPtr<Value> ge(const ValueSet&       left) const;

	// <
	virtual CountPtr<Value> lt(const Value&         right) const;
	virtual CountPtr<Value> lt(const ValueNull&      left) const;
	virtual CountPtr<Value> lt(const ValueBool&      left) const;
	virtual CountPtr<Value> lt(const ValueInt&       left) const;
	virtual CountPtr<Value> lt(const ValueFloat&     left) const;
	virtual CountPtr<Value> lt(const ValueString&    left) const;
	virtual CountPtr<Value> lt(const ValueStruct&    left) const;
	virtual CountPtr<Value> lt(const ValueReference& left) const;
	virtual CountPtr<Value> lt(const ValueIdentifier& left) const;
	virtual CountPtr<Value> lt(const ValueGraph&     left) const;
	virtual CountPtr<Value> lt(const ValueVertex&    left) const;
	virtual CountPtr<Value> lt(const ValueEdge&      left) const;
	virtual CountPtr<Value> lt(const ValueSet&       left) const;

	// >
	virtual CountPtr<Value> gt(const Value&         right) const;
	virtual CountPtr<Value> gt(const ValueNull&      left) const;
	virtual CountPtr<Value> gt(const ValueBool&      left) const;
	virtual CountPtr<Value> gt(const ValueInt&       left) const;
	virtual CountPtr<Value> gt(const ValueFloat&     left) const;
	virtual CountPtr<Value> gt(const ValueString&    left) const;
	virtual CountPtr<Value> gt(const ValueStruct&    left) const;
	virtual CountPtr<Value> gt(const ValueReference& left) const;
	virtual CountPtr<Value> gt(const ValueIdentifier& left) const;
	virtual CountPtr<Value> gt(const ValueGraph&     left) const;
	virtual CountPtr<Value> gt(const ValueVertex&    left) const;
	virtual CountPtr<Value> gt(const ValueEdge&      left) const;
	virtual CountPtr<Value> gt(const ValueSet&       left) const;

	// . (member access)
	virtual CountPtr<Value> member(const Value&         right) const;
	virtual CountPtr<Value> member(const ValueNull&      left) const;
	virtual CountPtr<Value> member(const ValueBool&      left) const;
	virtual CountPtr<Value> member(const ValueInt&       left) const;
	virtual CountPtr<Value> member(const ValueFloat&     left) const;
	virtual CountPtr<Value> member(const ValueString&    left) const;
	virtual CountPtr<Value> member(const ValueStruct&    left) const;
	virtual CountPtr<Value> member(const ValueReference& left) const;
	virtual CountPtr<Value> member(const ValueIdentifier& left) const;
	virtual CountPtr<Value> member(const ValueGraph&     left) const;
	virtual CountPtr<Value> member(const ValueVertex&    left) const;
	virtual CountPtr<Value> member(const ValueEdge&      left) const;
	virtual CountPtr<Value> member(const ValueSet&       left) const;

	// [] index
	virtual CountPtr<Value> index(const Value&         right) const;
	virtual CountPtr<Value> index(const ValueNull&      left) const;
	virtual CountPtr<Value> index(const ValueBool&      left) const;
	virtual CountPtr<Value> index(const ValueInt&       left) const;
	virtual CountPtr<Value> index(const ValueFloat&     left) const;
	virtual CountPtr<Value> index(const ValueString&    left) const;
	virtual CountPtr<Value> index(const ValueStruct&    left) const;
	virtual CountPtr<Value> index(const ValueReference& left) const;
	virtual CountPtr<Value> index(const ValueIdentifier& left) const;
	virtual CountPtr<Value> index(const ValueGraph&     left) const;
	virtual CountPtr<Value> index(const ValueVertex&    left) const;
	virtual CountPtr<Value> index(const ValueEdge&      left) const;
	virtual CountPtr<Value> index(const ValueSet&       left) const;

	virtual CountPtr<Value> logNOT(void)               const; // !

private:
	CountPtr<Value> m_val;
};

ostream& operator<<(ostream& os, const ValueReference& node);

#endif /* VALUEREFERENCE_HPP */
