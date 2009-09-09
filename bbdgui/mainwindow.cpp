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

#include <cassert>
#include <QtGui>
#include "mainwindow.h"
#include "texteditor.h"
#include "scriptthread.h"
#include "settings.h"
#include "dockscriptoutput.h"
#include "dockfiles.h"
#include "dockcallstack.h"
#include "dockvariables.h"
#include "dockvisualization.h"
#include "objectcreator.hpp"
#include "guilogger.hpp"
#include "version.hpp"
#include "guicontext.h"
#include "dialogincludedirs.h"
#include "dialogscriptparameters.h"
#include "dialogfind.h"
#include "dialogreplace.h"
#include "objectcreator.hpp"


/////////////////////////////////////////////////////////////////////////////
////

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),
	m_scriptThread(new ScriptThread),
	m_findText(""),
	m_findFlags(0),
	m_replaceFind(""),
	m_replaceReplacement(""),
	m_replaceFlags(0),
	m_replacePrompt(false)
{
	m_mdiArea = new QMdiArea;
	setCentralWidget(m_mdiArea);

	connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)),
			this, SLOT(updateMenus()));

	m_windowMapper = new QSignalMapper(this);
	connect(m_windowMapper, SIGNAL(mapped(QWidget *)),
			this, SLOT(setActiveSubWindow(QWidget *)));

	// TODO: add to the settings
	setIconSize(QSize(22, 22));
	setAnimated(false);
	setDockNestingEnabled(true);
//	setDocumentMode(true); // TODO: Qt 4.5

	createActions();
	createDocks();
	createToolBars();
	createMenus();
	updateMenus();
	readSettings();
	scriptFinished();// Update UI

	m_mdiArea->setViewMode(QMdiArea::TabbedView);
	setWindowTitle(tr("bbdgui"));

	connect(m_scriptThread, SIGNAL(started()), this, SLOT(scriptStarted()));
	connect(m_scriptThread, SIGNAL(finished()), this, SLOT(scriptFinished()));

	GuiContext* context = dynamic_cast<GuiContext*>(&CONTEXT);
	assert(context != NULL);
	connect(context, SIGNAL(executionPaused()), this, SLOT(scriptPaused()));

	statusBarMessage(tr("Ready"));
}


