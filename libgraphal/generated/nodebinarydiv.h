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

/****************************************************************************
 *                                                                          *
 *           This file was generated by gen_operators.pl script.            *
 *                        Don't update it manually!                         *
 *                                                                          *
 ****************************************************************************/

#ifndef NODEBINARYDIV_H
#define NODEBINARYDIV_H

#include "general.h"
#include "nodebinary.h"

class NodeBinaryDiv : public NodeBinary
{
public:
	NodeBinaryDiv(Node* left, Node* right);
	virtual ~NodeBinaryDiv(void);

	virtual CountPtr<Value> execute(void);
	virtual void dump(ostream& os, uint indent) const;

private:
	NodeBinaryDiv(void);
	NodeBinaryDiv(const NodeBinaryDiv& object);
	NodeBinaryDiv& operator=(const NodeBinaryDiv& object);
};

ostream& operator<<(ostream& os, const NodeBinaryDiv& node);

#endif /* NODEBINARYDIV_H */

