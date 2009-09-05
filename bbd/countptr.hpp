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

#include <cassert>
#include "general.hpp"
#include "objectcreator.hpp"


template<class TYPE> class CountPtr
{
/////////////////////////////////////////////////////////////////////////////
////

public:
	// Don't use this constructor, Qt qRegisterMetaType() in visualization.cpp requires it
	CountPtr(void)
		: m_ptr(NULL),
		m_num(new uint(1)),
		m_delete_automatically(new bool(false))
	{
		assert(false);
	}

	explicit CountPtr(TYPE* simpleptr)
		: m_ptr(simpleptr),
		m_num(new uint(1)),
		m_delete_automatically(new bool(true))
	{
		assert(simpleptr != NULL);
	}

	CountPtr(const CountPtr<TYPE>& cntptr)
	{
		ACCESS_MUTEX_LOCKER;
		m_ptr = cntptr.m_ptr;
		m_num = cntptr.m_num;
		m_delete_automatically = cntptr.m_delete_automatically;
		++*m_num;
	}

	~CountPtr()
	{
		free();
	}

	CountPtr<TYPE>& operator= (const CountPtr<TYPE>& cntptr)
	{
		ACCESS_MUTEX_LOCKER;

		if(this != &cntptr)
		{
			free();
			m_ptr = cntptr.m_ptr;
			m_num = cntptr.m_num;
			m_delete_automatically = cntptr.m_delete_automatically;
			++*m_num;
		}

		return *this;
	}


/////////////////////////////////////////////////////////////////////////////
////

	TYPE& operator*() const
	{
		ACCESS_MUTEX_LOCKER;
		return *m_ptr;
	}

	TYPE* operator->() const
	{
		ACCESS_MUTEX_LOCKER;
		return m_ptr;
	}

	const TYPE* getPtr(void) const
	{
		ACCESS_MUTEX_LOCKER;
		return m_ptr;
	}


/////////////////////////////////////////////////////////////////////////////
////

	uint getNumRefs(void) const
	{
		ACCESS_MUTEX_LOCKER;
		return *m_num;
	}

	// Vertices and Edges in ValueGraph
	void dontDeleteAutomatically(void)
	{
		ACCESS_MUTEX_LOCKER;
		*m_delete_automatically = false;
	}


/////////////////////////////////////////////////////////////////////////////
////

private:
	void free()
	{
		ACCESS_MUTEX_LOCKER;
		if(--*m_num == 0)
		{
			delete m_num;
			m_num = NULL;

			if(*m_delete_automatically == true && m_ptr != NULL)
				delete m_ptr;

			m_ptr = NULL;

			delete m_delete_automatically;
			m_delete_automatically = NULL;
		}
	}

private:
	TYPE* m_ptr;
	uint* m_num;
	bool* m_delete_automatically;
};

#endif // COUNTPTR_HPP
