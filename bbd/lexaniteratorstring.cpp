/*
 *      lexaniteratorstring.cpp
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

#include "lexaniteratorstring.hpp"

/////////////////////////////////////////////////////////////////////////////
////

LexanIteratorString::LexanIteratorString(const string& name, const string& value)
	: LexanIterator(),
	m_name(name),
	m_value(value),
	m_pos(-1)
{

}

LexanIteratorString::~LexanIteratorString(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

char LexanIteratorString::get(void)
{
	// It has to be incremented every call, unget() could be called
	if(++m_pos < (int)m_value.length())
		return m_value[m_pos];
	else
		return EOF;
}

void LexanIteratorString::unget(void)
{
	if(m_pos > 0)
		m_pos--;
}
