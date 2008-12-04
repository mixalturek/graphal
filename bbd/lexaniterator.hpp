/*
 *      lexaniterator.hpp
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

#ifndef LEXANITERATOR_HPP
#define LEXANITERATOR_HPP

#include "general.hpp"
#include "baseobject.hpp"

class LexanIterator : BaseObject
{
public:
	LexanIterator(void);
	virtual ~LexanIterator(void);

	virtual char get(void) = 0;
	virtual void unget(void) = 0;

	virtual const string getSource(void) const = 0;
	virtual int getPos(void) const = 0;
};

#endif