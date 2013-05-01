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


#ifndef DOCKSCRIPTOUTPUT_H
#define DOCKSCRIPTOUTPUT_H

#include <QDockWidget>
#include <QTextBrowser>


class DockScriptOutput : public QDockWidget
{
	Q_OBJECT

public:
	DockScriptOutput(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	~DockScriptOutput(void);

	QTextBrowser* getTextBrowser(void) const { return m_textEdit; }

signals:
	void anchorClicked(const QString& filename, int line);

public slots:
	void reinit(void);

	void error(const QString& str);
	void error(const QString& pos, const QString& str);
	void warn(const QString& str);
	void warn(const QString& pos, const QString& str);
	void info(const QString& str);
	void info(const QString& pos, const QString& str);
	void scriptStdout(const QString& str);

private slots:
	void anchorClicked(const QUrl& link);
	void append(const QString& str, const QColor& color);
	void append(const QString& pos, const QString& str, const QColor& color);

private:
	QTextBrowser* m_textEdit;
};

#endif // DOCKSCRIPTOUTPUT_H
