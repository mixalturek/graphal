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

#ifndef COUNTPTR_HPP
#define COUNTPTR_HPP

#include "general.hpp"


template<class TYPE> class CountPtr
{
/////////////////////////////////////////////////////////////////////////////
////

public:
	explicit CountPtr(TYPE* simpleptr)
		: m_ptr(simpleptr),
		m_num(new uint(1))
	{

	}

	CountPtr(const CountPtr<TYPE>& cntptr)
		: m_ptr(cntptr.m_ptr),
		m_num(cntptr.m_num)
	{
		++*m_num;
	}

	~CountPtr()
	{
		free();
	}

	CountPtr<TYPE>& operator= (const CountPtr<TYPE>& cntptr)
	{
		if(this != &cntptr)
		{
			free();
			m_ptr = cntptr.m_ptr;
			m_num = cntptr.m_num;
			++*m_num;
		}

		return *this;
	}


/////////////////////////////////////////////////////////////////////////////
////

	TYPE& operator*() const
	{
		return *m_ptr;
	}

	TYPE* operator->() const
	{
		return m_ptr;
	}


/////////////////////////////////////////////////////////////////////////////
////

	uint getNumRefs(void) const
	{
		return *m_num;
	}


/////////////////////////////////////////////////////////////////////////////
////

private:
	CountPtr(void);

	void free()
	{
		if(--*m_num == 0)
		{
			delete m_num;
			m_num = NULL;
			delete m_ptr;
			m_ptr = NULL;
		}
	}

private:
	TYPE* m_ptr;
	uint* m_num;
};

#endif // COUNTPTR_HPP