MainWindow::~MainWindow()
{
	m_scriptThread->wait();// TODO: timeout and then terminate()?
	delete m_scriptThread;
	m_scriptThread = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::closeEvent(QCloseEvent* event)
{
	// TODO: MessageBox("terminate?")
	if(m_scriptThread->isRunning())
	{
		CONTEXT.stopScript();
		m_scriptThread->wait();
	}

	writeSettings();
	m_mdiArea->closeAllSubWindows();

	if(m_mdiArea->subWindowList().size() != 0)
		event->ignore();
	else
		event->accept();
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::newFile()
{
	QMdiSubWindow* window = createTextEditor();
	TextEditor* editor = qobject_cast<TextEditor*>(window->widget());
	assert(editor != NULL);

	editor->newFile();
	window->show();
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::open()
{
	// TODO: save path to the settings
	QStringList fileName = QFileDialog::getOpenFileNames(this);
	foreach(QString str, fileName)
		open(str, true);
}

bool MainWindow::open(const QString& fileName, bool warnIfNotFound)
{
	QFileInfo info(fileName);
	if(info.isFile())
	{
		QMdiSubWindow* window = findTextEditor(fileName);

		if(window)
		{
			m_mdiArea->setActiveSubWindow(window);
			return true;
		}

		window = createTextEditor();
		TextEditor* editor = qobject_cast<TextEditor*>(window->widget());
		assert(editor != NULL);

		if(editor->loadFile(fileName, warnIfNotFound))
		{
			statusBarMessageWithTimeout(tr("File loaded"));
			window->show();
			return true;
		}
		else
			window->close();
	}

	return false;
}

void MainWindow::openAndScroll(const QString& fileName, int line)
{
	if(open(fileName, true))
	{
		TextEditor* editor = activeTextEditor();
		assert(editor != NULL);// Open() was ok

		if(line <= editor->blockCount())
		{
			// Three hours of my life to write the following line :-(
			editor->setTextCursor(QTextCursor(editor->document()->findBlockByNumber(line-1)));
			// editor->centerCursor();// TOOD: only if it is not visible
		}

		editor->setFocus();
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::save()
{
	if(activeTextEditor() && activeTextEditor()->save())
		statusBarMessageWithTimeout(tr("File saved"));
}

void MainWindow::saveAs()
{
	if(activeTextEditor() && activeTextEditor()->saveAs())
		statusBarMessageWithTimeout(tr("File saved"));
}

void MainWindow::saveAll()
{
	foreach(QMdiSubWindow* window, m_mdiArea->subWindowList())
	{
		TextEditor* editor = qobject_cast<TextEditor*>(window->widget());
		assert(editor != NULL);
		editor->save();
	}

	statusBarMessageWithTimeout(tr("Files saved"));
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::undo()
{
	if(activeTextEditor())
		activeTextEditor()->undo();
}

void MainWindow::redo()
{
	if(activeTextEditor())
		activeTextEditor()->redo();
}

void MainWindow::cut()
{
	if(activeTextEditor())
		activeTextEditor()->cut();
}

void MainWindow::copy()
{
	if(activeTextEditor())
		activeTextEditor()->copy();
}

void MainWindow::paste()
{
	if(activeTextEditor())
		activeTextEditor()->paste();
}

void MainWindow::selectAll(void)
{
	if(activeTextEditor())
		activeTextEditor()->selectAll();
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::about()
{
	// TODO: update text, version
	QMessageBox::about(this, tr("About bbdgui"),
		tr("Graph algorithms interpreter<br />SVN version ")
		+ QString::number(SVN_VERSION));
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::updateMenus()
{
	TextEditor* editor = activeTextEditor();

	m_saveAct->setEnabled(editor != NULL);
	m_saveAsAct->setEnabled(editor != NULL);
	m_saveAllAct->setEnabled(editor != NULL);
	m_pasteAct->setEnabled(editor != NULL);
	m_findAct->setEnabled(editor != NULL);
	m_replaceAct->setEnabled(editor != NULL);
	m_findNextAct->setEnabled(editor != NULL);
	m_findPreviousAct->setEnabled(editor != NULL);
	m_selectAllAct->setEnabled(editor != NULL);
	m_gotoLineAct->setEnabled(editor != NULL);
	m_closeAct->setEnabled(editor != NULL);
	m_closeAllAct->setEnabled(editor != NULL);
	m_tileAct->setEnabled(editor != NULL);
	m_cascadeAct->setEnabled(editor != NULL);
	m_nextAct->setEnabled(editor != NULL);
	m_previousAct->setEnabled(editor != NULL);
	m_separatorAct->setVisible(editor != NULL);

	m_undoAct->setEnabled(editor != NULL && editor->document()->isUndoAvailable());
	m_redoAct->setEnabled(editor != NULL && editor->document()->isRedoAvailable());

	bool hasSelection = editor != NULL && editor->textCursor().hasSelection();
	m_cutAct->setEnabled(hasSelection);
	m_copyAct->setEnabled(hasSelection);
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::updateWindowMenu()
{
	m_windowMenu->clear();

	m_windowMenu->addAction(m_tileAct);
	m_windowMenu->addAction(m_cascadeAct);
	m_windowMenu->addSeparator();
	m_windowMenu->addAction(m_nextAct);
	m_windowMenu->addAction(m_previousAct);
	m_windowMenu->addAction(m_separatorAct);

	QList<QMdiSubWindow*> windows = m_mdiArea->subWindowList();
	m_separatorAct->setVisible(!windows.isEmpty());

	for(int i = 0; i < windows.size(); ++i)
	{
		QString text;
		TextEditor* editor = qobject_cast<TextEditor*>(windows.at(i)->widget());
		assert(editor != NULL);

		if(i < 9)
			text = QString("&%1 %2").arg(i + 1).arg(editor->userFriendlyCurrentFile());
		else
			text = QString("%2").arg(editor->userFriendlyCurrentFile());

		QAction* action = m_windowMenu->addAction(text);
		action->setCheckable(true);
		action->setChecked(editor == activeTextEditor());

		connect(action, SIGNAL(triggered()), m_windowMapper, SLOT(map()));
		m_windowMapper->setMapping(action, windows.at(i));
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::updateVisualizationMenu(void)
{
	Visualization* vis = m_dockVisualization->getVisualization();

	if(!vis->hasVertices() && !vis->hasEdges())
	{
		m_visualizationMenu->setEnabled(false);
		return;
	}
	else
		m_visualizationMenu->setEnabled(true);


	m_visualizationMenu->clear();

//	if(vis->hasVertices())
//		m_visualizationMenu->addSeparator();

	VIS_DATA_CONTAINER::const_iterator it;
	QAction* action = NULL;

	const VIS_DATA_CONTAINER& dataVertices = vis->getVertexSets();
	for(it = dataVertices.begin(); it != dataVertices.end(); ++it)
	{
		action = m_visualizationMenu->addAction(QString::fromStdString(ID2STR(it->getName())));
		action->setStatusTip(tr("Toogle painting of this vertex set"));
		action->setCheckable(true);
		action->setChecked(it->isEnabled());
		connect(action, SIGNAL(toggled(bool)), it->getMe(), SLOT(setEnabled(bool)));
		connect(action, SIGNAL(toggled(bool)), this, SLOT(repaintVisualization()));
	}

//	if(vis->hasEdges())
	if(vis->hasVertices() && vis->hasEdges())
		m_visualizationMenu->addSeparator();

	const VIS_DATA_CONTAINER& dataEdges = vis->getEdgeSets();
	for(it = dataEdges.begin(); it != dataEdges.end(); ++it)
	{
		action = m_visualizationMenu->addAction(QString::fromStdString(ID2STR(it->getName())));
		action->setStatusTip(tr("Toogle painting of this edge set"));
		action->setCheckable(true);
		action->setChecked(it->isEnabled());
		connect(action, SIGNAL(toggled(bool)), it->getMe(), SLOT(setEnabled(bool)));
		connect(action, SIGNAL(toggled(bool)), this, SLOT(repaintVisualization()));
	}
}


/////////////////////////////////////////////////////////////////////////////
////

QMdiSubWindow* MainWindow::createTextEditor()
{
	QMdiSubWindow* window = new QMdiSubWindow(m_mdiArea);
	TextEditor* editor = new TextEditor(window);

	window->setAttribute(Qt::WA_DeleteOnClose);
	window->setWidget(editor);

	connect(editor, SIGNAL(copyAvailable(bool)), m_cutAct, SLOT(setEnabled(bool)));
	connect(editor, SIGNAL(copyAvailable(bool)), m_copyAct, SLOT(setEnabled(bool)));

	connect(editor, SIGNAL(undoAvailable(bool)), m_undoAct, SLOT(setEnabled(bool)));
	connect(editor, SIGNAL(redoAvailable(bool)), m_redoAct, SLOT(setEnabled(bool)));

	return m_mdiArea->addSubWindow(window);
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::createActions()
{
	GuiContext* context = dynamic_cast<GuiContext*>(&CONTEXT);
	assert(context != NULL);

	m_newAct = new QAction(QIcon(":/images/filenew.png"), tr("&New"), this);
	m_newAct->setShortcut(tr("Ctrl+N"));
	m_newAct->setStatusTip(tr("Create a new file"));
	connect(m_newAct, SIGNAL(triggered()), this, SLOT(newFile()));

	m_openAct = new QAction(QIcon(":/images/fileopen.png"), tr("&Open..."), this);
	m_openAct->setShortcut(tr("Ctrl+O"));
	m_openAct->setStatusTip(tr("Open an existing file"));
	connect(m_openAct, SIGNAL(triggered()), this, SLOT(open()));

	m_saveAct = new QAction(QIcon(":/images/filesave.png"), tr("&Save"), this);
	m_saveAct->setShortcut(tr("Ctrl+S"));
	m_saveAct->setStatusTip(tr("Save the document to disk"));
	connect(m_saveAct, SIGNAL(triggered()), this, SLOT(save()));

	m_saveAsAct = new QAction(QIcon(":/images/filesaveas.png"), tr("Save &As..."), this);
	m_saveAsAct->setStatusTip(tr("Save the document under a new name"));
	connect(m_saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

	m_saveAllAct = new QAction(QIcon(":/images/filesaveall.png"), tr("Save A&ll..."), this);
	m_saveAllAct->setShortcut(tr("Ctrl+Shift+S"));
	m_saveAllAct->setStatusTip(tr("Save all documents"));
	connect(m_saveAllAct, SIGNAL(triggered()), this, SLOT(saveAll()));

	m_closeAct = new QAction(QIcon(":/images/fileclose.png"), tr("Cl&ose"), this);
	m_closeAct->setShortcut(tr("Ctrl+F4"));
	m_closeAct->setStatusTip(tr("Close the active window"));
	connect(m_closeAct, SIGNAL(triggered()), m_mdiArea, SLOT(closeActiveSubWindow()));

	m_closeAllAct = new QAction(tr("Close &All"), this);
	m_closeAllAct->setShortcut(tr("Ctrl+Shift+F4"));
	m_closeAllAct->setStatusTip(tr("Close all the windows"));
	connect(m_closeAllAct, SIGNAL(triggered()), m_mdiArea, SLOT(closeAllSubWindows()));

	m_saveLayoutAct = new QAction(tr("Save application layout"), this);
	m_saveLayoutAct->setStatusTip(tr("Save the application layout to disk"));
	connect(m_saveLayoutAct, SIGNAL(triggered()), this, SLOT(saveLayout()));

	m_loadLayoutAct = new QAction(tr("Load application layout"), this);
	m_loadLayoutAct->setStatusTip(tr("Load the application layout"));
	connect(m_loadLayoutAct, SIGNAL(triggered()), this, SLOT(loadLayout()));

	m_exitAct = new QAction(QIcon(":/images/exit.png"), tr("E&xit"), this);
	m_exitAct->setShortcut(tr("Ctrl+Q"));
	m_exitAct->setStatusTip(tr("Exit the application"));
	connect(m_exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

	m_undoAct = new QAction(QIcon(":/images/undo.png"), tr("&Undo"), this);
	m_undoAct->setShortcut(tr("Ctrl+Z"));
	m_undoAct->setStatusTip(tr("Undo the last processed action"));
	connect(m_undoAct, SIGNAL(triggered()), this, SLOT(undo()));

	m_redoAct = new QAction(QIcon(":/images/redo.png"), tr("&Redo"), this);
	m_redoAct->setShortcut(tr("Ctrl+Y"));
	m_redoAct->setStatusTip(tr("Redo the action"));
	connect(m_redoAct, SIGNAL(triggered()), this, SLOT(redo()));

	m_cutAct = new QAction(QIcon(":/images/editcut.png"), tr("Cu&t"), this);
	m_cutAct->setShortcut(tr("Ctrl+X"));
	m_cutAct->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
	connect(m_cutAct, SIGNAL(triggered()), this, SLOT(cut()));

	m_copyAct = new QAction(QIcon(":/images/editcopy.png"), tr("&Copy"), this);
	m_copyAct->setShortcut(tr("Ctrl+C"));
	m_copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
	connect(m_copyAct, SIGNAL(triggered()), this, SLOT(copy()));

	m_pasteAct = new QAction(QIcon(":/images/editpaste.png"), tr("&Paste"), this);
	m_pasteAct->setShortcut(tr("Ctrl+V"));
	m_pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
	connect(m_pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

	m_selectAllAct = new QAction(tr("&Select all"), this);
	m_selectAllAct->setShortcut(tr("Ctrl+A"));
	m_selectAllAct->setStatusTip(tr("Select whole text in the editor"));
	connect(m_selectAllAct, SIGNAL(triggered()), this, SLOT(selectAll()));

	m_findAct = new QAction(QIcon(":/images/find.png"), tr("&Find"), this);
	m_findAct->setShortcut(tr("Ctrl+F"));
	m_findAct->setStatusTip(tr("Find text"));
	connect(m_findAct, SIGNAL(triggered()), this, SLOT(findDialog()));

	m_findNextAct = new QAction(QIcon(":/images/next.png"), tr("Find ne&xt"), this);
	m_findNextAct->setShortcut(tr("F3"));
	m_findNextAct->setStatusTip(tr("Find next occurence of the text"));
	connect(m_findNextAct, SIGNAL(triggered()), this, SLOT(findNext()));

	m_findPreviousAct = new QAction(QIcon(":/images/previous.png"), tr("Find pre&vious"), this);
	m_findPreviousAct->setShortcut(tr("Shift+F3"));
	m_findPreviousAct->setStatusTip(tr("Find previous occurence of the text"));
	connect(m_findPreviousAct, SIGNAL(triggered()), this, SLOT(findPrevious()));

	m_replaceAct = new QAction(tr("&Replace"), this);
	m_replaceAct->setShortcut(tr("Ctrl+R"));
	m_replaceAct->setStatusTip(tr("Replace text"));
	connect(m_replaceAct, SIGNAL(triggered()), this, SLOT(replaceDialog()));

	m_tileAct = new QAction(tr("&Tile"), this);
	m_tileAct->setStatusTip(tr("Tile the windows"));
	connect(m_tileAct, SIGNAL(triggered()), m_mdiArea, SLOT(tileSubWindows()));

	m_cascadeAct = new QAction(tr("&Cascade"), this);
	m_cascadeAct->setStatusTip(tr("Cascade the windows"));
	connect(m_cascadeAct, SIGNAL(triggered()), m_mdiArea, SLOT(cascadeSubWindows()));

	m_nextAct = new QAction(QIcon(":/images/next.png"), tr("Ne&xt"), this);
	m_nextAct->setStatusTip(tr("Move the focus to the next window"));
	connect(m_nextAct, SIGNAL(triggered()), m_mdiArea, SLOT(activateNextSubWindow()));

	m_previousAct = new QAction(QIcon(":/images/previous.png"), tr("Pre&vious"), this);
	m_previousAct->setStatusTip(tr("Move the focus to the previous window"));
	connect(m_previousAct, SIGNAL(triggered()), m_mdiArea, SLOT(activatePreviousSubWindow()));

	m_separatorAct = new QAction(this);
	m_separatorAct->setSeparator(true);

	m_aboutAct = new QAction(tr("&About"), this);
	m_aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(m_aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	m_aboutQtAct = new QAction(tr("About &Qt"), this);
	m_aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(m_aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	m_runScriptAct = new QAction(QIcon(":/images/run.png"), tr("&Run"), this);
	m_runScriptAct->setShortcut(tr("F5"));
	m_runScriptAct->setStatusTip(tr("Run current script"));
	connect(m_runScriptAct, SIGNAL(triggered()), this, SLOT(runScript()));

	m_stopScriptAct = new QAction(QIcon(":/images/stop.png"), tr("&Stop"), this);
	m_stopScriptAct->setShortcut(tr("Shift+F5"));
	m_stopScriptAct->setStatusTip(tr("Stop the executed script"));
	connect(m_stopScriptAct, SIGNAL(triggered()), context, SLOT(stopScript()));

	m_debugRunAct = new QAction(QIcon(":/images/dbgrun.png"), tr("&Continue"), this);
	m_debugRunAct->setShortcut(tr("F9"));
	m_debugRunAct->setStatusTip(tr("Continue execution until next breakpoint or script exit"));
	connect(m_debugRunAct, SIGNAL(triggered()), context, SLOT(debugRun()));

	m_debugStepAct = new QAction(QIcon(":/images/dbgstep.png"), tr("Step &into"), this);
	m_debugStepAct->setShortcut(tr("F10"));
	m_debugStepAct->setStatusTip(tr("Execute the next command, but step inside functions"));
	connect(m_debugStepAct, SIGNAL(triggered()), context, SLOT(debugStep()));

	m_debugOverAct = new QAction(QIcon(":/images/dbgnext.png"), tr("Step o&ver"), this);
	m_debugOverAct->setShortcut(tr("F11"));
	m_debugOverAct->setStatusTip(tr("Execute the next command, over the functions"));
	connect(m_debugOverAct, SIGNAL(triggered()), context, SLOT(debugOver()));

	m_debugOutAct = new QAction(QIcon(":/images/dbgstepout.png"), tr("Step &out"), this);
	m_debugOutAct->setShortcut(tr("F12"));
	m_debugOutAct->setStatusTip(tr("Continue execution until return from this function"));
	connect(m_debugOutAct, SIGNAL(triggered()), context, SLOT(debugOut()));

	m_debugLocationAct = new QAction(QIcon(":/images/location.png"), tr("&Location"), this);
	m_debugLocationAct->setShortcut(tr("Ctrl+L"));
	m_debugLocationAct->setStatusTip(tr("Show the currently executed location"));
	connect(m_debugLocationAct, SIGNAL(triggered()), this, SLOT(showLocation()));

	m_enableBreakpointsAct = new QAction(QIcon(":/images/breakpointstoggle.png"), tr("Toggle &breakpoints"), this);
	m_enableBreakpointsAct->setCheckable(true);
	m_enableBreakpointsAct->setChecked(true);
	m_enableBreakpointsAct->setStatusTip(tr("Enable or disable stopping the script on breakpoints"));
	connect(m_enableBreakpointsAct, SIGNAL(toggled(bool)), context, SLOT(enableBreakpoints(bool)));

	m_includeDirectoriesAct = new QAction(tr("Include &directories"), this);
	m_includeDirectoriesAct->setStatusTip(tr("Include directories settings"));
	connect(m_includeDirectoriesAct, SIGNAL(triggered()), this, SLOT(includeDirectories()));

	m_scriptParametersAct = new QAction(tr("Script &parameters"), this);
	m_scriptParametersAct->setStatusTip(tr("Script parameters settings"));
	connect(m_scriptParametersAct, SIGNAL(triggered()), this, SLOT(scriptParameters()));

	m_gotoLineAct = new QAction(tr("&Go to line"), this);
	m_gotoLineAct->setShortcut(tr("Ctrl+G"));
	m_gotoLineAct->setStatusTip(tr("Go to the specified line in the document"));
	connect(m_gotoLineAct, SIGNAL(triggered()), this, SLOT(gotoLine()));

	m_editorFontAct = new QAction(QIcon(":/images/fonts.png"), tr("&Editor font"), this);
	m_editorFontAct->setStatusTip(tr("Set the editor font"));
	connect(m_editorFontAct, SIGNAL(triggered()), this, SLOT(editorFont()));

	m_visualizationPointSizeAct = new QAction(QIcon(":/images/pointsize.png"), tr("&Vertices size"), this);
	m_visualizationPointSizeAct->setStatusTip(tr("Set the point size for vertices"));
	connect(m_visualizationPointSizeAct, SIGNAL(triggered()), this, SLOT(visualizationPointSize()));

	m_visualizationLineWidthAct = new QAction(QIcon(":/images/linewidth.png"),tr("&Edges width"), this);
	m_visualizationLineWidthAct->setStatusTip(tr("Set the line width for edges"));
	connect(m_visualizationLineWidthAct, SIGNAL(triggered()), this, SLOT(visualizationLineWidth()));
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::createMenus()
{
	QAction* tmp;

	// File
	m_fileMenu = menuBar()->addMenu(tr("&File"));
	m_fileMenu->addAction(m_newAct);
	m_fileMenu->addAction(m_openAct);
	m_fileMenu->addAction(m_saveAct);
	m_fileMenu->addAction(m_saveAsAct);
	m_fileMenu->addAction(m_saveAllAct);
	m_fileMenu->addSeparator();
	m_fileMenu->addAction(m_closeAct);
	m_fileMenu->addAction(m_closeAllAct);
	m_fileMenu->addSeparator();
	m_fileMenu->addAction(m_loadLayoutAct);
	m_fileMenu->addAction(m_saveLayoutAct);
	m_fileMenu->addSeparator();
	m_fileMenu->addAction(m_exitAct);

	// Edit
	m_editMenu = menuBar()->addMenu(tr("&Edit"));
	m_editMenu->addAction(m_undoAct);
	m_editMenu->addAction(m_redoAct);
	m_editMenu->addSeparator();
	m_editMenu->addAction(m_cutAct);
	m_editMenu->addAction(m_copyAct);
	m_editMenu->addAction(m_pasteAct);
	m_editMenu->addAction(m_selectAllAct);
	m_editMenu->addSeparator();
	m_editMenu->addAction(m_findAct);
	m_editMenu->addAction(m_findNextAct);
	m_editMenu->addAction(m_findPreviousAct);
	m_editMenu->addAction(m_replaceAct);
	m_editMenu->addSeparator();
	m_editMenu->addAction(m_gotoLineAct);


	// View
	m_viewMenu = menuBar()->addMenu(tr("&View"));

	tmp = m_dockFiles->toggleViewAction();
	tmp->setText(tmp->text() + tr(" dock"));
	m_viewMenu->addAction(tmp);

	tmp = m_dockScriptOutput->toggleViewAction();
	tmp->setText(tmp->text() + tr(" dock"));
	m_viewMenu->addAction(tmp);

	tmp = m_dockCallStack->toggleViewAction();
	tmp->setText(tmp->text() + tr(" dock"));
	m_viewMenu->addAction(tmp);

	tmp = m_dockVariables->toggleViewAction();
	tmp->setText(tmp->text() + tr(" dock"));
	m_viewMenu->addAction(tmp);

	tmp = m_dockVisualization->toggleViewAction();
	tmp->setText(tmp->text() + tr(" dock"));
	m_viewMenu->addAction(tmp);

	m_viewMenu->addSeparator();

	tmp = m_fileToolBar->toggleViewAction();
	tmp->setText(tmp->text() + tr(" toolbar"));
	m_viewMenu->addAction(tmp);

	tmp = m_editToolBar->toggleViewAction();
	tmp->setText(tmp->text() + tr(" toolbar"));
	m_viewMenu->addAction(tmp);

	tmp = m_scriptToolBar->toggleViewAction();
	tmp->setText(tmp->text() + tr(" toolbar"));
	m_viewMenu->addAction(tmp);


	// Script
	m_scriptMenu = menuBar()->addMenu(tr("&Script"));
	m_scriptMenu->addAction(m_runScriptAct);
	m_scriptMenu->addAction(m_stopScriptAct);
	m_scriptMenu->addSeparator();
	m_scriptMenu->addAction(m_debugRunAct);
	m_scriptMenu->addAction(m_debugStepAct);
	m_scriptMenu->addAction(m_debugOverAct);
	m_scriptMenu->addAction(m_debugOutAct);
	m_scriptMenu->addAction(m_debugLocationAct);
	m_scriptMenu->addSeparator();
	m_scriptMenu->addAction(m_enableBreakpointsAct);
	m_scriptMenu->addSeparator();
	m_scriptMenu->addAction(m_scriptParametersAct);
	m_scriptMenu->addAction(m_includeDirectoriesAct);


	// Visualization
	m_visualizationMenu = menuBar()->addMenu(tr("&Visualization"));
	updateVisualizationMenu();
	connect(m_dockVisualization->getVisualization(), SIGNAL(containersChanged()),
			this, SLOT(updateVisualizationMenu()));


	// Settings
	m_settingsMenu = menuBar()->addMenu(tr("&Settings"));
	m_settingsMenu->addAction(m_editorFontAct);
	m_settingsMenu->addSeparator();
	m_settingsMenu->addAction(m_visualizationPointSizeAct);
	m_settingsMenu->addAction(m_visualizationLineWidthAct);


	// Window
	m_windowMenu = menuBar()->addMenu(tr("&Window"));
	updateWindowMenu();
	connect(m_windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

	menuBar()->addSeparator();


	// Help
	m_helpMenu = menuBar()->addMenu(tr("&Help"));
	m_helpMenu->addAction(m_aboutAct);
	m_helpMenu->addAction(m_aboutQtAct);
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::createToolBars()
{
	m_fileToolBar = addToolBar(tr("File"));
	m_fileToolBar->setObjectName("File");
	m_fileToolBar->addAction(m_newAct);
	m_fileToolBar->addAction(m_openAct);
	m_fileToolBar->addAction(m_saveAct);
	m_fileToolBar->addAction(m_saveAsAct);
	m_fileToolBar->addAction(m_saveAllAct);
	m_fileToolBar->addAction(m_closeAct);

	m_editToolBar = addToolBar(tr("Edit"));
	m_editToolBar->setObjectName("Edit");
	m_editToolBar->addAction(m_undoAct);
	m_editToolBar->addAction(m_redoAct);
	m_editToolBar->addAction(m_cutAct);
	m_editToolBar->addAction(m_copyAct);
	m_editToolBar->addAction(m_pasteAct);

	m_scriptToolBar = addToolBar(tr("Script"));
	m_scriptToolBar->setObjectName("Script");
	m_scriptToolBar->addAction(m_runScriptAct);
	m_scriptToolBar->addAction(m_stopScriptAct);
	m_scriptToolBar->addAction(m_debugRunAct);
	m_scriptToolBar->addAction(m_debugStepAct);
	m_scriptToolBar->addAction(m_debugOverAct);
	m_scriptToolBar->addAction(m_debugOutAct);
	m_scriptToolBar->addAction(m_debugLocationAct);
	m_scriptToolBar->addAction(m_enableBreakpointsAct);
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::statusBarMessage(const QString& str)
{
	statusBar()->showMessage(str);
}

void MainWindow::statusBarMessageWithTimeout(const QString& str)
{
	statusBar()->showMessage(str, 2000);
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::createDocks()
{
	// Files
	m_dockFiles = new DockFiles(this);
	m_dockFiles->setObjectName("Files");
	addDockWidget(Qt::LeftDockWidgetArea, m_dockFiles);
	connect(m_dockFiles, SIGNAL(fileSelected(QString)),
			this, SLOT(fileSelected(QString)));
	connect(m_dockFiles, SIGNAL(directoryChanged(QString)),
			this, SLOT(statusBarMessageWithTimeout(QString)));


	// Script output
	m_dockScriptOutput = new DockScriptOutput(this);
	m_dockScriptOutput->setObjectName("ScriptOutput");
	addDockWidget(Qt::BottomDockWidgetArea, m_dockScriptOutput);

	GuiLogger* logger = dynamic_cast<GuiLogger*>(ObjectCreator::getInstance().getLogger());
	assert(logger != NULL);
	connect(logger, SIGNAL(error(QString)), m_dockScriptOutput, SLOT(error(QString)));
	connect(logger, SIGNAL(error(QString, QString)), m_dockScriptOutput, SLOT(error(QString, QString)));
	connect(logger, SIGNAL(warn(QString)), m_dockScriptOutput, SLOT(warn(QString)));
	connect(logger, SIGNAL(warn(QString, QString)), m_dockScriptOutput, SLOT(warn(QString, QString)));
	connect(logger, SIGNAL(info(QString)), m_dockScriptOutput, SLOT(info(QString)));
	connect(logger, SIGNAL(info(QString, QString)), m_dockScriptOutput, SLOT(info(QString, QString)));
	connect(logger, SIGNAL(scriptStdout(QString)), m_dockScriptOutput, SLOT(scriptStdout(QString)));
	connect(m_dockScriptOutput, SIGNAL(anchorClicked(QString, int)),
			this, SLOT(openAndScroll(const QString&, int)));


	// Call stack
	m_dockCallStack = new DockCallStack(this);
	m_dockCallStack->setObjectName("CallStack");
	addDockWidget(Qt::BottomDockWidgetArea, m_dockCallStack);
	connect(m_dockCallStack, SIGNAL(openRequest(const QString&, int)),
		this, SLOT(openAndScroll(const QString&, int)));


	// Variables
	m_dockVariables = new DockVariables(this);
	m_dockVariables->setObjectName("Variables");
	addDockWidget(Qt::BottomDockWidgetArea, m_dockVariables);


	// Visualization
	m_dockVisualization = new DockVisualization(this);
	m_dockVisualization->setObjectName("Visualization");
	addDockWidget(Qt::RightDockWidgetArea, m_dockVisualization);
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::readSettings()
{
	restoreGeometry(SETTINGS.getApplicationGeometry());
	restoreState(SETTINGS.getApplicationState());
	m_dockFiles->setRootIndex(SETTINGS.getDockFilesPath());

	foreach(QString path, SETTINGS.getOpenedFiles())
		open(path, false);
}

void MainWindow::writeSettings()
{
	SETTINGS.setApplicationGeometry(saveGeometry());
	SETTINGS.setApplicationState(saveState());
	SETTINGS.setDockFilesPath(m_dockFiles->rootIndex());

	// Opened files
	QStringList openedFiles;

	foreach(QMdiSubWindow* window, m_mdiArea->subWindowList(QMdiArea::StackingOrder))
	{
		TextEditor* editor = qobject_cast<TextEditor *>(window->widget());
		assert(editor != NULL);

		if(!editor->isUntitled())
			openedFiles << editor->currentFile();
	}

	SETTINGS.setOpenedFiles(openedFiles);
}


/////////////////////////////////////////////////////////////////////////////
////

TextEditor* MainWindow::activeTextEditor()
{
	if(QMdiSubWindow* window = m_mdiArea->activeSubWindow())
		return qobject_cast<TextEditor*>(window->widget());

	return 0;
}

QMdiSubWindow* MainWindow::findTextEditor(const QString &fileName)
{
	QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

	foreach(QMdiSubWindow* window, m_mdiArea->subWindowList())
	{
		TextEditor* editor = qobject_cast<TextEditor*>(window->widget());
		assert(editor != NULL);

		if(editor->currentFile() == canonicalFilePath)
			return window;
	}

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::setActiveSubWindow(QWidget* window)
{
	if(!window)
		return;

	m_mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(window));
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::saveLayout()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save layout"));
	if(fileName.isEmpty())
		return;

	QFile file(fileName);
	if(!file.open(QFile::WriteOnly))
	{
		QString msg = tr("Failed to open %1\n%2")
			.arg(fileName)
			.arg(file.errorString());
		QMessageBox::warning(this, tr("Error"), msg);
		return;
	}

	QByteArray geo_data = saveGeometry();
	QByteArray layout_data = saveState();

	bool ok = file.putChar((uchar)geo_data.size());
	if(ok)
		ok = file.write(geo_data) == geo_data.size();
	if(ok)
		ok = file.write(layout_data) == layout_data.size();

	if(!ok)
	{
		QString msg = tr("Error writing to %1\n%2")
			.arg(fileName)
			.arg(file.errorString());
		QMessageBox::warning(this, tr("Error"), msg);
		return;
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::loadLayout()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Load layout"));
	if(fileName.isEmpty())
		return;
	QFile file(fileName);
	if(!file.open(QFile::ReadOnly))
	{
		QString msg = tr("Failed to open %1\n%2")
			.arg(fileName)
			.arg(file.errorString());
		QMessageBox::warning(this, tr("Error"), msg);
		return;
	}

	uchar geo_size;
	QByteArray geo_data;
	QByteArray layout_data;

	bool ok = file.getChar((char*)&geo_size);
	if(ok)
	{
		geo_data = file.read(geo_size);
		ok = geo_data.size() == geo_size;
	}
	if(ok)
	{
		layout_data = file.readAll();
		ok = layout_data.size() > 0;
	}

	if(ok)
		ok = restoreGeometry(geo_data);
	if(ok)
		ok = restoreState(layout_data);

	if(!ok)
	{
		QString msg = tr("Error reading %1").arg(fileName);
		QMessageBox::warning(this, tr("Error"), msg);
		return;
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::fileSelected(const QString& path)
{
	open(path, true);
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::runScript()
{
	if(m_scriptThread->isRunning())
		return;

	saveAll();

	TextEditor* editor = activeTextEditor();
	if(editor == NULL)
	{
		m_dockScriptOutput->error(tr("No text editor is active!"));
		return;
	}

	m_dockScriptOutput->reinit();

	m_scriptThread->setScriptFilename(editor->currentFile());
	m_scriptThread->setIncludeDirectories(SETTINGS.getIncludeDirectories());
	m_scriptThread->setScriptParameters(SETTINGS.getScriptParameters());
	m_scriptThread->enableBreakpoints(m_enableBreakpointsAct->isChecked());
	m_scriptThread->start();
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::scriptStarted(void)
{
	m_runScriptAct->setEnabled(false);
	m_stopScriptAct->setEnabled(true);
	m_debugRunAct->setEnabled(true);
	m_debugStepAct->setEnabled(true);
	m_debugOverAct->setEnabled(true);
	m_debugOutAct->setEnabled(true);
	m_debugLocationAct->setEnabled(true);
	m_dockCallStack->clear();
	m_dockVariables->clear();
}

void MainWindow::scriptFinished(void)
{
	m_runScriptAct->setEnabled(true);
	m_stopScriptAct->setEnabled(false);
	m_debugRunAct->setEnabled(false);
	m_debugStepAct->setEnabled(false);
	m_debugOverAct->setEnabled(false);
	m_debugOutAct->setEnabled(false);
	m_debugLocationAct->setEnabled(false);
	m_dockCallStack->clear();
	m_dockVariables->clear();
	m_dockVisualization->getVisualization()->clear();
	m_dockVisualization->getVisualization()->updateGL();
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::scriptPaused(void)
{
	ACCESS_MUTEX_LOCKER;

	// Update position in the code
	const CodePosition* pos = CONTEXT.getPosition();
	openAndScroll(QString::fromStdString(ID2STR(pos->getFile())), pos->getLine());

	// Update call stack dock
	m_dockCallStack->clear();
	const deque<CallStackItem>& callStack = CONTEXT.getCallStack();
	deque<CallStackItem>::const_iterator it;

	for(it = callStack.begin(); it != callStack.end(); it++)
	{
		m_dockCallStack->insert(
			QString::fromStdString(ID2STR(it->getFunctionName())),
			QString::fromStdString(ID2STR(it->getReturnAddress()->getFile())),
			it->getReturnAddress()->getLine()
		);
	}

	// Update variables dock
	m_dockVariables->clear();
	const map<identifier, CountPtr<Value> >& vars = callStack.back().getVariables();
	map<identifier, CountPtr<Value> >::const_iterator itv;

	for(itv = vars.begin(); itv != vars.end(); itv++)
	{
		m_dockVariables->insert(
			QString::fromStdString(ID2STR(itv->first)),
			QString::fromStdString(itv->second->toString())
		);
	}

	// Update visualization window
	repaintVisualization();
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::repaintVisualization(void)
{
	m_dockVisualization->getVisualization()->updateGL();
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::includeDirectories(void)
{
	DialogIncludeDirs dlg(this);
	dlg.setDirectories(SETTINGS.getIncludeDirectories());
	if(dlg.exec() == QDialog::Accepted)
		SETTINGS.setIncludeDirectories(dlg.getDirectories());
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::scriptParameters(void)
{
	DialogScriptParameters dlg(this);
	dlg.setParameters(SETTINGS.getScriptParameters());
	if(dlg.exec() == QDialog::Accepted)
		SETTINGS.setScriptParameters(dlg.getParameters());
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::gotoLine(void)
{
	TextEditor* editor = activeTextEditor();
	if(editor == NULL)
	{
		statusBarMessageWithTimeout(tr("No text editor is active"));
		return;
	}

	bool ok = false;
	int val = QInputDialog::getInteger(this, tr("Go to line"),
		tr("Line 1 - ") + QString::number(editor->blockCount()),
		editor->textCursor().blockNumber()+1, 1, editor->blockCount(), 1, &ok);

	if(ok)
		editor->setTextCursor(QTextCursor(editor->document()->findBlockByNumber(val-1)));;
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::findDialog(void)
{
	TextEditor* editor = activeTextEditor();
	if(editor == NULL)
	{
		statusBarMessageWithTimeout(tr("No text editor is active"));
		return;
	}

	QString text;
	QTextCursor cursor(editor->textCursor());
	if(!cursor.hasSelection())
		cursor.select(QTextCursor::WordUnderCursor);

	text = cursor.selectedText();

	if(text.isEmpty())
		text = m_findText;

	DialogFind dlg(this);
	dlg.setText(text);
	dlg.setFlags(m_findFlags);

	if(dlg.exec() == QDialog::Accepted)
	{
		m_findText = dlg.getText();
		m_findFlags = dlg.getFlags();

		// The editor will not have the focus if the dialog is active
		editor->findText(m_findText, m_findFlags);
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::findNext(void)
{
	TextEditor* editor = activeTextEditor();
	if(editor == NULL)
	{
		statusBarMessageWithTimeout(tr("No text editor is active"));
		return;
	}

	m_findFlags &= ~QTextDocument::FindBackward;
	editor->findText(m_findText, m_findFlags);
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::findPrevious(void)
{
	TextEditor* editor = activeTextEditor();
	if(editor == NULL)
	{
		statusBarMessageWithTimeout(tr("No text editor is active"));
		return;
	}

	m_findFlags |= QTextDocument::FindBackward;
	editor->findText(m_findText, m_findFlags);
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::replaceDialog(void)
{
	TextEditor* editor = activeTextEditor();
	if(editor == NULL)
	{
		statusBarMessageWithTimeout(tr("No text editor is active"));
		return;
	}

	QString text;
	QTextCursor cursor(editor->textCursor());
	if(!cursor.hasSelection())
		cursor.select(QTextCursor::WordUnderCursor);

	text = cursor.selectedText();

	if(text.isEmpty())
		text = m_replaceFind;

	DialogReplace dlg(this);
	dlg.setTextFind(text);
	dlg.setTextReplace(m_replaceReplacement);
	dlg.setFlags(m_replaceFlags);
	dlg.setPrompt(m_replacePrompt);

	if(dlg.exec() == QDialog::Accepted)
	{
		m_replaceFind = dlg.getTextFind();
		m_replaceReplacement = dlg.getTextReplace();
		m_replaceFlags = dlg.getFlags();
		m_replacePrompt = dlg.getPrompt();

		// The editor will not have the focus if the dialog is active
		int num = editor->replaceText(m_replaceFind, m_replaceReplacement, m_replaceFlags, m_replacePrompt);
		QMessageBox::information(this, tr("Replace"), tr("%1 replacements made").arg(num));
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::showLocation(void)
{
	ACCESS_MUTEX_LOCKER;
	const CodePosition* pos = CONTEXT.getPosition();
	openAndScroll(QString::fromStdString(ID2STR(pos->getFile())), pos->getLine());
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::editorFont(void)
{
	QList<QMdiSubWindow*> windowList(m_mdiArea->subWindowList());

	QFont font(QFontDialog::getFont(0, SETTINGS.getEditorFont(), this));
	SETTINGS.setEditorFont(font);

	foreach(QMdiSubWindow* window, windowList)
	{
		TextEditor* editor = qobject_cast<TextEditor*>(window->widget());
		assert(editor != NULL);
		editor->setFont(font);
	}

	m_dockScriptOutput->getTextBrowser()->setFont(font);
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::visualizationPointSize(void)
{
	bool ok;
	double size = QInputDialog::getDouble(this, tr("Vertices size"),
		tr("The size of the points"), SETTINGS.getVisualizationPointSize(), 1.0, 100.0, 1, &ok);
	if(ok)
	{
		SETTINGS.setVisualizationPointSize(size);
		repaintVisualization();
	}
}

void MainWindow::visualizationLineWidth(void)
{
	bool ok;
	double size = QInputDialog::getDouble(this, tr("Edges width"),
		tr("The width of the lines"), SETTINGS.getVisualizationLineWidth(), 1.0, 100.0, 1, &ok);
	if(ok)
	{
		SETTINGS.setVisualizationLineWidth(size);
		repaintVisualization();
	}
}
