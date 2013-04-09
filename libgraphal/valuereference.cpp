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


#include "valuereference.h"
#include "valuenull.h"
#include "valuebool.h"
#include "valueint.h"
#include "valuefloat.h"
#include "valuestring.h"
#include "valuestruct.h"
#include "valueidentifier.h"
#include "valuegraph.h"
#include "valuevertex.h"
#include "valueedge.h"
#include "valueset.h"


/////////////////////////////////////////////////////////////////////////////
////

ValueReference::ValueReference(CountPtr<Value> val)
	: Value(),
	m_val(val)
{
	assert(!val->isLValue());
}


ValueReference::~ValueReference()
{

}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueReference::getReferredValue(void) const
{
	ACCESS_MUTEX_LOCKER;
	CountPtr<Value> tmp(m_val);

	while(tmp->isLValue())
		tmp = tmp->getReferredValue();

	return tmp;
}

CountPtr<Value> ValueReference::assign(CountPtr<Value> val)
{
	ACCESS_MUTEX_LOCKER;

	// Pointers support; array and struct items can have two references inside
	ValueReference* assign_to = m_val->toValueReference();
	if(assign_to == NULL)
		assign_to = this;

	if(val->isLValue())
		return assign_to->m_val = val->getReferredValue();
	else
		return assign_to->m_val = val;
}

