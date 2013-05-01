/*
 * Copyright 2009 Michal Turek
 *
 * This file is part of Graphal GUI.
 * http://graphal.sourceforge.net/
 *
 * Graphal GUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal GUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Graphal GUI.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef GUIFACTORY_HPP
#define GUIFACTORY_HPP

#include "general.h"
#include "objectfactory.h"


class GuiFactory : public ObjectFactory
{
public:
	GuiFactory(void);
	virtual ~GuiFactory(void);

	void dump(ostream& os, uint indent) const;

	virtual Logger* newLogger(void) const;
	virtual Mutex* newMutex(void) const;
	virtual Context* newContext(void) const;
	virtual VisualizationConnector* newVisualizationConnector(void) const;

private:
};

#endif // GUIFACTORY_HPP
