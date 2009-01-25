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


#include "value.hpp"
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

PTR_Value Value::logAND(const Value& right) const
{
	return (this->toBool() && right.toBool()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
}

PTR_Value Value::logOR(const Value& right) const
{
	return (this->toBool() || right.toBool()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;
}


/////////////////////////////////////////////////////////////////////////////
////

// +
PTR_Value Value::add(const ValueNull& /* left */)       const { return VALUENULL; }
PTR_Value Value::add(const ValueBool& /* left */)       const { return VALUENULL; }
PTR_Value Value::add(const ValueInt& /* left */)        const { return VALUENULL; }
PTR_Value Value::add(const ValueFloat& /* left */)      const { return VALUENULL; }
PTR_Value Value::add(const ValueString& /* left */)     const { return VALUENULL; }
PTR_Value Value::add(const ValueStruct& /* left */)     const { return VALUENULL; }
PTR_Value Value::add(const ValueReference& left)        const { return left.getVal()->add(*this);  }
PTR_Value Value::add(const ValueGraph& /* left */)      const { return VALUENULL; }
PTR_Value Value::add(const ValueVertex& /* left */)     const { return VALUENULL; }
PTR_Value Value::add(const ValueEdge& /* left */)       const { return VALUENULL; }
PTR_Value Value::add(const ValueVertexSet& /* left */)  const { return VALUENULL; }
PTR_Value Value::add(const ValueEdgeSet& /* left */)    const { return VALUENULL; }

// -
PTR_Value Value::sub(const ValueNull& /* left */)       const { return VALUENULL; }
PTR_Value Value::sub(const ValueBool& /* left */)       const { return VALUENULL; }
PTR_Value Value::sub(const ValueInt& /* left */)        const { return VALUENULL; }
PTR_Value Value::sub(const ValueFloat& /* left */)      const { return VALUENULL; }
PTR_Value Value::sub(const ValueString& /* left */)     const { return VALUENULL; }
PTR_Value Value::sub(const ValueStruct& /* left */)     const { return VALUENULL; }
PTR_Value Value::sub(const ValueReference& left)        const { return left.getVal()->sub(*this);  }
PTR_Value Value::sub(const ValueGraph& /* left */)      const { return VALUENULL; }
PTR_Value Value::sub(const ValueVertex& /* left */)     const { return VALUENULL; }
PTR_Value Value::sub(const ValueEdge& /* left */)       const { return VALUENULL; }
PTR_Value Value::sub(const ValueVertexSet& /* left */)  const { return VALUENULL; }
PTR_Value Value::sub(const ValueEdgeSet& /* left */)    const { return VALUENULL; }

// *
PTR_Value Value::mult(const ValueNull& /* left */)      const { return VALUENULL; }
PTR_Value Value::mult(const ValueBool& /* left */)      const { return VALUENULL; }
PTR_Value Value::mult(const ValueInt& /* left */)       const { return VALUENULL; }
PTR_Value Value::mult(const ValueFloat& /* left */)     const { return VALUENULL; }
PTR_Value Value::mult(const ValueString& /* left */)    const { return VALUENULL; }
PTR_Value Value::mult(const ValueStruct& /* left */)    const { return VALUENULL; }
PTR_Value Value::mult(const ValueReference& left)       const { return left.getVal()->mult(*this); }
PTR_Value Value::mult(const ValueGraph& /* left */)     const { return VALUENULL; }
PTR_Value Value::mult(const ValueVertex& /* left */)    const { return VALUENULL; }
PTR_Value Value::mult(const ValueEdge& /* left */)      const { return VALUENULL; }
PTR_Value Value::mult(const ValueVertexSet& /* left */) const { return VALUENULL; }
PTR_Value Value::mult(const ValueEdgeSet& /* left */)   const { return VALUENULL; }

// /
PTR_Value Value::div(const ValueNull& /* left */)       const { return VALUENULL; }
PTR_Value Value::div(const ValueBool& /* left */)       const { return VALUENULL; }
PTR_Value Value::div(const ValueInt& /* left */)        const { return VALUENULL; }
PTR_Value Value::div(const ValueFloat& /* left */)      const { return VALUENULL; }
PTR_Value Value::div(const ValueString& /* left */)     const { return VALUENULL; }
PTR_Value Value::div(const ValueStruct& /* left */)     const { return VALUENULL; }
PTR_Value Value::div(const ValueReference& left)        const { return left.getVal()->div(*this);  }
PTR_Value Value::div(const ValueGraph& /* left */)      const { return VALUENULL; }
PTR_Value Value::div(const ValueVertex& /* left */)     const { return VALUENULL; }
PTR_Value Value::div(const ValueEdge& /* left */)       const { return VALUENULL; }
PTR_Value Value::div(const ValueVertexSet& /* left */)  const { return VALUENULL; }
PTR_Value Value::div(const ValueEdgeSet& /* left */)    const { return VALUENULL; }

// %
PTR_Value Value::mod(const ValueNull& /* left */)       const { return VALUENULL; }
PTR_Value Value::mod(const ValueBool& /* left */)       const { return VALUENULL; }
PTR_Value Value::mod(const ValueInt& /* left */)        const { return VALUENULL; }
PTR_Value Value::mod(const ValueFloat& /* left */)      const { return VALUENULL; }
PTR_Value Value::mod(const ValueString& /* left */)     const { return VALUENULL; }
PTR_Value Value::mod(const ValueStruct& /* left */)     const { return VALUENULL; }
PTR_Value Value::mod(const ValueReference& left)        const { return left.getVal()->mod(*this);  }
PTR_Value Value::mod(const ValueGraph& /* left */)      const { return VALUENULL; }
PTR_Value Value::mod(const ValueVertex& /* left */)     const { return VALUENULL; }
PTR_Value Value::mod(const ValueEdge& /* left */)       const { return VALUENULL; }
PTR_Value Value::mod(const ValueVertexSet& /* left */)  const { return VALUENULL; }
PTR_Value Value::mod(const ValueEdgeSet& /* left */)    const { return VALUENULL; }

// ==
PTR_Value Value::eq(const ValueNull& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::eq(const ValueBool& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::eq(const ValueInt& /* left */)         const { return VALUEBOOL_FALSE; }
PTR_Value Value::eq(const ValueFloat& /* left */)       const { return VALUEBOOL_FALSE; }
PTR_Value Value::eq(const ValueString& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::eq(const ValueStruct& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::eq(const ValueReference& left)         const { return left.getVal()->eq(*this);        }
PTR_Value Value::eq(const ValueGraph& /* left */)       const { return VALUEBOOL_FALSE; }
PTR_Value Value::eq(const ValueVertex& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::eq(const ValueEdge& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::eq(const ValueVertexSet& /* left */)   const { return VALUEBOOL_FALSE; }
PTR_Value Value::eq(const ValueEdgeSet& /* left */)     const { return VALUEBOOL_FALSE; }

// !=
PTR_Value Value::ne(const ValueNull& /* left */)        const { return VALUEBOOL_TRUE; }
PTR_Value Value::ne(const ValueBool& /* left */)        const { return VALUEBOOL_TRUE; }
PTR_Value Value::ne(const ValueInt& /* left */)         const { return VALUEBOOL_TRUE; }
PTR_Value Value::ne(const ValueFloat& /* left */)       const { return VALUEBOOL_TRUE; }
PTR_Value Value::ne(const ValueString& /* left */)      const { return VALUEBOOL_TRUE; }
PTR_Value Value::ne(const ValueStruct& /* left */)      const { return VALUEBOOL_TRUE; }
PTR_Value Value::ne(const ValueReference& left)         const { return left.getVal()->ne(*this);        }
PTR_Value Value::ne(const ValueGraph& /* left */)       const { return VALUEBOOL_TRUE; }
PTR_Value Value::ne(const ValueVertex& /* left */)      const { return VALUEBOOL_TRUE; }
PTR_Value Value::ne(const ValueEdge& /* left */)        const { return VALUEBOOL_TRUE; }
PTR_Value Value::ne(const ValueVertexSet& /* left */)   const { return VALUEBOOL_TRUE; }
PTR_Value Value::ne(const ValueEdgeSet& /* left */)     const { return VALUEBOOL_TRUE; }

// <=
PTR_Value Value::le(const ValueNull& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::le(const ValueBool& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::le(const ValueInt& /* left */)         const { return VALUEBOOL_FALSE; }
PTR_Value Value::le(const ValueFloat& /* left */)       const { return VALUEBOOL_FALSE; }
PTR_Value Value::le(const ValueString& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::le(const ValueStruct& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::le(const ValueReference& left)         const { return left.getVal()->le(*this);        }
PTR_Value Value::le(const ValueGraph& /* left */)       const { return VALUEBOOL_FALSE; }
PTR_Value Value::le(const ValueVertex& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::le(const ValueEdge& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::le(const ValueVertexSet& /* left */)   const { return VALUEBOOL_FALSE; }
PTR_Value Value::le(const ValueEdgeSet& /* left */)     const { return VALUEBOOL_FALSE; }

// >=
PTR_Value Value::ge(const ValueNull& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::ge(const ValueBool& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::ge(const ValueInt& /* left */)         const { return VALUEBOOL_FALSE; }
PTR_Value Value::ge(const ValueFloat& /* left */)       const { return VALUEBOOL_FALSE; }
PTR_Value Value::ge(const ValueString& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::ge(const ValueStruct& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::ge(const ValueReference& left)         const { return left.getVal()->ge(*this);        }
PTR_Value Value::ge(const ValueGraph& /* left */)       const { return VALUEBOOL_FALSE; }
PTR_Value Value::ge(const ValueVertex& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::ge(const ValueEdge& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::ge(const ValueVertexSet& /* left */)   const { return VALUEBOOL_FALSE; }
PTR_Value Value::ge(const ValueEdgeSet& /* left */)     const { return VALUEBOOL_FALSE; }

// <
PTR_Value Value::lt(const ValueNull& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::lt(const ValueBool& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::lt(const ValueInt& /* left */)         const { return VALUEBOOL_FALSE; }
PTR_Value Value::lt(const ValueFloat& /* left */)       const { return VALUEBOOL_FALSE; }
PTR_Value Value::lt(const ValueString& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::lt(const ValueStruct& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::lt(const ValueReference& left)         const { return left.getVal()->lt(*this);        }
PTR_Value Value::lt(const ValueGraph& /* left */)       const { return VALUEBOOL_FALSE; }
PTR_Value Value::lt(const ValueVertex& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::lt(const ValueEdge& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::lt(const ValueVertexSet& /* left */)   const { return VALUEBOOL_FALSE; }
PTR_Value Value::lt(const ValueEdgeSet& /* left */)     const { return VALUEBOOL_FALSE; }

// >
PTR_Value Value::gt(const ValueNull& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::gt(const ValueBool& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::gt(const ValueInt& /* left */)         const { return VALUEBOOL_FALSE; }
PTR_Value Value::gt(const ValueFloat& /* left */)       const { return VALUEBOOL_FALSE; }
PTR_Value Value::gt(const ValueString& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::gt(const ValueStruct& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::gt(const ValueReference& left)         const { return left.getVal()->gt(*this);        }
PTR_Value Value::gt(const ValueGraph& /* left */)       const { return VALUEBOOL_FALSE; }
PTR_Value Value::gt(const ValueVertex& /* left */)      const { return VALUEBOOL_FALSE; }
PTR_Value Value::gt(const ValueEdge& /* left */)        const { return VALUEBOOL_FALSE; }
PTR_Value Value::gt(const ValueVertexSet& /* left */)   const { return VALUEBOOL_FALSE; }
PTR_Value Value::gt(const ValueEdgeSet& /* left */)     const { return VALUEBOOL_FALSE; }

// . (member access)
PTR_Value Value::member(const ValueNull& /* left */)      const { return VALUENULL; }
PTR_Value Value::member(const ValueBool& /* left */)      const { return VALUENULL; }
PTR_Value Value::member(const ValueInt& /* left */)       const { return VALUENULL; }
PTR_Value Value::member(const ValueFloat& /* left */)     const { return VALUENULL; }
PTR_Value Value::member(const ValueString& /* left */)    const { return VALUENULL; }
PTR_Value Value::member(const ValueStruct& /* left */)    const { return VALUENULL; }
PTR_Value Value::member(const ValueReference& left)       const { return left.getVal()->member(*this); }
PTR_Value Value::member(const ValueGraph& /* left */)     const { return VALUENULL; }
PTR_Value Value::member(const ValueVertex& /* left */)    const { return VALUENULL; }
PTR_Value Value::member(const ValueEdge& /* left */)      const { return VALUENULL; }
PTR_Value Value::member(const ValueVertexSet& /* left */) const { return VALUENULL; }
PTR_Value Value::member(const ValueEdgeSet& /* left */)   const { return VALUENULL; }

// [] index
PTR_Value Value::index(const ValueNull& /* left */)      const { return VALUENULL; }
PTR_Value Value::index(const ValueBool& /* left */)      const { return VALUENULL; }
PTR_Value Value::index(const ValueInt& /* left */)       const { return VALUENULL; }
PTR_Value Value::index(const ValueFloat& /* left */)     const { return VALUENULL; }
PTR_Value Value::index(const ValueString& /* left */)    const { return VALUENULL; }
PTR_Value Value::index(const ValueStruct& /* left */)    const { return VALUENULL; }
PTR_Value Value::index(const ValueReference& left)       const { return left.getVal()->index(*this); }
PTR_Value Value::index(const ValueGraph& /* left */)     const { return VALUENULL; }
PTR_Value Value::index(const ValueVertex& /* left */)    const { return VALUENULL; }
PTR_Value Value::index(const ValueEdge& /* left */)      const { return VALUENULL; }
PTR_Value Value::index(const ValueVertexSet& /* left */) const { return VALUENULL; }
PTR_Value Value::index(const ValueEdgeSet& /* left */)   const { return VALUENULL; }

// - (unary)
PTR_Value Value::subUn(void)   const { return VALUENULL; }
