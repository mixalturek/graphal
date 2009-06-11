/*
 *      Copyright 2009 Michal Turek <http://woq.nipax.cz/>
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


#ifndef SCRIPTTHREAD_H
#define SCRIPTTHREAD_H

#include <QThread>

class ScriptThread : public QThread
{
public:
	ScriptThread(QObject* parent = 0);
	~ScriptThread(void);

	void run(void);
	void setScriptFilename(const QString& filename) { m_scriptFilename = filename; }
	void setIncludeDirectories(const QStringList& directories) { m_includeDirectories = directories; }

private:
	QString m_scriptFilename;
	QStringList m_includeDirectories;
};

#endif // SCRIPTTHREAD_H
