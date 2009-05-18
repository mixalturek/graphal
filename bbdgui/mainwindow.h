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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TextEditor;
class ScriptThread;
class DockScriptOutput;
class DockFiles;

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
class QSignalMapper;
class QModelIndex;
class QUrl;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	~MainWindow(void);

protected:
	void closeEvent(QCloseEvent* event);

private slots:
	void newFile();
	void open();
	bool open(const QString& fileName, bool warnIfNotFound);
	void open(const QString& fileName, int line);
	void save();
	void saveAs();
	void saveAll();
	void undo();
	void redo();
	void cut();
	void copy();
	void paste();
	void about();
	void updateMenus();
	void updateWindowMenu();
	void runScript();

	void saveLayout();
	void loadLayout();

	void fileSelected(const QString& path);

	void statusBarMessage(const QString& str);
	void statusBarMessageWithTimeout(const QString& str);

	QMdiSubWindow* createTextEditor();
	void setActiveSubWindow(QWidget* window);

	void scriptStarted(void);
	void scriptFinished(void);

private:
	void createActions();
	void createMenus();
	void createToolBars();
	void createDocks();
	void readSettings();
	void writeSettings();

	TextEditor* activeTextEditor();
	QMdiSubWindow* findTextEditor(const QString& fileName);

private:
	QMdiArea* m_mdiArea;
	QSignalMapper* m_windowMapper;
	QMenu* m_fileMenu;
	QMenu* m_editMenu;
	QMenu* m_viewMenu;
	QMenu* m_scriptMenu;
	QMenu* m_windowMenu;
	QMenu* m_helpMenu;
	QToolBar* m_fileToolBar;
	QToolBar* m_editToolBar;
	QToolBar* m_scriptToolBar;
	DockFiles* m_dockFiles;
	DockScriptOutput* m_dockScriptOutput;

	QAction* m_newAct;
	QAction* m_openAct;
	QAction* m_saveAct;
	QAction* m_saveAsAct;
	QAction* m_saveAllAct;
	QAction* m_saveLayoutAct;
	QAction* m_loadLayoutAct;
	QAction* m_exitAct;
	QAction* m_undoAct;
	QAction* m_redoAct;
	QAction* m_cutAct;
	QAction* m_copyAct;
	QAction* m_pasteAct;
	QAction* m_closeAct;
	QAction* m_closeAllAct;
	QAction* m_tileAct;
	QAction* m_cascadeAct;
	QAction* m_nextAct;
	QAction* m_previousAct;
	QAction* m_separatorAct;
	QAction* m_aboutAct;
	QAction* m_aboutQtAct;
	QAction* m_runScriptAct;
	QAction* m_debugRunAct;
	QAction* m_debugStepAct;
	QAction* m_debugOverAct;
	QAction* m_debugOutAct;

	ScriptThread* m_scriptThread;
};

#endif
