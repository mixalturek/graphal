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


#include "nodevalue.h"
#include "value.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeValue::NodeValue(Value* value)
	: Node(),
	m_value(value)
{
	assert(value != NULL);
}

NodeValue::NodeValue(CountPtr<Value> value)
	: Node(),
	m_value(value)
{

}

NodeValue::~NodeValue()
{

}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeValue::execute(void)
{
	return m_value;
}

void NodeValue::dump(ostream& os, uint indent) const
{
//	dumpIndent(os, indent);
//	os << "<NodeValue>" << endl;
	m_value->dump(os, indent);
//	dumpIndent(os, indent);
//	os << "</NodeValue>" << endl;
}

ostream& operator<<(ostream& os, const NodeValue& node)
{
	node.dump(os, 0);
	return os;
}
