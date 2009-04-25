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
QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
class QSignalMapper;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

protected:
	void closeEvent(QCloseEvent* event);

private slots:
	void newFile();
	void open();
	void save();
	void saveAs();
	void saveAll();
	void cut();
	void copy();
	void paste();
	void about();
	void updateMenus();
	void updateWindowMenu();

	void saveLayout();
	void loadLayout();

	TextEditor* createTextEditor();
	void setActiveSubWindow(QWidget* window);

private:
	void createActions();
	void createMenus();
	void createToolBars();
	void createStatusBar();
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
	QMenu* m_windowMenu;
	QMenu* m_helpMenu;
	QToolBar* m_fileToolBar;
	QToolBar* m_editToolBar;
	QDockWidget* m_filesDock;

	QAction* m_newAct;
	QAction* m_openAct;
	QAction* m_saveAct;
	QAction* m_saveAsAct;
	QAction* m_saveAllAct;
	QAction* m_saveLayoutAct;
	QAction* m_loadLayoutAct;
	QAction* m_exitAct;
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
};

#endif