CountPtr<Value> ValueReference::assignRef(CountPtr<Value> val)
{
	ACCESS_MUTEX_LOCKER;
	assert("ValueReference::assignRef() should not be called!" != NULL);
	return m_val = val;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueReference::iterator(void) const
{
	return getReferredValue()->iterator();
}

CountPtr<Value> ValueReference::hasNext(void) const
{
	return getReferredValue()->hasNext();
}

CountPtr<Value> ValueReference::next(void)
{
	return getReferredValue()->next();
}

void ValueReference::resetIterator(void)
{
	getReferredValue()->resetIterator();
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueReference::dump(ostream& os, uint indent) const
{
	ACCESS_MUTEX_LOCKER;

	dumpIndent(os, indent);

	// Debug
//	os << "<ValueReference refobjaddr=\"" << m_val.getPtr() << "\">" << endl;
	os << "<ValueReference>" << endl;

	m_val->dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</ValueReference>" << endl;
}

ostream& operator<<(ostream& os, const ValueReference& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueReference::add(const Value& right)          const { return this->getReferredValue()->add(right); } // +
CountPtr<Value> ValueReference::add(const ValueNull& left)       const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueReference::add(const ValueBool& left)       const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueReference::add(const ValueInt& left)        const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueReference::add(const ValueFloat& left)      const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueReference::add(const ValueString& left)     const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueReference::add(const ValueStruct& left)     const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueReference::add(const ValueReference& left)  const { return left.getReferredValue()->add(*getReferredValue()); }
CountPtr<Value> ValueReference::add(const ValueIdentifier& left) const { return left.getReferredValue()->add(*getReferredValue()); }
CountPtr<Value> ValueReference::add(const ValueGraph& left)      const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueReference::add(const ValueVertex& left)     const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueReference::add(const ValueEdge& left)       const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueReference::add(const ValueSet& left)        const { return static_cast<const Value&>(left).add(*getReferredValue()); }

CountPtr<Value> ValueReference::sub(const Value& right)          const { return this->getReferredValue()->sub(right); } // -
CountPtr<Value> ValueReference::sub(const ValueNull& left)       const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueReference::sub(const ValueBool& left)       const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueReference::sub(const ValueInt& left)        const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueReference::sub(const ValueFloat& left)      const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueReference::sub(const ValueString& left)     const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueReference::sub(const ValueStruct& left)     const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueReference::sub(const ValueReference& left)  const { return left.getReferredValue()->sub(*getReferredValue()); }
CountPtr<Value> ValueReference::sub(const ValueIdentifier& left) const { return left.getReferredValue()->sub(*getReferredValue()); }
CountPtr<Value> ValueReference::sub(const ValueGraph& left)      const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueReference::sub(const ValueVertex& left)     const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueReference::sub(const ValueEdge& left)       const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueReference::sub(const ValueSet& left)        const { return static_cast<const Value&>(left).sub(*getReferredValue()); }

CountPtr<Value> ValueReference::mult(const Value& right)         const { return this->getReferredValue()->mult(right); } // *
CountPtr<Value> ValueReference::mult(const ValueNull& left)      const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueReference::mult(const ValueBool& left)      const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueReference::mult(const ValueInt& left)       const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueReference::mult(const ValueFloat& left)     const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueReference::mult(const ValueString& left)    const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueReference::mult(const ValueStruct& left)    const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueReference::mult(const ValueReference& left) const { return left.getReferredValue()->mult(*getReferredValue()); }
CountPtr<Value> ValueReference::mult(const ValueIdentifier& left)const { return left.getReferredValue()->mult(*getReferredValue()); }
CountPtr<Value> ValueReference::mult(const ValueGraph& left)     const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueReference::mult(const ValueVertex& left)    const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueReference::mult(const ValueEdge& left)      const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueReference::mult(const ValueSet& left)       const { return static_cast<const Value&>(left).mult(*getReferredValue()); }

CountPtr<Value> ValueReference::div(const Value& right)          const { return this->getReferredValue()->div(right); } // /
CountPtr<Value> ValueReference::div(const ValueNull& left)       const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueReference::div(const ValueBool& left)       const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueReference::div(const ValueInt& left)        const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueReference::div(const ValueFloat& left)      const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueReference::div(const ValueString& left)     const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueReference::div(const ValueStruct& left)     const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueReference::div(const ValueReference& left)  const { return left.getReferredValue()->div(*getReferredValue()); }
CountPtr<Value> ValueReference::div(const ValueIdentifier& left) const { return left.getReferredValue()->div(*getReferredValue()); }
CountPtr<Value> ValueReference::div(const ValueGraph& left)      const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueReference::div(const ValueVertex& left)     const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueReference::div(const ValueEdge& left)       const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueReference::div(const ValueSet& left)        const { return static_cast<const Value&>(left).div(*getReferredValue()); }

CountPtr<Value> ValueReference::mod(const Value& right)          const { return this->getReferredValue()->mod(right); } // %
CountPtr<Value> ValueReference::mod(const ValueNull& left)       const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueReference::mod(const ValueBool& left)       const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueReference::mod(const ValueInt& left)        const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueReference::mod(const ValueFloat& left)      const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueReference::mod(const ValueString& left)     const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueReference::mod(const ValueStruct& left)     const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueReference::mod(const ValueReference& left)  const { return left.getReferredValue()->mod(*getReferredValue()); }
CountPtr<Value> ValueReference::mod(const ValueIdentifier& left) const { return left.getReferredValue()->mod(*getReferredValue()); }
CountPtr<Value> ValueReference::mod(const ValueGraph& left)      const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueReference::mod(const ValueVertex& left)     const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueReference::mod(const ValueEdge& left)       const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueReference::mod(const ValueSet& left)  const { return static_cast<const Value&>(left).mod(*getReferredValue()); }

CountPtr<Value> ValueReference::eq(const Value& right)           const { return this->getReferredValue()->eq(right); } // ==
CountPtr<Value> ValueReference::eq(const ValueNull& left)        const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueReference::eq(const ValueBool& left)        const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueReference::eq(const ValueInt& left)         const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueReference::eq(const ValueFloat& left)       const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueReference::eq(const ValueString& left)      const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueReference::eq(const ValueStruct& left)      const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueReference::eq(const ValueReference& left)   const { return left.getReferredValue()->eq(*getReferredValue()); }
CountPtr<Value> ValueReference::eq(const ValueIdentifier& left)  const { return left.getReferredValue()->eq(*getReferredValue()); }
CountPtr<Value> ValueReference::eq(const ValueGraph& left)       const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueReference::eq(const ValueVertex& left)      const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueReference::eq(const ValueEdge& left)        const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueReference::eq(const ValueSet& left)         const { return static_cast<const Value&>(left).eq(*getReferredValue()); }

CountPtr<Value> ValueReference::ne(const Value& right)           const { return this->getReferredValue()->ne(right); } // !=
CountPtr<Value> ValueReference::ne(const ValueNull& left)        const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueReference::ne(const ValueBool& left)        const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueReference::ne(const ValueInt& left)         const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueReference::ne(const ValueFloat& left)       const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueReference::ne(const ValueString& left)      const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueReference::ne(const ValueStruct& left)      const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueReference::ne(const ValueReference& left)   const { return left.getReferredValue()->ne(*getReferredValue()); }
CountPtr<Value> ValueReference::ne(const ValueIdentifier& left)  const { return left.getReferredValue()->ne(*getReferredValue()); }
CountPtr<Value> ValueReference::ne(const ValueGraph& left)       const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueReference::ne(const ValueVertex& left)      const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueReference::ne(const ValueEdge& left)        const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueReference::ne(const ValueSet& left)         const { return static_cast<const Value&>(left).ne(*getReferredValue()); }

CountPtr<Value> ValueReference::le(const Value& right)           const { return this->getReferredValue()->le(right); } // <=
CountPtr<Value> ValueReference::le(const ValueNull& left)        const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueReference::le(const ValueBool& left)        const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueReference::le(const ValueInt& left)         const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueReference::le(const ValueFloat& left)       const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueReference::le(const ValueString& left)      const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueReference::le(const ValueStruct& left)      const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueReference::le(const ValueReference& left)   const { return left.getReferredValue()->le(*getReferredValue()); }
CountPtr<Value> ValueReference::le(const ValueIdentifier& left)  const { return left.getReferredValue()->le(*getReferredValue()); }
CountPtr<Value> ValueReference::le(const ValueGraph& left)       const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueReference::le(const ValueVertex& left)      const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueReference::le(const ValueEdge& left)        const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueReference::le(const ValueSet& left)         const { return static_cast<const Value&>(left).le(*getReferredValue()); }

CountPtr<Value> ValueReference::ge(const Value& right)           const { return this->getReferredValue()->ge(right); } // >=
CountPtr<Value> ValueReference::ge(const ValueNull& left)        const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueReference::ge(const ValueBool& left)        const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueReference::ge(const ValueInt& left)         const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueReference::ge(const ValueFloat& left)       const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueReference::ge(const ValueString& left)      const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueReference::ge(const ValueStruct& left)      const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueReference::ge(const ValueReference& left)   const { return left.getReferredValue()->ge(*getReferredValue()); }
CountPtr<Value> ValueReference::ge(const ValueIdentifier& left)  const { return left.getReferredValue()->ge(*getReferredValue()); }
CountPtr<Value> ValueReference::ge(const ValueGraph& left)       const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueReference::ge(const ValueVertex& left)      const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueReference::ge(const ValueEdge& left)        const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueReference::ge(const ValueSet& left)         const { return static_cast<const Value&>(left).ge(*getReferredValue()); }

CountPtr<Value> ValueReference::lt(const Value& right)           const { return this->getReferredValue()->lt(right); } // <
CountPtr<Value> ValueReference::lt(const ValueNull& left)        const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueReference::lt(const ValueBool& left)        const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueReference::lt(const ValueInt& left)         const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueReference::lt(const ValueFloat& left)       const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueReference::lt(const ValueString& left)      const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueReference::lt(const ValueStruct& left)      const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueReference::lt(const ValueReference& left)   const { return left.getReferredValue()->lt(*getReferredValue()); }
CountPtr<Value> ValueReference::lt(const ValueIdentifier& left)  const { return left.getReferredValue()->lt(*getReferredValue()); }
CountPtr<Value> ValueReference::lt(const ValueGraph& left)       const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueReference::lt(const ValueVertex& left)      const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueReference::lt(const ValueEdge& left)        const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueReference::lt(const ValueSet& left)         const { return static_cast<const Value&>(left).lt(*getReferredValue()); }

CountPtr<Value> ValueReference::gt(const Value& right)           const { return this->getReferredValue()->gt(right); } // >
CountPtr<Value> ValueReference::gt(const ValueNull& left)        const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueReference::gt(const ValueBool& left)        const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueReference::gt(const ValueInt& left)         const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueReference::gt(const ValueFloat& left)       const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueReference::gt(const ValueString& left)      const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueReference::gt(const ValueStruct& left)      const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueReference::gt(const ValueReference& left)   const { return left.getReferredValue()->gt(*getReferredValue()); }
CountPtr<Value> ValueReference::gt(const ValueIdentifier& left)  const { return left.getReferredValue()->gt(*getReferredValue()); }
CountPtr<Value> ValueReference::gt(const ValueGraph& left)       const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueReference::gt(const ValueVertex& left)      const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueReference::gt(const ValueEdge& left)        const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueReference::gt(const ValueSet& left)         const { return static_cast<const Value&>(left).gt(*getReferredValue()); }

CountPtr<Value> ValueReference::member(const Value& right)         const { return this->getReferredValue()->gt(right); } // .
CountPtr<Value> ValueReference::member(const ValueNull& left)      const { return static_cast<const Value&>(left).member(*getReferredValue()); }
CountPtr<Value> ValueReference::member(const ValueBool& left)      const { return static_cast<const Value&>(left).member(*getReferredValue()); }
CountPtr<Value> ValueReference::member(const ValueInt& left)       const { return static_cast<const Value&>(left).member(*getReferredValue()); }
CountPtr<Value> ValueReference::member(const ValueFloat& left)     const { return static_cast<const Value&>(left).member(*getReferredValue()); }
CountPtr<Value> ValueReference::member(const ValueString& left)    const { return static_cast<const Value&>(left).member(*getReferredValue()); }
CountPtr<Value> ValueReference::member(const ValueStruct& left)    const { return static_cast<const Value&>(left).member(*getReferredValue()); }
CountPtr<Value> ValueReference::member(const ValueReference& left) const { return left.getReferredValue()->member(*getReferredValue()); }
CountPtr<Value> ValueReference::member(const ValueIdentifier& left)const { return left.getReferredValue()->member(*getReferredValue()); }
CountPtr<Value> ValueReference::member(const ValueGraph& left)     const { return static_cast<const Value&>(left).member(*getReferredValue()); }
CountPtr<Value> ValueReference::member(const ValueVertex& left)    const { return static_cast<const Value&>(left).member(*getReferredValue()); }
CountPtr<Value> ValueReference::member(const ValueEdge& left)      const { return static_cast<const Value&>(left).member(*getReferredValue()); }
CountPtr<Value> ValueReference::member(const ValueSet& left)       const { return static_cast<const Value&>(left).member(*getReferredValue()); }


CountPtr<Value> ValueReference::index(const Value& right)         const { return this->getReferredValue()->index(right); } // []
CountPtr<Value> ValueReference::index(const ValueNull& left)      const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueReference::index(const ValueBool& left)      const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueReference::index(const ValueInt& left)       const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueReference::index(const ValueFloat& left)     const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueReference::index(const ValueString& left)    const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueReference::index(const ValueStruct& left)    const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueReference::index(const ValueReference& left) const { return left.getReferredValue()->index(*getReferredValue()); }
CountPtr<Value> ValueReference::index(const ValueIdentifier& left)const { return left.getReferredValue()->index(*getReferredValue()); }
CountPtr<Value> ValueReference::index(const ValueGraph& left)     const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueReference::index(const ValueVertex& left)    const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueReference::index(const ValueEdge& left)      const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueReference::index(const ValueSet& left)       const { return static_cast<const Value&>(left).index(*getReferredValue()); }

CountPtr<Value> ValueReference::logNOT(void)                      const { return this->getReferredValue()->logNOT(); } // !
