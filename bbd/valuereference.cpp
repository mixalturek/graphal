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


#include "valuereference.hpp"
#include "valuenull.hpp"
#include "valuebool.hpp"
#include "valueint.hpp"
#include "valuefloat.hpp"
#include "valuestring.hpp"
#include "valuestruct.hpp"
#include "valueidentifier.hpp"
#include "valuegraph.hpp"
#include "valuevertex.hpp"
#include "valueedge.hpp"
#include "valuevertexset.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueReference::ValueReference(CountPtr<Value> val)
	: Value(),
	m_val(val)
{
	assert(!val->isReference());
}


ValueReference::~ValueReference()
{

}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueReference::getReferredValue(void) const
{
	CountPtr<Value> tmp(m_val);

	while(tmp->isReference())
		tmp = tmp->getReferredValue();

	return tmp;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueReference::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
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

PTR_Value ValueReference::add(const Value& right)          const { return right.add(*this); } // +
PTR_Value ValueReference::add(const ValueNull& left)       const { return left.add(*m_val); }
PTR_Value ValueReference::add(const ValueBool& left)       const { return left.add(*m_val); }
PTR_Value ValueReference::add(const ValueInt& left)        const { return left.add(*m_val); }
PTR_Value ValueReference::add(const ValueFloat& left)      const { return left.add(*m_val); }
PTR_Value ValueReference::add(const ValueString& left)     const { return left.add(*m_val); }
PTR_Value ValueReference::add(const ValueStruct& left)     const { return left.add(*m_val); }
PTR_Value ValueReference::add(const ValueReference& left)  const { return left.getVal()->add(*m_val); }
PTR_Value ValueReference::add(const ValueIdentifier& left) const { return left.getVal()->add(*m_val); }
PTR_Value ValueReference::add(const ValueGraph& left)      const { return left.add(*m_val); }
PTR_Value ValueReference::add(const ValueVertex& left)     const { return left.add(*m_val); }
PTR_Value ValueReference::add(const ValueEdge& left)       const { return left.add(*m_val); }
PTR_Value ValueReference::add(const ValueVertexSet& left)  const { return left.add(*m_val); }
PTR_Value ValueReference::add(const ValueEdgeSet& left)    const { return left.add(*m_val); }

PTR_Value ValueReference::sub(const Value& right)          const { return right.sub(*this); } // -
PTR_Value ValueReference::sub(const ValueNull& left)       const { return left.sub(*m_val); }
PTR_Value ValueReference::sub(const ValueBool& left)       const { return left.sub(*m_val); }
PTR_Value ValueReference::sub(const ValueInt& left)        const { return left.sub(*m_val); }
PTR_Value ValueReference::sub(const ValueFloat& left)      const { return left.sub(*m_val); }
PTR_Value ValueReference::sub(const ValueString& left)     const { return left.sub(*m_val); }
PTR_Value ValueReference::sub(const ValueStruct& left)     const { return left.sub(*m_val); }
PTR_Value ValueReference::sub(const ValueReference& left)  const { return left.getVal()->sub(*m_val); }
PTR_Value ValueReference::sub(const ValueIdentifier& left) const { return left.getVal()->sub(*m_val); }
PTR_Value ValueReference::sub(const ValueGraph& left)      const { return left.sub(*m_val); }
PTR_Value ValueReference::sub(const ValueVertex& left)     const { return left.sub(*m_val); }
PTR_Value ValueReference::sub(const ValueEdge& left)       const { return left.sub(*m_val); }
PTR_Value ValueReference::sub(const ValueVertexSet& left)  const { return left.sub(*m_val); }
PTR_Value ValueReference::sub(const ValueEdgeSet& left)    const { return left.sub(*m_val); }

PTR_Value ValueReference::mult(const Value& right)         const { return right.mult(*this); } // *
PTR_Value ValueReference::mult(const ValueNull& left)      const { return left.mult(*m_val); }
PTR_Value ValueReference::mult(const ValueBool& left)      const { return left.mult(*m_val); }
PTR_Value ValueReference::mult(const ValueInt& left)       const { return left.mult(*m_val); }
PTR_Value ValueReference::mult(const ValueFloat& left)     const { return left.mult(*m_val); }
PTR_Value ValueReference::mult(const ValueString& left)    const { return left.mult(*m_val); }
PTR_Value ValueReference::mult(const ValueStruct& left)    const { return left.mult(*m_val); }
PTR_Value ValueReference::mult(const ValueReference& left) const { return left.getVal()->mult(*m_val); }
PTR_Value ValueReference::mult(const ValueIdentifier& left)const { return left.getVal()->mult(*m_val); }
PTR_Value ValueReference::mult(const ValueGraph& left)     const { return left.mult(*m_val); }
PTR_Value ValueReference::mult(const ValueVertex& left)    const { return left.mult(*m_val); }
PTR_Value ValueReference::mult(const ValueEdge& left)      const { return left.mult(*m_val); }
PTR_Value ValueReference::mult(const ValueVertexSet& left) const { return left.mult(*m_val); }
PTR_Value ValueReference::mult(const ValueEdgeSet& left)   const { return left.mult(*m_val); }

PTR_Value ValueReference::div(const Value& right)          const { return right.div(*this); } // /
PTR_Value ValueReference::div(const ValueNull& left)       const { return left.div(*m_val); }
PTR_Value ValueReference::div(const ValueBool& left)       const { return left.div(*m_val); }
PTR_Value ValueReference::div(const ValueInt& left)        const { return left.div(*m_val); }
PTR_Value ValueReference::div(const ValueFloat& left)      const { return left.div(*m_val); }
PTR_Value ValueReference::div(const ValueString& left)     const { return left.div(*m_val); }
PTR_Value ValueReference::div(const ValueStruct& left)     const { return left.div(*m_val); }
PTR_Value ValueReference::div(const ValueReference& left)  const { return left.getVal()->div(*m_val); }
PTR_Value ValueReference::div(const ValueIdentifier& left) const { return left.getVal()->div(*m_val); }
PTR_Value ValueReference::div(const ValueGraph& left)      const { return left.div(*m_val); }
PTR_Value ValueReference::div(const ValueVertex& left)     const { return left.div(*m_val); }
PTR_Value ValueReference::div(const ValueEdge& left)       const { return left.div(*m_val); }
PTR_Value ValueReference::div(const ValueVertexSet& left)  const { return left.div(*m_val); }
PTR_Value ValueReference::div(const ValueEdgeSet& left)    const { return left.div(*m_val); }

PTR_Value ValueReference::mod(const Value& right)          const { return right.mod(*this); } // %
PTR_Value ValueReference::mod(const ValueNull& left)       const { return left.mod(*m_val); }
PTR_Value ValueReference::mod(const ValueBool& left)       const { return left.mod(*m_val); }
PTR_Value ValueReference::mod(const ValueInt& left)        const { return left.mod(*m_val); }
PTR_Value ValueReference::mod(const ValueFloat& left)      const { return left.mod(*m_val); }
PTR_Value ValueReference::mod(const ValueString& left)     const { return left.mod(*m_val); }
PTR_Value ValueReference::mod(const ValueStruct& left)     const { return left.mod(*m_val); }
PTR_Value ValueReference::mod(const ValueReference& left)  const { return left.getVal()->mod(*m_val); }
PTR_Value ValueReference::mod(const ValueIdentifier& left) const { return left.getVal()->mod(*m_val); }
PTR_Value ValueReference::mod(const ValueGraph& left)      const { return left.mod(*m_val); }
PTR_Value ValueReference::mod(const ValueVertex& left)     const { return left.mod(*m_val); }
PTR_Value ValueReference::mod(const ValueEdge& left)       const { return left.mod(*m_val); }
PTR_Value ValueReference::mod(const ValueVertexSet& left)  const { return left.mod(*m_val); }
PTR_Value ValueReference::mod(const ValueEdgeSet& left)    const { return left.mod(*m_val); }

PTR_Value ValueReference::eq(const Value& right)           const { return right.eq(*this); } // ==
PTR_Value ValueReference::eq(const ValueNull& left)        const { return left.eq(*m_val); }
PTR_Value ValueReference::eq(const ValueBool& left)        const { return left.eq(*m_val); }
PTR_Value ValueReference::eq(const ValueInt& left)         const { return left.eq(*m_val); }
PTR_Value ValueReference::eq(const ValueFloat& left)       const { return left.eq(*m_val); }
PTR_Value ValueReference::eq(const ValueString& left)      const { return left.eq(*m_val); }
PTR_Value ValueReference::eq(const ValueStruct& left)      const { return left.eq(*m_val); }
PTR_Value ValueReference::eq(const ValueReference& left)   const { return left.getVal()->eq(*m_val); }
PTR_Value ValueReference::eq(const ValueIdentifier& left)  const { return left.getVal()->eq(*m_val); }
PTR_Value ValueReference::eq(const ValueGraph& left)       const { return left.eq(*m_val); }
PTR_Value ValueReference::eq(const ValueVertex& left)      const { return left.eq(*m_val); }
PTR_Value ValueReference::eq(const ValueEdge& left)        const { return left.eq(*m_val); }
PTR_Value ValueReference::eq(const ValueVertexSet& left)   const { return left.eq(*m_val); }
PTR_Value ValueReference::eq(const ValueEdgeSet& left)     const { return left.eq(*m_val); }

PTR_Value ValueReference::ne(const Value& right)           const { return right.ne(*this); } // !=
PTR_Value ValueReference::ne(const ValueNull& left)        const { return left.ne(*m_val); }
PTR_Value ValueReference::ne(const ValueBool& left)        const { return left.ne(*m_val); }
PTR_Value ValueReference::ne(const ValueInt& left)         const { return left.ne(*m_val); }
PTR_Value ValueReference::ne(const ValueFloat& left)       const { return left.ne(*m_val); }
PTR_Value ValueReference::ne(const ValueString& left)      const { return left.ne(*m_val); }
PTR_Value ValueReference::ne(const ValueStruct& left)      const { return left.ne(*m_val); }
PTR_Value ValueReference::ne(const ValueReference& left)   const { return left.getVal()->ne(*m_val); }
PTR_Value ValueReference::ne(const ValueIdentifier& left)  const { return left.getVal()->ne(*m_val); }
PTR_Value ValueReference::ne(const ValueGraph& left)       const { return left.ne(*m_val); }
PTR_Value ValueReference::ne(const ValueVertex& left)      const { return left.ne(*m_val); }
PTR_Value ValueReference::ne(const ValueEdge& left)        const { return left.ne(*m_val); }
PTR_Value ValueReference::ne(const ValueVertexSet& left)   const { return left.ne(*m_val); }
PTR_Value ValueReference::ne(const ValueEdgeSet& left)     const { return left.ne(*m_val); }

PTR_Value ValueReference::le(const Value& right)           const { return right.le(*this); } // <=
PTR_Value ValueReference::le(const ValueNull& left)        const { return left.le(*m_val); }
PTR_Value ValueReference::le(const ValueBool& left)        const { return left.le(*m_val); }
PTR_Value ValueReference::le(const ValueInt& left)         const { return left.le(*m_val); }
PTR_Value ValueReference::le(const ValueFloat& left)       const { return left.le(*m_val); }
PTR_Value ValueReference::le(const ValueString& left)      const { return left.le(*m_val); }
PTR_Value ValueReference::le(const ValueStruct& left)      const { return left.le(*m_val); }
PTR_Value ValueReference::le(const ValueReference& left)   const { return left.getVal()->le(*m_val); }
PTR_Value ValueReference::le(const ValueIdentifier& left)  const { return left.getVal()->le(*m_val); }
PTR_Value ValueReference::le(const ValueGraph& left)       const { return left.le(*m_val); }
PTR_Value ValueReference::le(const ValueVertex& left)      const { return left.le(*m_val); }
PTR_Value ValueReference::le(const ValueEdge& left)        const { return left.le(*m_val); }
PTR_Value ValueReference::le(const ValueVertexSet& left)   const { return left.le(*m_val); }
PTR_Value ValueReference::le(const ValueEdgeSet& left)     const { return left.le(*m_val); }

PTR_Value ValueReference::ge(const Value& right)           const { return right.ge(*this); } // >=
PTR_Value ValueReference::ge(const ValueNull& left)        const { return left.ge(*m_val); }
PTR_Value ValueReference::ge(const ValueBool& left)        const { return left.ge(*m_val); }
PTR_Value ValueReference::ge(const ValueInt& left)         const { return left.ge(*m_val); }
PTR_Value ValueReference::ge(const ValueFloat& left)       const { return left.ge(*m_val); }
PTR_Value ValueReference::ge(const ValueString& left)      const { return left.ge(*m_val); }
PTR_Value ValueReference::ge(const ValueStruct& left)      const { return left.ge(*m_val); }
PTR_Value ValueReference::ge(const ValueReference& left)   const { return left.getVal()->ge(*m_val); }
PTR_Value ValueReference::ge(const ValueIdentifier& left)  const { return left.getVal()->ge(*m_val); }
PTR_Value ValueReference::ge(const ValueGraph& left)       const { return left.ge(*m_val); }
PTR_Value ValueReference::ge(const ValueVertex& left)      const { return left.ge(*m_val); }
PTR_Value ValueReference::ge(const ValueEdge& left)        const { return left.ge(*m_val); }
PTR_Value ValueReference::ge(const ValueVertexSet& left)   const { return left.ge(*m_val); }
PTR_Value ValueReference::ge(const ValueEdgeSet& left)     const { return left.ge(*m_val); }

PTR_Value ValueReference::lt(const Value& right)           const { return right.lt(*this); } // <
PTR_Value ValueReference::lt(const ValueNull& left)        const { return left.lt(*m_val); }
PTR_Value ValueReference::lt(const ValueBool& left)        const { return left.lt(*m_val); }
PTR_Value ValueReference::lt(const ValueInt& left)         const { return left.lt(*m_val); }
PTR_Value ValueReference::lt(const ValueFloat& left)       const { return left.lt(*m_val); }
PTR_Value ValueReference::lt(const ValueString& left)      const { return left.lt(*m_val); }
PTR_Value ValueReference::lt(const ValueStruct& left)      const { return left.lt(*m_val); }
PTR_Value ValueReference::lt(const ValueReference& left)   const { return left.getVal()->lt(*m_val); }
PTR_Value ValueReference::lt(const ValueIdentifier& left)  const { return left.getVal()->lt(*m_val); }
PTR_Value ValueReference::lt(const ValueGraph& left)       const { return left.lt(*m_val); }
PTR_Value ValueReference::lt(const ValueVertex& left)      const { return left.lt(*m_val); }
PTR_Value ValueReference::lt(const ValueEdge& left)        const { return left.lt(*m_val); }
PTR_Value ValueReference::lt(const ValueVertexSet& left)   const { return left.lt(*m_val); }
PTR_Value ValueReference::lt(const ValueEdgeSet& left)     const { return left.lt(*m_val); }

PTR_Value ValueReference::gt(const Value& right)           const { return right.gt(*this); } // >
PTR_Value ValueReference::gt(const ValueNull& left)        const { return left.gt(*m_val); }
PTR_Value ValueReference::gt(const ValueBool& left)        const { return left.gt(*m_val); }
PTR_Value ValueReference::gt(const ValueInt& left)         const { return left.gt(*m_val); }
PTR_Value ValueReference::gt(const ValueFloat& left)       const { return left.gt(*m_val); }
PTR_Value ValueReference::gt(const ValueString& left)      const { return left.gt(*m_val); }
PTR_Value ValueReference::gt(const ValueStruct& left)      const { return left.gt(*m_val); }
PTR_Value ValueReference::gt(const ValueReference& left)   const { return left.getVal()->gt(*m_val); }
PTR_Value ValueReference::gt(const ValueIdentifier& left)  const { return left.getVal()->gt(*m_val); }
PTR_Value ValueReference::gt(const ValueGraph& left)       const { return left.gt(*m_val); }
PTR_Value ValueReference::gt(const ValueVertex& left)      const { return left.gt(*m_val); }
PTR_Value ValueReference::gt(const ValueEdge& left)        const { return left.gt(*m_val); }
PTR_Value ValueReference::gt(const ValueVertexSet& left)   const { return left.gt(*m_val); }
PTR_Value ValueReference::gt(const ValueEdgeSet& left)     const { return left.gt(*m_val); }

PTR_Value ValueReference::member(const Value& right)         const { return right.member(*this); } // .
PTR_Value ValueReference::member(const ValueNull& left)      const { return left.member(*m_val); }
PTR_Value ValueReference::member(const ValueBool& left)      const { return left.member(*m_val); }
PTR_Value ValueReference::member(const ValueInt& left)       const { return left.member(*m_val); }
PTR_Value ValueReference::member(const ValueFloat& left)     const { return left.member(*m_val); }
PTR_Value ValueReference::member(const ValueString& left)    const { return left.member(*m_val); }
PTR_Value ValueReference::member(const ValueStruct& left)    const { return left.member(*m_val); }
PTR_Value ValueReference::member(const ValueReference& left) const { return left.getVal()->member(*m_val); }
PTR_Value ValueReference::member(const ValueIdentifier& left)const { return left.getVal()->member(*m_val); }
PTR_Value ValueReference::member(const ValueGraph& left)     const { return left.member(*m_val); }
PTR_Value ValueReference::member(const ValueVertex& left)    const { return left.member(*m_val); }
PTR_Value ValueReference::member(const ValueEdge& left)      const { return left.member(*m_val); }
PTR_Value ValueReference::member(const ValueVertexSet& left) const { return left.member(*m_val); }
PTR_Value ValueReference::member(const ValueEdgeSet& left)   const { return left.member(*m_val); }

PTR_Value ValueReference::index(const Value& right)         const { return right.index(*this); } // []
PTR_Value ValueReference::index(const ValueNull& left)      const { return left.index(*m_val); }
PTR_Value ValueReference::index(const ValueBool& left)      const { return left.index(*m_val); }
PTR_Value ValueReference::index(const ValueInt& left)       const { return left.index(*m_val); }
PTR_Value ValueReference::index(const ValueFloat& left)     const { return left.index(*m_val); }
PTR_Value ValueReference::index(const ValueString& left)    const { return left.index(*m_val); }
PTR_Value ValueReference::index(const ValueStruct& left)    const { return left.index(*m_val); }
PTR_Value ValueReference::index(const ValueReference& left) const { return left.getVal()->index(*m_val); }
PTR_Value ValueReference::index(const ValueIdentifier& left)const { return left.getVal()->index(*m_val); }
PTR_Value ValueReference::index(const ValueGraph& left)     const { return left.index(*m_val); }
PTR_Value ValueReference::index(const ValueVertex& left)    const { return left.index(*m_val); }
PTR_Value ValueReference::index(const ValueEdge& left)      const { return left.index(*m_val); }
PTR_Value ValueReference::index(const ValueVertexSet& left) const { return left.index(*m_val); }
PTR_Value ValueReference::index(const ValueEdgeSet& left)   const { return left.index(*m_val); }

PTR_Value ValueReference::logNOT(void)                      const { return m_val->logNOT(); } // !
