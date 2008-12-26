/*
 *      retval.hpp
 *
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

#ifndef RETVAL_HPP
#define RETVAL_HPP

#include "general.hpp"

class Value;

class RetVal
{
public:
	RetVal(Value* val, bool autodel = true);
	~RetVal(void);

	Value& operator*() const { return *m_val; }
	Value* operator->() const { return m_val; }

	Value* release(void) { m_autodel = false; return m_val; }

private:
	RetVal(void);

private:
	Value* m_val;
	bool   m_autodel;
};

#endif // RETVAL_HPP
