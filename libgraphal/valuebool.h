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


#ifndef VARIABLEBOOL_HPP
#define VARIABLEBOOL_HPP

#include "general.h"
#include "value.h"

#define VALUEBOOL_TRUE  ValueBool::getInstanceTrue()
#define VALUEBOOL_FALSE ValueBool::getInstanceFalse()

// Singleton
class ValueBool : public Value
{
public:
	static inline CountPtr<Value>& getInstanceTrue(void)
	{
		return *m_instance_true;
	}

	static inline CountPtr<Value>& getInstanceFalse(void)
	{
		return *m_instance_false;
	}

	static void initInstance(void);
	static void destroyInstance(void);

private:
	ValueBool();
	ValueBool(bool val);
	virtual ~ValueBool();
	ValueBool(const ValueBool& object);
	ValueBool& operator=(const ValueBool& object);

public:
	bool             getVal(void) const { return m_val; }
	virtual bool     toBool(void) const { return m_val; }
	virtual string toString(void) const { return (m_val) ? "true" : "false"; }
	virtual bool  isNumeric(void) const { return true; }
	virtual int       toInt(void) const { return m_val; }
	virtual float   toFloat(void) const { return m_val; }

	virtual ValueBool*           toValueBool(void) { return this; }

	virtual void dump(ostream& os, uint indent) const;

	// +
	virtual CountPtr<Value> add(const Value&      right) const;
	virtual CountPtr<Value> add(const ValueBool&   left) const;
	virtual CountPtr<Value> add(const ValueInt&    left) const;
	virtual CountPtr<Value> add(const ValueFloat&  left) const;

	// -
	virtual CountPtr<Value> sub(const Value&      right) const;
	virtual CountPtr<Value> sub(const ValueBool&   left) const;
	virtual CountPtr<Value> sub(const ValueInt&    left) const;
	virtual CountPtr<Value> sub(const ValueFloat&  left) const;

	// *
	virtual CountPtr<Value> mult(const Value&      right) const;
	virtual CountPtr<Value> mult(const ValueBool&   left) const;
	virtual CountPtr<Value> mult(const ValueInt&    left) const;
	virtual CountPtr<Value> mult(const ValueFloat&  left) const;

	// /
	virtual CountPtr<Value> div(const Value&      right) const;
	virtual CountPtr<Value> div(const ValueBool&   left) const;
	virtual CountPtr<Value> div(const ValueInt&    left) const;
	virtual CountPtr<Value> div(const ValueFloat&  left) const;

	// %
	virtual CountPtr<Value> mod(const Value&      right) const;
	virtual CountPtr<Value> mod(const ValueBool&   left) const;
	virtual CountPtr<Value> mod(const ValueInt&    left) const;
	virtual CountPtr<Value> mod(const ValueFloat&  left) const;

	// ==
	virtual CountPtr<Value> eq(const Value&      right) const;
	virtual CountPtr<Value> eq(const ValueBool&   left) const;
	virtual CountPtr<Value> eq(const ValueInt&    left) const;
	virtual CountPtr<Value> eq(const ValueFloat&  left) const;

	// !=
	virtual CountPtr<Value> ne(const Value&      right) const;
	virtual CountPtr<Value> ne(const ValueBool&   left) const;
	virtual CountPtr<Value> ne(const ValueInt&    left) const;
	virtual CountPtr<Value> ne(const ValueFloat&  left) const;

	// <=
	virtual CountPtr<Value> le(const Value&      right) const;
	virtual CountPtr<Value> le(const ValueBool&   left) const;
	virtual CountPtr<Value> le(const ValueInt&    left) const;
	virtual CountPtr<Value> le(const ValueFloat&  left) const;

	// >=
	virtual CountPtr<Value> ge(const Value&      right) const;
	virtual CountPtr<Value> ge(const ValueBool&   left) const;
	virtual CountPtr<Value> ge(const ValueInt&    left) const;
	virtual CountPtr<Value> ge(const ValueFloat&  left) const;

	// <
	virtual CountPtr<Value> lt(const Value&      right) const;
	virtual CountPtr<Value> lt(const ValueBool&   left) const;
	virtual CountPtr<Value> lt(const ValueInt&    left) const;
	virtual CountPtr<Value> lt(const ValueFloat&  left) const;

	// >
	virtual CountPtr<Value> gt(const Value&      right) const;
	virtual CountPtr<Value> gt(const ValueBool&   left) const;
	virtual CountPtr<Value> gt(const ValueInt&    left) const;
	virtual CountPtr<Value> gt(const ValueFloat&  left) const;

	// !
	virtual CountPtr<Value> logNOT(void) const;

	// - (unary)
	virtual CountPtr<Value> subUn(void) const;

	// .
	virtual CountPtr<Value> member(const Value& right) const;

	// []
	virtual CountPtr<Value> index(const Value&  right) const;
	virtual CountPtr<Value> index(const ValueString& left) const;
	virtual CountPtr<Value> index(const ValueArray& left) const;

private:
	static CountPtr<Value>* m_instance_true;
	static CountPtr<Value>* m_instance_false;
	const bool m_val;
};

ostream& operator<<(ostream& os, const ValueBool& node);

#endif /* VARIABLEBOOL_HPP */
