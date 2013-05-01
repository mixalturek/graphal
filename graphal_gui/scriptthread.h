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
	void setScriptParameters(const QStringList& parameters) { m_scriptParameters = parameters; }
	void enableBreakpoints(bool enable) { m_breakpointsEnabled = enable; }

private:
	QString m_scriptFilename;
	QStringList m_includeDirectories;
	QStringList m_scriptParameters;
	bool m_breakpointsEnabled;
};

#endif // SCRIPTTHREAD_H
