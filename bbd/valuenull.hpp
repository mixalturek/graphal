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


#ifndef VARIABLENULL_HPP
#define VARIABLENULL_HPP

#include "general.hpp"
#include "value.hpp"

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

	virtual PTR_Value add(const Value&    right) const; // +
	virtual PTR_Value sub(const Value&    right) const; // -
	virtual PTR_Value mult(const Value&   right) const; // *
	virtual PTR_Value div(const Value&    right) const; // /
	virtual PTR_Value mod(const Value&    right) const; // %
	virtual PTR_Value eq(const Value&     right) const; // ==
	virtual PTR_Value eq(const ValueNull& left)  const;
	virtual PTR_Value ne(const Value&     right) const; // !=
	virtual PTR_Value ne(const ValueNull& left)  const;
	virtual PTR_Value le(const Value&     right) const; // <=
	virtual PTR_Value ge(const Value&     right) const; // >=
	virtual PTR_Value lt(const Value&     right) const; // <
	virtual PTR_Value gt(const Value&     right) const; // >
	virtual PTR_Value member(const Value& right) const; // .
	virtual PTR_Value index(const Value&  right) const; // []
	virtual PTR_Value logNOT(void)               const; // !

private:
	static CountPtr<Value>* m_instance;
};

ostream& operator<<(ostream& os, const ValueNull& node);

#endif /* VARIABLENULL_HPP */
