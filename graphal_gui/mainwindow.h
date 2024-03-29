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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextDocument>

class TextEditor;
class ScriptThread;
class DockScriptOutput;
class DockFiles;
class DockCallStack;
class DockVariables;
class DockVisualization;

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
	void openAndScroll(const QString& fileName, int line);
	void save();
	void saveAs();
	void saveAll();
	void undo();
	void redo();
	void cut();
	void copy();
	void paste();
	void selectAll(void);
	void findDialog(void);
	void replaceDialog(void);
	void findNext(void);
	void findPrevious(void);
	void about();
	void updateMenus();
	void updateWindowMenu();
	void updateVisualizationMenu(void);
	void runScript();
	void includeDirectories(void);
	void scriptParameters(void);
	void gotoLine(void);
	void saveCurrentView(void);
	void resetView(void);
	void screenshot(void);
	void settings(void);
	void loadGraph(void);

	void saveLayout();
	void loadLayout();

	void fileSelected(const QString& path);

	void statusBarMessage(const QString& str);
	void statusBarMessageWithTimeout(const QString& str);

	QMdiSubWindow* createTextEditor();
	void setActiveSubWindow(QWidget* window);

	void scriptStarted(void);
	void scriptFinished(void);
	void scriptPaused(void);
	void showLocation(void);
	void repaintVisualization(void);

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
	QMenu* m_visualizationMenu;
	QMenu* m_windowMenu;
	QMenu* m_helpMenu;
	QToolBar* m_fileToolBar;
	QToolBar* m_editToolBar;
	QToolBar* m_scriptToolBar;
	DockFiles* m_dockFiles;
	DockScriptOutput* m_dockScriptOutput;
	DockCallStack* m_dockCallStack;
	DockVariables* m_dockVariables;
	DockVisualization* m_dockVisualization;

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
	QAction* m_selectAllAct;
	QAction* m_findAct;
	QAction* m_findNextAct;
	QAction* m_findPreviousAct;
	QAction* m_replaceAct;
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
	QAction* m_stopScriptAct;
	QAction* m_debugRunAct;
	QAction* m_debugStepAct;
	QAction* m_debugOverAct;
	QAction* m_debugOutAct;
	QAction* m_debugLocationAct;
	QAction* m_enableBreakpointsAct;
	QAction* m_includeDirectoriesAct;
	QAction* m_scriptParametersAct;
	QAction* m_gotoLineAct;
	QAction* m_saveCurrentViewAct;
	QAction* m_resetViewAct;
	QAction* m_screnshotAct;
	QAction* m_settingsAct;
	QAction* m_loadGraphAct;

	ScriptThread* m_scriptThread;

	QString m_findText;
	QTextDocument::FindFlags m_findFlags;

	QString m_replaceFind;
	QString m_replaceReplacement;
	QTextDocument::FindFlags m_replaceFlags;
	bool m_replacePrompt;
};

#endif
