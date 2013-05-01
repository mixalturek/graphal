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

#ifndef COUNTPTR_HPP
#define COUNTPTR_HPP

#include <cassert>
#include "general.h"
#include "objectcreator.h"


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

	bool operator== (const CountPtr<TYPE>& cntptr) const
	{
		ACCESS_MUTEX_LOCKER;
		return m_ptr->eq(*(cntptr.m_ptr))->toBool();
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
