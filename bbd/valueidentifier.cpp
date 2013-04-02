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


#include "valueidentifier.hpp"
#include "valuenull.hpp"
#include "valuebool.hpp"
#include "valueint.hpp"
#include "valuefloat.hpp"
#include "valuestring.hpp"
#include "valuestruct.hpp"
#include "valuereference.hpp"
#include "valuegraph.hpp"
#include "valuevertex.hpp"
#include "valueedge.hpp"
#include "valueset.hpp"
#include "logger.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueIdentifier::ValueIdentifier(identifier val)
	: Value(),
	m_val(val)
{

}

ValueIdentifier::~ValueIdentifier(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueIdentifier::getReferredValue(void) const
{
	ACCESS_MUTEX_LOCKER;
	CountPtr<Value> tmp(CONTEXT.getLocalVariable(m_val));

	while(tmp->isLValue())
		tmp = tmp->getReferredValue();

	return tmp;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueIdentifier::iterator(void) const
{
	return getReferredValue()->iterator();
}

CountPtr<Value> ValueIdentifier::hasNext(void) const
{
	return getReferredValue()->hasNext();
}

CountPtr<Value> ValueIdentifier::next(void)
{
	return getReferredValue()->next();
}

void ValueIdentifier::resetIterator(void)
{
	getReferredValue()->resetIterator();
}


/////////////////////////////////////////////////////////////////////////////
////


void ValueIdentifier::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<ValueIdentifier name=\"" << ID2STR(m_val) << "\" id=\"" << m_val << "\">" << endl;

	if(CONTEXT.isVariableSet(m_val))
		CONTEXT.getLocalVariable(m_val)->dump(os, indent+1);
	else
	{
		dumpIndent(os, indent+1);
		os << "<NoValue />" << endl;
	}

	dumpIndent(os, indent);
	os << "</ValueIdentifier>" << endl;
}

ostream& operator<<(ostream& os, const ValueIdentifier& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueIdentifier::add(const Value& right)          const { return this->getReferredValue()->add(right); } // +
CountPtr<Value> ValueIdentifier::add(const ValueNull& left)       const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::add(const ValueBool& left)       const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::add(const ValueInt& left)        const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::add(const ValueFloat& left)      const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::add(const ValueString& left)     const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::add(const ValueStruct& left)     const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::add(const ValueReference& left)  const { return left.getReferredValue()->add(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::add(const ValueIdentifier& left) const { return left.getReferredValue()->add(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::add(const ValueGraph& left)      const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::add(const ValueVertex& left)     const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::add(const ValueEdge& left)       const { return static_cast<const Value&>(left).add(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::add(const ValueSet& left)        const { return static_cast<const Value&>(left).add(*getReferredValue()); }

CountPtr<Value> ValueIdentifier::sub(const Value& right)          const { return this->getReferredValue()->sub(right); } // -
CountPtr<Value> ValueIdentifier::sub(const ValueNull& left)       const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::sub(const ValueBool& left)       const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::sub(const ValueInt& left)        const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::sub(const ValueFloat& left)      const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::sub(const ValueString& left)     const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::sub(const ValueStruct& left)     const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::sub(const ValueReference& left)  const { return left.getReferredValue()->sub(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::sub(const ValueIdentifier& left) const { return left.getReferredValue()->sub(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::sub(const ValueGraph& left)      const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::sub(const ValueVertex& left)     const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::sub(const ValueEdge& left)       const { return static_cast<const Value&>(left).sub(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::sub(const ValueSet& left)        const { return static_cast<const Value&>(left).sub(*getReferredValue()); }

CountPtr<Value> ValueIdentifier::mult(const Value& right)         const { return this->getReferredValue()->mult(right); } // *
CountPtr<Value> ValueIdentifier::mult(const ValueNull& left)      const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mult(const ValueBool& left)      const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mult(const ValueInt& left)       const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mult(const ValueFloat& left)     const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mult(const ValueString& left)    const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mult(const ValueStruct& left)    const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mult(const ValueReference& left) const { return left.getReferredValue()->mult(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mult(const ValueIdentifier& left)const { return left.getReferredValue()->mult(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mult(const ValueGraph& left)     const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mult(const ValueVertex& left)    const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mult(const ValueEdge& left)      const { return static_cast<const Value&>(left).mult(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mult(const ValueSet& left)       const { return static_cast<const Value&>(left).mult(*getReferredValue()); }

CountPtr<Value> ValueIdentifier::div(const Value& right)          const { return this->getReferredValue()->div(right); } // /
CountPtr<Value> ValueIdentifier::div(const ValueNull& left)       const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::div(const ValueBool& left)       const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::div(const ValueInt& left)        const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::div(const ValueFloat& left)      const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::div(const ValueString& left)     const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::div(const ValueStruct& left)     const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::div(const ValueReference& left)  const { return left.getReferredValue()->div(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::div(const ValueIdentifier& left) const { return left.getReferredValue()->div(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::div(const ValueGraph& left)      const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::div(const ValueVertex& left)     const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::div(const ValueEdge& left)       const { return static_cast<const Value&>(left).div(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::div(const ValueSet& left)        const { return static_cast<const Value&>(left).div(*getReferredValue()); }

CountPtr<Value> ValueIdentifier::mod(const Value& right)          const { return this->getReferredValue()->mod(right); } // %
CountPtr<Value> ValueIdentifier::mod(const ValueNull& left)       const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mod(const ValueBool& left)       const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mod(const ValueInt& left)        const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mod(const ValueFloat& left)      const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mod(const ValueString& left)     const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mod(const ValueStruct& left)     const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mod(const ValueReference& left)  const { return left.getReferredValue()->mod(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mod(const ValueIdentifier& left) const { return left.getReferredValue()->mod(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mod(const ValueGraph& left)      const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mod(const ValueVertex& left)     const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mod(const ValueEdge& left)       const { return static_cast<const Value&>(left).mod(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::mod(const ValueSet& left)        const { return static_cast<const Value&>(left).mod(*getReferredValue()); }

CountPtr<Value> ValueIdentifier::eq(const Value& right)           const { return this->getReferredValue()->eq(right); } // ==
CountPtr<Value> ValueIdentifier::eq(const ValueNull& left)        const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::eq(const ValueBool& left)        const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::eq(const ValueInt& left)         const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::eq(const ValueFloat& left)       const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::eq(const ValueString& left)      const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::eq(const ValueStruct& left)      const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::eq(const ValueReference& left)   const { return left.getReferredValue()->eq(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::eq(const ValueIdentifier& left)  const { return left.getReferredValue()->eq(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::eq(const ValueGraph& left)       const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::eq(const ValueVertex& left)      const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::eq(const ValueEdge& left)        const { return static_cast<const Value&>(left).eq(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::eq(const ValueSet& left)         const { return static_cast<const Value&>(left).eq(*getReferredValue()); }

CountPtr<Value> ValueIdentifier::ne(const Value& right)           const { return this->getReferredValue()->ne(right); } // !=
CountPtr<Value> ValueIdentifier::ne(const ValueNull& left)        const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ne(const ValueBool& left)        const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ne(const ValueInt& left)         const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ne(const ValueFloat& left)       const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ne(const ValueString& left)      const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ne(const ValueStruct& left)      const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ne(const ValueReference& left)   const { return left.getReferredValue()->ne(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ne(const ValueIdentifier& left)  const { return left.getReferredValue()->ne(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ne(const ValueGraph& left)       const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ne(const ValueVertex& left)      const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ne(const ValueEdge& left)        const { return static_cast<const Value&>(left).ne(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ne(const ValueSet& left)         const { return static_cast<const Value&>(left).ne(*getReferredValue()); }

CountPtr<Value> ValueIdentifier::le(const Value& right)           const { return this->getReferredValue()->le(right); } // <=
CountPtr<Value> ValueIdentifier::le(const ValueNull& left)        const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::le(const ValueBool& left)        const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::le(const ValueInt& left)         const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::le(const ValueFloat& left)       const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::le(const ValueString& left)      const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::le(const ValueStruct& left)      const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::le(const ValueReference& left)   const { return left.getReferredValue()->le(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::le(const ValueIdentifier& left)  const { return left.getReferredValue()->le(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::le(const ValueGraph& left)       const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::le(const ValueVertex& left)      const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::le(const ValueEdge& left)        const { return static_cast<const Value&>(left).le(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::le(const ValueSet& left)         const { return static_cast<const Value&>(left).le(*getReferredValue()); }

CountPtr<Value> ValueIdentifier::ge(const Value& right)           const { return this->getReferredValue()->ge(right); } // >=
CountPtr<Value> ValueIdentifier::ge(const ValueNull& left)        const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ge(const ValueBool& left)        const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ge(const ValueInt& left)         const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ge(const ValueFloat& left)       const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ge(const ValueString& left)      const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ge(const ValueStruct& left)      const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ge(const ValueReference& left)   const { return left.getReferredValue()->ge(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ge(const ValueIdentifier& left)  const { return left.getReferredValue()->ge(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ge(const ValueGraph& left)       const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ge(const ValueVertex& left)      const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ge(const ValueEdge& left)        const { return static_cast<const Value&>(left).ge(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::ge(const ValueSet& left)         const { return static_cast<const Value&>(left).ge(*getReferredValue()); }

CountPtr<Value> ValueIdentifier::lt(const Value& right)           const { return this->getReferredValue()->lt(right); } // <
CountPtr<Value> ValueIdentifier::lt(const ValueNull& left)        const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::lt(const ValueBool& left)        const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::lt(const ValueInt& left)         const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::lt(const ValueFloat& left)       const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::lt(const ValueString& left)      const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::lt(const ValueStruct& left)      const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::lt(const ValueReference& left)   const { return left.getReferredValue()->lt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::lt(const ValueIdentifier& left)  const { return left.getReferredValue()->lt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::lt(const ValueGraph& left)       const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::lt(const ValueVertex& left)      const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::lt(const ValueEdge& left)        const { return static_cast<const Value&>(left).lt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::lt(const ValueSet& left)         const { return static_cast<const Value&>(left).lt(*getReferredValue()); }

CountPtr<Value> ValueIdentifier::gt(const Value& right)           const { return this->getReferredValue()->gt(right); } // >
CountPtr<Value> ValueIdentifier::gt(const ValueNull& left)        const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::gt(const ValueBool& left)        const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::gt(const ValueInt& left)         const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::gt(const ValueFloat& left)       const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::gt(const ValueString& left)      const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::gt(const ValueStruct& left)      const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::gt(const ValueReference& left)   const { return left.getReferredValue()->gt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::gt(const ValueIdentifier& left)  const { return left.getReferredValue()->gt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::gt(const ValueGraph& left)       const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::gt(const ValueVertex& left)      const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::gt(const ValueEdge& left)        const { return static_cast<const Value&>(left).gt(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::gt(const ValueSet& left)         const { return static_cast<const Value&>(left).gt(*getReferredValue()); }

CountPtr<Value> ValueIdentifier::member(const Value& right)             const { return this->getReferredValue()->member(right); } // .
CountPtr<Value> ValueIdentifier::member(const ValueNull& /*left*/)      const { WARN_P(_("Member access to the NULL variable")); return VALUENULL; }
CountPtr<Value> ValueIdentifier::member(const ValueBool& /*left*/)      const { WARN_P(_("Member access to the bool variable")); return VALUENULL; }
CountPtr<Value> ValueIdentifier::member(const ValueInt& /*left*/)       const { WARN_P(_("Member access to the int variable")); return VALUENULL; }
CountPtr<Value> ValueIdentifier::member(const ValueFloat& /*left*/)     const { WARN_P(_("Member access to the float variable")); return VALUENULL; }
CountPtr<Value> ValueIdentifier::member(const ValueString& /*left*/)    const { WARN_P(_("Member access to the string variable")); return VALUENULL; }
CountPtr<Value> ValueIdentifier::member(const ValueStruct& left)        const { return const_cast<ValueStruct&>(left).getItem(m_val); }
CountPtr<Value> ValueIdentifier::member(const ValueReference& left)     const { return left.getReferredValue()->member(*static_cast<const Value*>(this)); }
CountPtr<Value> ValueIdentifier::member(const ValueIdentifier& left)    const { return left.getReferredValue()->member(*static_cast<const Value*>(this)); }
CountPtr<Value> ValueIdentifier::member(const ValueGraph& /*left*/)     const { WARN_P(_("Member access to the graph variable")); return VALUENULL; }
CountPtr<Value> ValueIdentifier::member(const ValueVertex& left)        const { return const_cast<ValueVertex&>(left).getItem(m_val); }
CountPtr<Value> ValueIdentifier::member(const ValueEdge& left)          const { return const_cast<ValueEdge&>(left).getItem(m_val); }
CountPtr<Value> ValueIdentifier::member(const ValueSet& /*left*/)       const { WARN_P(_("Member access to the VertexSet variable")); return VALUENULL; }

CountPtr<Value> ValueIdentifier::index(const Value& right)         const { return this->getReferredValue()->index(right); } // []
CountPtr<Value> ValueIdentifier::index(const ValueNull& left)      const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::index(const ValueBool& left)      const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::index(const ValueInt& left)       const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::index(const ValueFloat& left)     const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::index(const ValueString& left)    const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::index(const ValueStruct& left)    const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::index(const ValueReference& left) const { return left.getReferredValue()->index(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::index(const ValueIdentifier& left)const { return left.getReferredValue()->index(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::index(const ValueGraph& left)     const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::index(const ValueVertex& left)    const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::index(const ValueEdge& left)      const { return static_cast<const Value&>(left).index(*getReferredValue()); }
CountPtr<Value> ValueIdentifier::index(const ValueSet& left)       const { return static_cast<const Value&>(left).index(*getReferredValue()); }

CountPtr<Value> ValueIdentifier::logNOT(void)                      const { return this->getReferredValue()->logNOT(); } // !
