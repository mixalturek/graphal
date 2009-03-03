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
#include "valuevertexset.hpp"
#include "logger.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueIdentifier::ValueIdentifier(identifier val)
	: Value(),
	m_val(val)
{

}

ValueIdentifier::~ValueIdentifier()
{

}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueIdentifier::getReferredValue(void) const
{
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

PTR_Value ValueIdentifier::add(const Value& right)          const { return this->getReferredValue()->add(right); } // +
PTR_Value ValueIdentifier::add(const ValueNull& left)       const { return dynamic_cast<const Value&>(left).add(*getReferredValue()); }
PTR_Value ValueIdentifier::add(const ValueBool& left)       const { return dynamic_cast<const Value&>(left).add(*getReferredValue()); }
PTR_Value ValueIdentifier::add(const ValueInt& left)        const { return dynamic_cast<const Value&>(left).add(*getReferredValue()); }
PTR_Value ValueIdentifier::add(const ValueFloat& left)      const { return dynamic_cast<const Value&>(left).add(*getReferredValue()); }
PTR_Value ValueIdentifier::add(const ValueString& left)     const { return dynamic_cast<const Value&>(left).add(*getReferredValue()); }
PTR_Value ValueIdentifier::add(const ValueStruct& left)     const { return dynamic_cast<const Value&>(left).add(*getReferredValue()); }
PTR_Value ValueIdentifier::add(const ValueReference& left)  const { return left.getReferredValue()->add(*getReferredValue()); }
PTR_Value ValueIdentifier::add(const ValueIdentifier& left) const { return left.getReferredValue()->add(*getReferredValue()); }
PTR_Value ValueIdentifier::add(const ValueGraph& left)      const { return dynamic_cast<const Value&>(left).add(*getReferredValue()); }
PTR_Value ValueIdentifier::add(const ValueVertex& left)     const { return dynamic_cast<const Value&>(left).add(*getReferredValue()); }
PTR_Value ValueIdentifier::add(const ValueEdge& left)       const { return dynamic_cast<const Value&>(left).add(*getReferredValue()); }
PTR_Value ValueIdentifier::add(const ValueVertexSet& left)  const { return dynamic_cast<const Value&>(left).add(*getReferredValue()); }
PTR_Value ValueIdentifier::add(const ValueEdgeSet& left)    const { return dynamic_cast<const Value&>(left).add(*getReferredValue()); }

PTR_Value ValueIdentifier::sub(const Value& right)          const { return this->getReferredValue()->sub(right); } // -
PTR_Value ValueIdentifier::sub(const ValueNull& left)       const { return dynamic_cast<const Value&>(left).sub(*getReferredValue()); }
PTR_Value ValueIdentifier::sub(const ValueBool& left)       const { return dynamic_cast<const Value&>(left).sub(*getReferredValue()); }
PTR_Value ValueIdentifier::sub(const ValueInt& left)        const { return dynamic_cast<const Value&>(left).sub(*getReferredValue()); }
PTR_Value ValueIdentifier::sub(const ValueFloat& left)      const { return dynamic_cast<const Value&>(left).sub(*getReferredValue()); }
PTR_Value ValueIdentifier::sub(const ValueString& left)     const { return dynamic_cast<const Value&>(left).sub(*getReferredValue()); }
PTR_Value ValueIdentifier::sub(const ValueStruct& left)     const { return dynamic_cast<const Value&>(left).sub(*getReferredValue()); }
PTR_Value ValueIdentifier::sub(const ValueReference& left)  const { return left.getReferredValue()->sub(*getReferredValue()); }
PTR_Value ValueIdentifier::sub(const ValueIdentifier& left) const { return left.getReferredValue()->sub(*getReferredValue()); }
PTR_Value ValueIdentifier::sub(const ValueGraph& left)      const { return dynamic_cast<const Value&>(left).sub(*getReferredValue()); }
PTR_Value ValueIdentifier::sub(const ValueVertex& left)     const { return dynamic_cast<const Value&>(left).sub(*getReferredValue()); }
PTR_Value ValueIdentifier::sub(const ValueEdge& left)       const { return dynamic_cast<const Value&>(left).sub(*getReferredValue()); }
PTR_Value ValueIdentifier::sub(const ValueVertexSet& left)  const { return dynamic_cast<const Value&>(left).sub(*getReferredValue()); }
PTR_Value ValueIdentifier::sub(const ValueEdgeSet& left)    const { return dynamic_cast<const Value&>(left).sub(*getReferredValue()); }

PTR_Value ValueIdentifier::mult(const Value& right)         const { return this->getReferredValue()->mult(right); } // *
PTR_Value ValueIdentifier::mult(const ValueNull& left)      const { return dynamic_cast<const Value&>(left).mult(*getReferredValue()); }
PTR_Value ValueIdentifier::mult(const ValueBool& left)      const { return dynamic_cast<const Value&>(left).mult(*getReferredValue()); }
PTR_Value ValueIdentifier::mult(const ValueInt& left)       const { return dynamic_cast<const Value&>(left).mult(*getReferredValue()); }
PTR_Value ValueIdentifier::mult(const ValueFloat& left)     const { return dynamic_cast<const Value&>(left).mult(*getReferredValue()); }
PTR_Value ValueIdentifier::mult(const ValueString& left)    const { return dynamic_cast<const Value&>(left).mult(*getReferredValue()); }
PTR_Value ValueIdentifier::mult(const ValueStruct& left)    const { return dynamic_cast<const Value&>(left).mult(*getReferredValue()); }
PTR_Value ValueIdentifier::mult(const ValueReference& left) const { return left.getReferredValue()->mult(*getReferredValue()); }
PTR_Value ValueIdentifier::mult(const ValueIdentifier& left)const { return left.getReferredValue()->mult(*getReferredValue()); }
PTR_Value ValueIdentifier::mult(const ValueGraph& left)     const { return dynamic_cast<const Value&>(left).mult(*getReferredValue()); }
PTR_Value ValueIdentifier::mult(const ValueVertex& left)    const { return dynamic_cast<const Value&>(left).mult(*getReferredValue()); }
PTR_Value ValueIdentifier::mult(const ValueEdge& left)      const { return dynamic_cast<const Value&>(left).mult(*getReferredValue()); }
PTR_Value ValueIdentifier::mult(const ValueVertexSet& left) const { return dynamic_cast<const Value&>(left).mult(*getReferredValue()); }
PTR_Value ValueIdentifier::mult(const ValueEdgeSet& left)   const { return dynamic_cast<const Value&>(left).mult(*getReferredValue()); }

PTR_Value ValueIdentifier::div(const Value& right)          const { return this->getReferredValue()->div(right); } // /
PTR_Value ValueIdentifier::div(const ValueNull& left)       const { return dynamic_cast<const Value&>(left).div(*getReferredValue()); }
PTR_Value ValueIdentifier::div(const ValueBool& left)       const { return dynamic_cast<const Value&>(left).div(*getReferredValue()); }
PTR_Value ValueIdentifier::div(const ValueInt& left)        const { return dynamic_cast<const Value&>(left).div(*getReferredValue()); }
PTR_Value ValueIdentifier::div(const ValueFloat& left)      const { return dynamic_cast<const Value&>(left).div(*getReferredValue()); }
PTR_Value ValueIdentifier::div(const ValueString& left)     const { return dynamic_cast<const Value&>(left).div(*getReferredValue()); }
PTR_Value ValueIdentifier::div(const ValueStruct& left)     const { return dynamic_cast<const Value&>(left).div(*getReferredValue()); }
PTR_Value ValueIdentifier::div(const ValueReference& left)  const { return left.getReferredValue()->div(*getReferredValue()); }
PTR_Value ValueIdentifier::div(const ValueIdentifier& left) const { return left.getReferredValue()->div(*getReferredValue()); }
PTR_Value ValueIdentifier::div(const ValueGraph& left)      const { return dynamic_cast<const Value&>(left).div(*getReferredValue()); }
PTR_Value ValueIdentifier::div(const ValueVertex& left)     const { return dynamic_cast<const Value&>(left).div(*getReferredValue()); }
PTR_Value ValueIdentifier::div(const ValueEdge& left)       const { return dynamic_cast<const Value&>(left).div(*getReferredValue()); }
PTR_Value ValueIdentifier::div(const ValueVertexSet& left)  const { return dynamic_cast<const Value&>(left).div(*getReferredValue()); }
PTR_Value ValueIdentifier::div(const ValueEdgeSet& left)    const { return dynamic_cast<const Value&>(left).div(*getReferredValue()); }

PTR_Value ValueIdentifier::mod(const Value& right)          const { return this->getReferredValue()->mod(right); } // %
PTR_Value ValueIdentifier::mod(const ValueNull& left)       const { return dynamic_cast<const Value&>(left).mod(*getReferredValue()); }
PTR_Value ValueIdentifier::mod(const ValueBool& left)       const { return dynamic_cast<const Value&>(left).mod(*getReferredValue()); }
PTR_Value ValueIdentifier::mod(const ValueInt& left)        const { return dynamic_cast<const Value&>(left).mod(*getReferredValue()); }
PTR_Value ValueIdentifier::mod(const ValueFloat& left)      const { return dynamic_cast<const Value&>(left).mod(*getReferredValue()); }
PTR_Value ValueIdentifier::mod(const ValueString& left)     const { return dynamic_cast<const Value&>(left).mod(*getReferredValue()); }
PTR_Value ValueIdentifier::mod(const ValueStruct& left)     const { return dynamic_cast<const Value&>(left).mod(*getReferredValue()); }
PTR_Value ValueIdentifier::mod(const ValueReference& left)  const { return left.getReferredValue()->mod(*getReferredValue()); }
PTR_Value ValueIdentifier::mod(const ValueIdentifier& left) const { return left.getReferredValue()->mod(*getReferredValue()); }
PTR_Value ValueIdentifier::mod(const ValueGraph& left)      const { return dynamic_cast<const Value&>(left).mod(*getReferredValue()); }
PTR_Value ValueIdentifier::mod(const ValueVertex& left)     const { return dynamic_cast<const Value&>(left).mod(*getReferredValue()); }
PTR_Value ValueIdentifier::mod(const ValueEdge& left)       const { return dynamic_cast<const Value&>(left).mod(*getReferredValue()); }
PTR_Value ValueIdentifier::mod(const ValueVertexSet& left)  const { return dynamic_cast<const Value&>(left).mod(*getReferredValue()); }
PTR_Value ValueIdentifier::mod(const ValueEdgeSet& left)    const { return dynamic_cast<const Value&>(left).mod(*getReferredValue()); }

PTR_Value ValueIdentifier::eq(const Value& right)           const { return this->getReferredValue()->eq(right); } // ==
PTR_Value ValueIdentifier::eq(const ValueNull& left)        const { return dynamic_cast<const Value&>(left).eq(*getReferredValue()); }
PTR_Value ValueIdentifier::eq(const ValueBool& left)        const { return dynamic_cast<const Value&>(left).eq(*getReferredValue()); }
PTR_Value ValueIdentifier::eq(const ValueInt& left)         const { return dynamic_cast<const Value&>(left).eq(*getReferredValue()); }
PTR_Value ValueIdentifier::eq(const ValueFloat& left)       const { return dynamic_cast<const Value&>(left).eq(*getReferredValue()); }
PTR_Value ValueIdentifier::eq(const ValueString& left)      const { return dynamic_cast<const Value&>(left).eq(*getReferredValue()); }
PTR_Value ValueIdentifier::eq(const ValueStruct& left)      const { return dynamic_cast<const Value&>(left).eq(*getReferredValue()); }
PTR_Value ValueIdentifier::eq(const ValueReference& left)   const { return left.getReferredValue()->eq(*getReferredValue()); }
PTR_Value ValueIdentifier::eq(const ValueIdentifier& left)  const { return left.getReferredValue()->eq(*getReferredValue()); }
PTR_Value ValueIdentifier::eq(const ValueGraph& left)       const { return dynamic_cast<const Value&>(left).eq(*getReferredValue()); }
PTR_Value ValueIdentifier::eq(const ValueVertex& left)      const { return dynamic_cast<const Value&>(left).eq(*getReferredValue()); }
PTR_Value ValueIdentifier::eq(const ValueEdge& left)        const { return dynamic_cast<const Value&>(left).eq(*getReferredValue()); }
PTR_Value ValueIdentifier::eq(const ValueVertexSet& left)   const { return dynamic_cast<const Value&>(left).eq(*getReferredValue()); }
PTR_Value ValueIdentifier::eq(const ValueEdgeSet& left)     const { return dynamic_cast<const Value&>(left).eq(*getReferredValue()); }

PTR_Value ValueIdentifier::ne(const Value& right)           const { return this->getReferredValue()->ne(right); } // !=
PTR_Value ValueIdentifier::ne(const ValueNull& left)        const { return dynamic_cast<const Value&>(left).ne(*getReferredValue()); }
PTR_Value ValueIdentifier::ne(const ValueBool& left)        const { return dynamic_cast<const Value&>(left).ne(*getReferredValue()); }
PTR_Value ValueIdentifier::ne(const ValueInt& left)         const { return dynamic_cast<const Value&>(left).ne(*getReferredValue()); }
PTR_Value ValueIdentifier::ne(const ValueFloat& left)       const { return dynamic_cast<const Value&>(left).ne(*getReferredValue()); }
PTR_Value ValueIdentifier::ne(const ValueString& left)      const { return dynamic_cast<const Value&>(left).ne(*getReferredValue()); }
PTR_Value ValueIdentifier::ne(const ValueStruct& left)      const { return dynamic_cast<const Value&>(left).ne(*getReferredValue()); }
PTR_Value ValueIdentifier::ne(const ValueReference& left)   const { return left.getReferredValue()->ne(*getReferredValue()); }
PTR_Value ValueIdentifier::ne(const ValueIdentifier& left)  const { return left.getReferredValue()->ne(*getReferredValue()); }
PTR_Value ValueIdentifier::ne(const ValueGraph& left)       const { return dynamic_cast<const Value&>(left).ne(*getReferredValue()); }
PTR_Value ValueIdentifier::ne(const ValueVertex& left)      const { return dynamic_cast<const Value&>(left).ne(*getReferredValue()); }
PTR_Value ValueIdentifier::ne(const ValueEdge& left)        const { return dynamic_cast<const Value&>(left).ne(*getReferredValue()); }
PTR_Value ValueIdentifier::ne(const ValueVertexSet& left)   const { return dynamic_cast<const Value&>(left).ne(*getReferredValue()); }
PTR_Value ValueIdentifier::ne(const ValueEdgeSet& left)     const { return dynamic_cast<const Value&>(left).ne(*getReferredValue()); }

PTR_Value ValueIdentifier::le(const Value& right)           const { return this->getReferredValue()->le(right); } // <=
PTR_Value ValueIdentifier::le(const ValueNull& left)        const { return dynamic_cast<const Value&>(left).le(*getReferredValue()); }
PTR_Value ValueIdentifier::le(const ValueBool& left)        const { return dynamic_cast<const Value&>(left).le(*getReferredValue()); }
PTR_Value ValueIdentifier::le(const ValueInt& left)         const { return dynamic_cast<const Value&>(left).le(*getReferredValue()); }
PTR_Value ValueIdentifier::le(const ValueFloat& left)       const { return dynamic_cast<const Value&>(left).le(*getReferredValue()); }
PTR_Value ValueIdentifier::le(const ValueString& left)      const { return dynamic_cast<const Value&>(left).le(*getReferredValue()); }
PTR_Value ValueIdentifier::le(const ValueStruct& left)      const { return dynamic_cast<const Value&>(left).le(*getReferredValue()); }
PTR_Value ValueIdentifier::le(const ValueReference& left)   const { return left.getReferredValue()->le(*getReferredValue()); }
PTR_Value ValueIdentifier::le(const ValueIdentifier& left)  const { return left.getReferredValue()->le(*getReferredValue()); }
PTR_Value ValueIdentifier::le(const ValueGraph& left)       const { return dynamic_cast<const Value&>(left).le(*getReferredValue()); }
PTR_Value ValueIdentifier::le(const ValueVertex& left)      const { return dynamic_cast<const Value&>(left).le(*getReferredValue()); }
PTR_Value ValueIdentifier::le(const ValueEdge& left)        const { return dynamic_cast<const Value&>(left).le(*getReferredValue()); }
PTR_Value ValueIdentifier::le(const ValueVertexSet& left)   const { return dynamic_cast<const Value&>(left).le(*getReferredValue()); }
PTR_Value ValueIdentifier::le(const ValueEdgeSet& left)     const { return dynamic_cast<const Value&>(left).le(*getReferredValue()); }

PTR_Value ValueIdentifier::ge(const Value& right)           const { return this->getReferredValue()->ge(right); } // >=
PTR_Value ValueIdentifier::ge(const ValueNull& left)        const { return dynamic_cast<const Value&>(left).ge(*getReferredValue()); }
PTR_Value ValueIdentifier::ge(const ValueBool& left)        const { return dynamic_cast<const Value&>(left).ge(*getReferredValue()); }
PTR_Value ValueIdentifier::ge(const ValueInt& left)         const { return dynamic_cast<const Value&>(left).ge(*getReferredValue()); }
PTR_Value ValueIdentifier::ge(const ValueFloat& left)       const { return dynamic_cast<const Value&>(left).ge(*getReferredValue()); }
PTR_Value ValueIdentifier::ge(const ValueString& left)      const { return dynamic_cast<const Value&>(left).ge(*getReferredValue()); }
PTR_Value ValueIdentifier::ge(const ValueStruct& left)      const { return dynamic_cast<const Value&>(left).ge(*getReferredValue()); }
PTR_Value ValueIdentifier::ge(const ValueReference& left)   const { return left.getReferredValue()->ge(*getReferredValue()); }
PTR_Value ValueIdentifier::ge(const ValueIdentifier& left)  const { return left.getReferredValue()->ge(*getReferredValue()); }
PTR_Value ValueIdentifier::ge(const ValueGraph& left)       const { return dynamic_cast<const Value&>(left).ge(*getReferredValue()); }
PTR_Value ValueIdentifier::ge(const ValueVertex& left)      const { return dynamic_cast<const Value&>(left).ge(*getReferredValue()); }
PTR_Value ValueIdentifier::ge(const ValueEdge& left)        const { return dynamic_cast<const Value&>(left).ge(*getReferredValue()); }
PTR_Value ValueIdentifier::ge(const ValueVertexSet& left)   const { return dynamic_cast<const Value&>(left).ge(*getReferredValue()); }
PTR_Value ValueIdentifier::ge(const ValueEdgeSet& left)     const { return dynamic_cast<const Value&>(left).ge(*getReferredValue()); }

PTR_Value ValueIdentifier::lt(const Value& right)           const { return this->getReferredValue()->lt(right); } // <
PTR_Value ValueIdentifier::lt(const ValueNull& left)        const { return dynamic_cast<const Value&>(left).lt(*getReferredValue()); }
PTR_Value ValueIdentifier::lt(const ValueBool& left)        const { return dynamic_cast<const Value&>(left).lt(*getReferredValue()); }
PTR_Value ValueIdentifier::lt(const ValueInt& left)         const { return dynamic_cast<const Value&>(left).lt(*getReferredValue()); }
PTR_Value ValueIdentifier::lt(const ValueFloat& left)       const { return dynamic_cast<const Value&>(left).lt(*getReferredValue()); }
PTR_Value ValueIdentifier::lt(const ValueString& left)      const { return dynamic_cast<const Value&>(left).lt(*getReferredValue()); }
PTR_Value ValueIdentifier::lt(const ValueStruct& left)      const { return dynamic_cast<const Value&>(left).lt(*getReferredValue()); }
PTR_Value ValueIdentifier::lt(const ValueReference& left)   const { return left.getReferredValue()->lt(*getReferredValue()); }
PTR_Value ValueIdentifier::lt(const ValueIdentifier& left)  const { return left.getReferredValue()->lt(*getReferredValue()); }
PTR_Value ValueIdentifier::lt(const ValueGraph& left)       const { return dynamic_cast<const Value&>(left).lt(*getReferredValue()); }
PTR_Value ValueIdentifier::lt(const ValueVertex& left)      const { return dynamic_cast<const Value&>(left).lt(*getReferredValue()); }
PTR_Value ValueIdentifier::lt(const ValueEdge& left)        const { return dynamic_cast<const Value&>(left).lt(*getReferredValue()); }
PTR_Value ValueIdentifier::lt(const ValueVertexSet& left)   const { return dynamic_cast<const Value&>(left).lt(*getReferredValue()); }
PTR_Value ValueIdentifier::lt(const ValueEdgeSet& left)     const { return dynamic_cast<const Value&>(left).lt(*getReferredValue()); }

PTR_Value ValueIdentifier::gt(const Value& right)           const { return this->getReferredValue()->gt(right); } // >
PTR_Value ValueIdentifier::gt(const ValueNull& left)        const { return dynamic_cast<const Value&>(left).gt(*getReferredValue()); }
PTR_Value ValueIdentifier::gt(const ValueBool& left)        const { return dynamic_cast<const Value&>(left).gt(*getReferredValue()); }
PTR_Value ValueIdentifier::gt(const ValueInt& left)         const { return dynamic_cast<const Value&>(left).gt(*getReferredValue()); }
PTR_Value ValueIdentifier::gt(const ValueFloat& left)       const { return dynamic_cast<const Value&>(left).gt(*getReferredValue()); }
PTR_Value ValueIdentifier::gt(const ValueString& left)      const { return dynamic_cast<const Value&>(left).gt(*getReferredValue()); }
PTR_Value ValueIdentifier::gt(const ValueStruct& left)      const { return dynamic_cast<const Value&>(left).gt(*getReferredValue()); }
PTR_Value ValueIdentifier::gt(const ValueReference& left)   const { return left.getReferredValue()->gt(*getReferredValue()); }
PTR_Value ValueIdentifier::gt(const ValueIdentifier& left)  const { return left.getReferredValue()->gt(*getReferredValue()); }
PTR_Value ValueIdentifier::gt(const ValueGraph& left)       const { return dynamic_cast<const Value&>(left).gt(*getReferredValue()); }
PTR_Value ValueIdentifier::gt(const ValueVertex& left)      const { return dynamic_cast<const Value&>(left).gt(*getReferredValue()); }
PTR_Value ValueIdentifier::gt(const ValueEdge& left)        const { return dynamic_cast<const Value&>(left).gt(*getReferredValue()); }
PTR_Value ValueIdentifier::gt(const ValueVertexSet& left)   const { return dynamic_cast<const Value&>(left).gt(*getReferredValue()); }
PTR_Value ValueIdentifier::gt(const ValueEdgeSet& left)     const { return dynamic_cast<const Value&>(left).gt(*getReferredValue()); }

PTR_Value ValueIdentifier::member(const Value& right)             const { return this->getReferredValue()->member(right); } // .
PTR_Value ValueIdentifier::member(const ValueNull& /*left*/)      const { WARN << _("Member access to the NULL variable, operation is not supported") << endl; return VALUENULL; }
PTR_Value ValueIdentifier::member(const ValueBool& /*left*/)      const { WARN << _("Member access to the bool variable, operation is not supported") << endl; return VALUENULL; }
PTR_Value ValueIdentifier::member(const ValueInt& /*left*/)       const { WARN << _("Member access to the int variable, operation is not supported") << endl; return VALUENULL; }
PTR_Value ValueIdentifier::member(const ValueFloat& /*left*/)     const { WARN << _("Member access to the float variable, operation is not supported") << endl; return VALUENULL; }
PTR_Value ValueIdentifier::member(const ValueString& /*left*/)    const { WARN << _("Member access to the string variable, operation is not supported") << endl; return VALUENULL; }
PTR_Value ValueIdentifier::member(const ValueStruct& left)        const { return const_cast<ValueStruct&>(left).getItem(m_val); }
PTR_Value ValueIdentifier::member(const ValueReference& left)     const { return left.getReferredValue()->member(*dynamic_cast<const Value*>(this)); }
PTR_Value ValueIdentifier::member(const ValueIdentifier& left)    const { return left.getReferredValue()->member(*dynamic_cast<const Value*>(this)); }
PTR_Value ValueIdentifier::member(const ValueGraph& /*left*/)     const { WARN << _("Member access to the graph variable, operation is not supported") << endl; return VALUENULL; }
PTR_Value ValueIdentifier::member(const ValueVertex& left)        const { return const_cast<ValueVertex&>(left).getItem(m_val); }
PTR_Value ValueIdentifier::member(const ValueEdge& left)          const { return const_cast<ValueEdge&>(left).getItem(m_val); }
PTR_Value ValueIdentifier::member(const ValueVertexSet& /*left*/) const { WARN << _("Member access to the VertexSet variable, operation is not supported") << endl; return VALUENULL; }
PTR_Value ValueIdentifier::member(const ValueEdgeSet& /*left*/)   const { WARN << _("Member access to the EdgeSet variable, operation is not supported") << endl; return VALUENULL; }

PTR_Value ValueIdentifier::index(const Value& right)         const { return this->getReferredValue()->index(right); } // []
PTR_Value ValueIdentifier::index(const ValueNull& left)      const { return dynamic_cast<const Value&>(left).index(*getReferredValue()); }
PTR_Value ValueIdentifier::index(const ValueBool& left)      const { return dynamic_cast<const Value&>(left).index(*getReferredValue()); }
PTR_Value ValueIdentifier::index(const ValueInt& left)       const { return dynamic_cast<const Value&>(left).index(*getReferredValue()); }
PTR_Value ValueIdentifier::index(const ValueFloat& left)     const { return dynamic_cast<const Value&>(left).index(*getReferredValue()); }
PTR_Value ValueIdentifier::index(const ValueString& left)    const { return dynamic_cast<const Value&>(left).index(*getReferredValue()); }
PTR_Value ValueIdentifier::index(const ValueStruct& left)    const { return dynamic_cast<const Value&>(left).index(*getReferredValue()); }
PTR_Value ValueIdentifier::index(const ValueReference& left) const { return left.getReferredValue()->index(*getReferredValue()); }
PTR_Value ValueIdentifier::index(const ValueIdentifier& left)const { return left.getReferredValue()->index(*getReferredValue()); }
PTR_Value ValueIdentifier::index(const ValueGraph& left)     const { return dynamic_cast<const Value&>(left).index(*getReferredValue()); }
PTR_Value ValueIdentifier::index(const ValueVertex& left)    const { return dynamic_cast<const Value&>(left).index(*getReferredValue()); }
PTR_Value ValueIdentifier::index(const ValueEdge& left)      const { return dynamic_cast<const Value&>(left).index(*getReferredValue()); }
PTR_Value ValueIdentifier::index(const ValueVertexSet& left) const { return dynamic_cast<const Value&>(left).index(*getReferredValue()); }
PTR_Value ValueIdentifier::index(const ValueEdgeSet& left)   const { return dynamic_cast<const Value&>(left).index(*getReferredValue()); }

PTR_Value ValueIdentifier::logNOT(void)                      const { return this->getReferredValue()->logNOT(); } // !
