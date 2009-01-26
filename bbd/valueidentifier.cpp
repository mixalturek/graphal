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

	while(tmp->isReference())
		tmp = tmp->getReferredValue();

	return tmp;
}


/////////////////////////////////////////////////////////////////////////////
////


void ValueIdentifier::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<ValueIdentifier name=\"" << ID2STR(m_val) << "\" id=\"" << m_val << "\" />" << endl;
	// The value is known during the script execution, not now
}

ostream& operator<<(ostream& os, const ValueIdentifier& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

PTR_Value ValueIdentifier::add(const Value& right)          const { return right.add(*this); } // +
PTR_Value ValueIdentifier::add(const ValueNull& left)       const { return left.add(*getVal()); }
PTR_Value ValueIdentifier::add(const ValueBool& left)       const { return left.add(*getVal()); }
PTR_Value ValueIdentifier::add(const ValueInt& left)        const { return left.add(*getVal()); }
PTR_Value ValueIdentifier::add(const ValueFloat& left)      const { return left.add(*getVal()); }
PTR_Value ValueIdentifier::add(const ValueString& left)     const { return left.add(*getVal()); }
PTR_Value ValueIdentifier::add(const ValueStruct& left)     const { return left.add(*getVal()); }
PTR_Value ValueIdentifier::add(const ValueReference& left)  const { return left.getVal()->add(*getVal()); }
PTR_Value ValueIdentifier::add(const ValueIdentifier& left) const { return left.getVal()->add(*getVal()); }
PTR_Value ValueIdentifier::add(const ValueGraph& left)      const { return left.add(*getVal()); }
PTR_Value ValueIdentifier::add(const ValueVertex& left)     const { return left.add(*getVal()); }
PTR_Value ValueIdentifier::add(const ValueEdge& left)       const { return left.add(*getVal()); }
PTR_Value ValueIdentifier::add(const ValueVertexSet& left)  const { return left.add(*getVal()); }
PTR_Value ValueIdentifier::add(const ValueEdgeSet& left)    const { return left.add(*getVal()); }

PTR_Value ValueIdentifier::sub(const Value& right)          const { return right.sub(*this); } // -
PTR_Value ValueIdentifier::sub(const ValueNull& left)       const { return left.sub(*getVal()); }
PTR_Value ValueIdentifier::sub(const ValueBool& left)       const { return left.sub(*getVal()); }
PTR_Value ValueIdentifier::sub(const ValueInt& left)        const { return left.sub(*getVal()); }
PTR_Value ValueIdentifier::sub(const ValueFloat& left)      const { return left.sub(*getVal()); }
PTR_Value ValueIdentifier::sub(const ValueString& left)     const { return left.sub(*getVal()); }
PTR_Value ValueIdentifier::sub(const ValueStruct& left)     const { return left.sub(*getVal()); }
PTR_Value ValueIdentifier::sub(const ValueReference& left)  const { return left.getVal()->sub(*getVal()); }
PTR_Value ValueIdentifier::sub(const ValueIdentifier& left) const { return left.getVal()->sub(*getVal()); }
PTR_Value ValueIdentifier::sub(const ValueGraph& left)      const { return left.sub(*getVal()); }
PTR_Value ValueIdentifier::sub(const ValueVertex& left)     const { return left.sub(*getVal()); }
PTR_Value ValueIdentifier::sub(const ValueEdge& left)       const { return left.sub(*getVal()); }
PTR_Value ValueIdentifier::sub(const ValueVertexSet& left)  const { return left.sub(*getVal()); }
PTR_Value ValueIdentifier::sub(const ValueEdgeSet& left)    const { return left.sub(*getVal()); }

PTR_Value ValueIdentifier::mult(const Value& right)         const { return right.mult(*this); } // *
PTR_Value ValueIdentifier::mult(const ValueNull& left)      const { return left.mult(*getVal()); }
PTR_Value ValueIdentifier::mult(const ValueBool& left)      const { return left.mult(*getVal()); }
PTR_Value ValueIdentifier::mult(const ValueInt& left)       const { return left.mult(*getVal()); }
PTR_Value ValueIdentifier::mult(const ValueFloat& left)     const { return left.mult(*getVal()); }
PTR_Value ValueIdentifier::mult(const ValueString& left)    const { return left.mult(*getVal()); }
PTR_Value ValueIdentifier::mult(const ValueStruct& left)    const { return left.mult(*getVal()); }
PTR_Value ValueIdentifier::mult(const ValueReference& left) const { return left.getVal()->mult(*getVal()); }
PTR_Value ValueIdentifier::mult(const ValueIdentifier& left)const { return left.getVal()->mult(*getVal()); }
PTR_Value ValueIdentifier::mult(const ValueGraph& left)     const { return left.mult(*getVal()); }
PTR_Value ValueIdentifier::mult(const ValueVertex& left)    const { return left.mult(*getVal()); }
PTR_Value ValueIdentifier::mult(const ValueEdge& left)      const { return left.mult(*getVal()); }
PTR_Value ValueIdentifier::mult(const ValueVertexSet& left) const { return left.mult(*getVal()); }
PTR_Value ValueIdentifier::mult(const ValueEdgeSet& left)   const { return left.mult(*getVal()); }

PTR_Value ValueIdentifier::div(const Value& right)          const { return right.div(*this); } // /
PTR_Value ValueIdentifier::div(const ValueNull& left)       const { return left.div(*getVal()); }
PTR_Value ValueIdentifier::div(const ValueBool& left)       const { return left.div(*getVal()); }
PTR_Value ValueIdentifier::div(const ValueInt& left)        const { return left.div(*getVal()); }
PTR_Value ValueIdentifier::div(const ValueFloat& left)      const { return left.div(*getVal()); }
PTR_Value ValueIdentifier::div(const ValueString& left)     const { return left.div(*getVal()); }
PTR_Value ValueIdentifier::div(const ValueStruct& left)     const { return left.div(*getVal()); }
PTR_Value ValueIdentifier::div(const ValueReference& left)  const { return left.getVal()->div(*getVal()); }
PTR_Value ValueIdentifier::div(const ValueIdentifier& left) const { return left.getVal()->div(*getVal()); }
PTR_Value ValueIdentifier::div(const ValueGraph& left)      const { return left.div(*getVal()); }
PTR_Value ValueIdentifier::div(const ValueVertex& left)     const { return left.div(*getVal()); }
PTR_Value ValueIdentifier::div(const ValueEdge& left)       const { return left.div(*getVal()); }
PTR_Value ValueIdentifier::div(const ValueVertexSet& left)  const { return left.div(*getVal()); }
PTR_Value ValueIdentifier::div(const ValueEdgeSet& left)    const { return left.div(*getVal()); }

PTR_Value ValueIdentifier::mod(const Value& right)          const { return right.mod(*this); } // %
PTR_Value ValueIdentifier::mod(const ValueNull& left)       const { return left.mod(*getVal()); }
PTR_Value ValueIdentifier::mod(const ValueBool& left)       const { return left.mod(*getVal()); }
PTR_Value ValueIdentifier::mod(const ValueInt& left)        const { return left.mod(*getVal()); }
PTR_Value ValueIdentifier::mod(const ValueFloat& left)      const { return left.mod(*getVal()); }
PTR_Value ValueIdentifier::mod(const ValueString& left)     const { return left.mod(*getVal()); }
PTR_Value ValueIdentifier::mod(const ValueStruct& left)     const { return left.mod(*getVal()); }
PTR_Value ValueIdentifier::mod(const ValueReference& left)  const { return left.getVal()->mod(*getVal()); }
PTR_Value ValueIdentifier::mod(const ValueIdentifier& left) const { return left.getVal()->mod(*getVal()); }
PTR_Value ValueIdentifier::mod(const ValueGraph& left)      const { return left.mod(*getVal()); }
PTR_Value ValueIdentifier::mod(const ValueVertex& left)     const { return left.mod(*getVal()); }
PTR_Value ValueIdentifier::mod(const ValueEdge& left)       const { return left.mod(*getVal()); }
PTR_Value ValueIdentifier::mod(const ValueVertexSet& left)  const { return left.mod(*getVal()); }
PTR_Value ValueIdentifier::mod(const ValueEdgeSet& left)    const { return left.mod(*getVal()); }

PTR_Value ValueIdentifier::eq(const Value& right)           const { return right.eq(*this); } // ==
PTR_Value ValueIdentifier::eq(const ValueNull& left)        const { return left.eq(*getVal()); }
PTR_Value ValueIdentifier::eq(const ValueBool& left)        const { return left.eq(*getVal()); }
PTR_Value ValueIdentifier::eq(const ValueInt& left)         const { return left.eq(*getVal()); }
PTR_Value ValueIdentifier::eq(const ValueFloat& left)       const { return left.eq(*getVal()); }
PTR_Value ValueIdentifier::eq(const ValueString& left)      const { return left.eq(*getVal()); }
PTR_Value ValueIdentifier::eq(const ValueStruct& left)      const { return left.eq(*getVal()); }
PTR_Value ValueIdentifier::eq(const ValueReference& left)   const { return left.getVal()->eq(*getVal()); }
PTR_Value ValueIdentifier::eq(const ValueIdentifier& left)  const { return left.getVal()->eq(*getVal()); }
PTR_Value ValueIdentifier::eq(const ValueGraph& left)       const { return left.eq(*getVal()); }
PTR_Value ValueIdentifier::eq(const ValueVertex& left)      const { return left.eq(*getVal()); }
PTR_Value ValueIdentifier::eq(const ValueEdge& left)        const { return left.eq(*getVal()); }
PTR_Value ValueIdentifier::eq(const ValueVertexSet& left)   const { return left.eq(*getVal()); }
PTR_Value ValueIdentifier::eq(const ValueEdgeSet& left)     const { return left.eq(*getVal()); }

PTR_Value ValueIdentifier::ne(const Value& right)           const { return right.ne(*this); } // !=
PTR_Value ValueIdentifier::ne(const ValueNull& left)        const { return left.ne(*getVal()); }
PTR_Value ValueIdentifier::ne(const ValueBool& left)        const { return left.ne(*getVal()); }
PTR_Value ValueIdentifier::ne(const ValueInt& left)         const { return left.ne(*getVal()); }
PTR_Value ValueIdentifier::ne(const ValueFloat& left)       const { return left.ne(*getVal()); }
PTR_Value ValueIdentifier::ne(const ValueString& left)      const { return left.ne(*getVal()); }
PTR_Value ValueIdentifier::ne(const ValueStruct& left)      const { return left.ne(*getVal()); }
PTR_Value ValueIdentifier::ne(const ValueReference& left)   const { return left.getVal()->ne(*getVal()); }
PTR_Value ValueIdentifier::ne(const ValueIdentifier& left)  const { return left.getVal()->ne(*getVal()); }
PTR_Value ValueIdentifier::ne(const ValueGraph& left)       const { return left.ne(*getVal()); }
PTR_Value ValueIdentifier::ne(const ValueVertex& left)      const { return left.ne(*getVal()); }
PTR_Value ValueIdentifier::ne(const ValueEdge& left)        const { return left.ne(*getVal()); }
PTR_Value ValueIdentifier::ne(const ValueVertexSet& left)   const { return left.ne(*getVal()); }
PTR_Value ValueIdentifier::ne(const ValueEdgeSet& left)     const { return left.ne(*getVal()); }

PTR_Value ValueIdentifier::le(const Value& right)           const { return right.le(*this); } // <=
PTR_Value ValueIdentifier::le(const ValueNull& left)        const { return left.le(*getVal()); }
PTR_Value ValueIdentifier::le(const ValueBool& left)        const { return left.le(*getVal()); }
PTR_Value ValueIdentifier::le(const ValueInt& left)         const { return left.le(*getVal()); }
PTR_Value ValueIdentifier::le(const ValueFloat& left)       const { return left.le(*getVal()); }
PTR_Value ValueIdentifier::le(const ValueString& left)      const { return left.le(*getVal()); }
PTR_Value ValueIdentifier::le(const ValueStruct& left)      const { return left.le(*getVal()); }
PTR_Value ValueIdentifier::le(const ValueReference& left)   const { return left.getVal()->le(*getVal()); }
PTR_Value ValueIdentifier::le(const ValueIdentifier& left)  const { return left.getVal()->le(*getVal()); }
PTR_Value ValueIdentifier::le(const ValueGraph& left)       const { return left.le(*getVal()); }
PTR_Value ValueIdentifier::le(const ValueVertex& left)      const { return left.le(*getVal()); }
PTR_Value ValueIdentifier::le(const ValueEdge& left)        const { return left.le(*getVal()); }
PTR_Value ValueIdentifier::le(const ValueVertexSet& left)   const { return left.le(*getVal()); }
PTR_Value ValueIdentifier::le(const ValueEdgeSet& left)     const { return left.le(*getVal()); }

PTR_Value ValueIdentifier::ge(const Value& right)           const { return right.ge(*this); } // >=
PTR_Value ValueIdentifier::ge(const ValueNull& left)        const { return left.ge(*getVal()); }
PTR_Value ValueIdentifier::ge(const ValueBool& left)        const { return left.ge(*getVal()); }
PTR_Value ValueIdentifier::ge(const ValueInt& left)         const { return left.ge(*getVal()); }
PTR_Value ValueIdentifier::ge(const ValueFloat& left)       const { return left.ge(*getVal()); }
PTR_Value ValueIdentifier::ge(const ValueString& left)      const { return left.ge(*getVal()); }
PTR_Value ValueIdentifier::ge(const ValueStruct& left)      const { return left.ge(*getVal()); }
PTR_Value ValueIdentifier::ge(const ValueReference& left)   const { return left.getVal()->ge(*getVal()); }
PTR_Value ValueIdentifier::ge(const ValueIdentifier& left)  const { return left.getVal()->ge(*getVal()); }
PTR_Value ValueIdentifier::ge(const ValueGraph& left)       const { return left.ge(*getVal()); }
PTR_Value ValueIdentifier::ge(const ValueVertex& left)      const { return left.ge(*getVal()); }
PTR_Value ValueIdentifier::ge(const ValueEdge& left)        const { return left.ge(*getVal()); }
PTR_Value ValueIdentifier::ge(const ValueVertexSet& left)   const { return left.ge(*getVal()); }
PTR_Value ValueIdentifier::ge(const ValueEdgeSet& left)     const { return left.ge(*getVal()); }

PTR_Value ValueIdentifier::lt(const Value& right)           const { return right.lt(*this); } // <
PTR_Value ValueIdentifier::lt(const ValueNull& left)        const { return left.lt(*getVal()); }
PTR_Value ValueIdentifier::lt(const ValueBool& left)        const { return left.lt(*getVal()); }
PTR_Value ValueIdentifier::lt(const ValueInt& left)         const { return left.lt(*getVal()); }
PTR_Value ValueIdentifier::lt(const ValueFloat& left)       const { return left.lt(*getVal()); }
PTR_Value ValueIdentifier::lt(const ValueString& left)      const { return left.lt(*getVal()); }
PTR_Value ValueIdentifier::lt(const ValueStruct& left)      const { return left.lt(*getVal()); }
PTR_Value ValueIdentifier::lt(const ValueReference& left)   const { return left.getVal()->lt(*getVal()); }
PTR_Value ValueIdentifier::lt(const ValueIdentifier& left)  const { return left.getVal()->lt(*getVal()); }
PTR_Value ValueIdentifier::lt(const ValueGraph& left)       const { return left.lt(*getVal()); }
PTR_Value ValueIdentifier::lt(const ValueVertex& left)      const { return left.lt(*getVal()); }
PTR_Value ValueIdentifier::lt(const ValueEdge& left)        const { return left.lt(*getVal()); }
PTR_Value ValueIdentifier::lt(const ValueVertexSet& left)   const { return left.lt(*getVal()); }
PTR_Value ValueIdentifier::lt(const ValueEdgeSet& left)     const { return left.lt(*getVal()); }

PTR_Value ValueIdentifier::gt(const Value& right)           const { return right.gt(*this); } // >
PTR_Value ValueIdentifier::gt(const ValueNull& left)        const { return left.gt(*getVal()); }
PTR_Value ValueIdentifier::gt(const ValueBool& left)        const { return left.gt(*getVal()); }
PTR_Value ValueIdentifier::gt(const ValueInt& left)         const { return left.gt(*getVal()); }
PTR_Value ValueIdentifier::gt(const ValueFloat& left)       const { return left.gt(*getVal()); }
PTR_Value ValueIdentifier::gt(const ValueString& left)      const { return left.gt(*getVal()); }
PTR_Value ValueIdentifier::gt(const ValueStruct& left)      const { return left.gt(*getVal()); }
PTR_Value ValueIdentifier::gt(const ValueReference& left)   const { return left.getVal()->gt(*getVal()); }
PTR_Value ValueIdentifier::gt(const ValueIdentifier& left)  const { return left.getVal()->gt(*getVal()); }
PTR_Value ValueIdentifier::gt(const ValueGraph& left)       const { return left.gt(*getVal()); }
PTR_Value ValueIdentifier::gt(const ValueVertex& left)      const { return left.gt(*getVal()); }
PTR_Value ValueIdentifier::gt(const ValueEdge& left)        const { return left.gt(*getVal()); }
PTR_Value ValueIdentifier::gt(const ValueVertexSet& left)   const { return left.gt(*getVal()); }
PTR_Value ValueIdentifier::gt(const ValueEdgeSet& left)     const { return left.gt(*getVal()); }

PTR_Value ValueIdentifier::member(const Value& right)             const { return right.member(*this); } // .
PTR_Value ValueIdentifier::member(const ValueNull& /*left*/)      const { WARN << _("Member access to the NULL variable, operation is not supported") << endl; return VALUENULL; }
PTR_Value ValueIdentifier::member(const ValueBool& /*left*/)      const { WARN << _("Member access to the bool variable, operation is not supported") << endl; return VALUENULL; }
PTR_Value ValueIdentifier::member(const ValueInt& /*left*/)       const { WARN << _("Member access to the int variable, operation is not supported") << endl; return VALUENULL; }
PTR_Value ValueIdentifier::member(const ValueFloat& /*left*/)     const { WARN << _("Member access to the float variable, operation is not supported") << endl; return VALUENULL; }
PTR_Value ValueIdentifier::member(const ValueString& /*left*/)    const { WARN << _("Member access to the string variable, operation is not supported") << endl; return VALUENULL; }
PTR_Value ValueIdentifier::member(const ValueStruct& left)        const { return const_cast<ValueStruct&>(left).getItem(m_val); }
PTR_Value ValueIdentifier::member(const ValueReference& left)     const { return left.getVal()->member(*getVal()); }
PTR_Value ValueIdentifier::member(const ValueIdentifier& left)    const { return left.getVal()->member(*getVal()); }
PTR_Value ValueIdentifier::member(const ValueGraph& /*left*/)     const { WARN << _("Member access to the graph variable, operation is not supported") << endl; return VALUENULL; }
PTR_Value ValueIdentifier::member(const ValueVertex& left)        const { return const_cast<ValueVertex&>(left).getItem(m_val); }
PTR_Value ValueIdentifier::member(const ValueEdge& left)          const { return const_cast<ValueEdge&>(left).getItem(m_val); }
PTR_Value ValueIdentifier::member(const ValueVertexSet& /*left*/) const { WARN << _("Member access to the VertexSet variable, operation is not supported") << endl; return VALUENULL; }
PTR_Value ValueIdentifier::member(const ValueEdgeSet& /*left*/)   const { WARN << _("Member access to the EdgeSet variable, operation is not supported") << endl; return VALUENULL; }

PTR_Value ValueIdentifier::index(const Value& right)         const { return right.index(*this); } // []
PTR_Value ValueIdentifier::index(const ValueNull& left)      const { return left.index(*getVal()); }
PTR_Value ValueIdentifier::index(const ValueBool& left)      const { return left.index(*getVal()); }
PTR_Value ValueIdentifier::index(const ValueInt& left)       const { return left.index(*getVal()); }
PTR_Value ValueIdentifier::index(const ValueFloat& left)     const { return left.index(*getVal()); }
PTR_Value ValueIdentifier::index(const ValueString& left)    const { return left.index(*getVal()); }
PTR_Value ValueIdentifier::index(const ValueStruct& left)    const { return left.index(*getVal()); }
PTR_Value ValueIdentifier::index(const ValueReference& left) const { return left.getVal()->index(*getVal()); }
PTR_Value ValueIdentifier::index(const ValueIdentifier& left)const { return left.getVal()->index(*getVal()); }
PTR_Value ValueIdentifier::index(const ValueGraph& left)     const { return left.index(*getVal()); }
PTR_Value ValueIdentifier::index(const ValueVertex& left)    const { return left.index(*getVal()); }
PTR_Value ValueIdentifier::index(const ValueEdge& left)      const { return left.index(*getVal()); }
PTR_Value ValueIdentifier::index(const ValueVertexSet& left) const { return left.index(*getVal()); }
PTR_Value ValueIdentifier::index(const ValueEdgeSet& left)   const { return left.index(*getVal()); }

PTR_Value ValueIdentifier::logNOT(void)                     const { return CONTEXT.getLocalVariable(m_val)->logNOT(); } // !
