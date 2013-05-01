/*
 * Copyright 2009 Michal Turek
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


#include "nodejumpcontinue.h"
#include "valuenull.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeJumpContinue::NodeJumpContinue()
	: Node()
{

}

NodeJumpContinue::~NodeJumpContinue()
{

}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeJumpContinue::execute(void)
{
	throw this;

	// It will never be called
	return VALUENULL;
}

void NodeJumpContinue::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<NodeJumpContinue />" << endl;
}

ostream& operator<<(ostream& os, const NodeJumpContinue& node)
{
	node.dump(os, 0);
	return os;
}
