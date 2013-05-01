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


#ifndef GUIMUTEX_H
#define GUIMUTEX_H

#include <QMutex>
#include "general.h"
#include "mutex.h"

class GuiMutex : public Mutex
{
public:
	GuiMutex(void);
	virtual ~GuiMutex(void);

	virtual void lock(void);
	virtual void unlock(void);

private:
	QMutex m_mutex;
};

#endif // GUIMUTEX_H
