/*
 *      Copyright 2009 Michal Turek <http://woq.nipax.cz/>
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

#ifndef EXITVALUE_HPP
#define EXITVALUE_HPP

#include "general.hpp"
#include "baseobject.hpp"
#include "countptr.hpp"
#include "value.hpp"


class ExitValue : public BaseObject
{
public:
	ExitValue(CountPtr<Value>& value);
	virtual ~ExitValue();

	virtual void dump(ostream& os, uint indent) const;
	CountPtr<Value>& getValue(void) { return m_value; }

private:
	CountPtr<Value> m_value;
};

#endif // EXITVALUE_HPP
