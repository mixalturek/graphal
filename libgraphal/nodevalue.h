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


#ifndef NODEVALUE_HPP
#define NODEVALUE_HPP

#include "general.h"
#include "node.h"


class NodeValue : public Node
{
public:
	NodeValue(Value* value);
	NodeValue(CountPtr<Value> value);
	virtual ~NodeValue();

	virtual CountPtr<Value> execute(void);
	virtual void dump(ostream& os, uint indent) const;

private:
	CountPtr<Value> m_value;
};

ostream& operator<<(ostream& os, const NodeValue& node);

#endif // NODEVALUE_HPP
