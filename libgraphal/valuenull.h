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


#ifndef VARIABLENULL_HPP
#define VARIABLENULL_HPP

#include "general.h"
#include "value.h"

#define VALUENULL ValueNull::getInstance()

// Singleton
class ValueNull : public Value
{
public:
	static inline CountPtr<Value>& getInstance(void)
	{
		return *m_instance;
	}

	static void initInstance(void);
	static void destroyInstance(void);

private:
	ValueNull();
	virtual ~ValueNull();
	ValueNull(const ValueNull& object);
	ValueNull& operator=(const ValueNull& object);

public:
	virtual bool     toBool(void) const { return false; }
	virtual bool     isNull(void) const { return true; }
	virtual string toString(void) const { return "NULL"; }

	virtual void dump(ostream& os, uint indent) const;

	virtual CountPtr<Value> add(const Value&    right) const; // +
	virtual CountPtr<Value> sub(const Value&    right) const; // -
	virtual CountPtr<Value> mult(const Value&   right) const; // *
	virtual CountPtr<Value> div(const Value&    right) const; // /
	virtual CountPtr<Value> mod(const Value&    right) const; // %
	virtual CountPtr<Value> eq(const Value&     right) const; // ==
	virtual CountPtr<Value> eq(const ValueNull& left)  const;
	virtual CountPtr<Value> ne(const Value&     right) const; // !=
	virtual CountPtr<Value> ne(const ValueNull& left)  const;
	virtual CountPtr<Value> le(const Value&     right) const; // <=
	virtual CountPtr<Value> ge(const Value&     right) const; // >=
	virtual CountPtr<Value> lt(const Value&     right) const; // <
	virtual CountPtr<Value> gt(const Value&     right) const; // >
	virtual CountPtr<Value> member(const Value& right) const; // .
	virtual CountPtr<Value> index(const Value&  right) const; // []
	virtual CountPtr<Value> logNOT(void)               const; // !

private:
	static CountPtr<Value>* m_instance;
};

ostream& operator<<(ostream& os, const ValueNull& node);

#endif /* VARIABLENULL_HPP */
