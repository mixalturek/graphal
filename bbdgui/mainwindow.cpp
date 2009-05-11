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
#include "objectcreator.hpp"
#include "logger.hpp"
#include "version.hpp"


/////////////////////////////////////////////////////////////////////////////
////

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),
	m_scriptThread(new ScriptThread())
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

	m_mdiArea->setViewMode(QMdiArea::TabbedView);
	setWindowTitle(tr("bbdgui"));

	connect(m_scriptThread, SIGNAL(started()), this, SLOT(scriptStarted()));
	connect(m_scriptThread, SIGNAL(finished()), this, SLOT(scriptFinished()));
	connect(m_dockScriptOutput->getTextBrowser(), SIGNAL(anchorClicked(QUrl)),
			this, SLOT(open(QUrl)));

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
	writeSettings();
	m_mdiArea->closeAllSubWindows();

	if(activeTextEditor())
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
	if(!fileName.isEmpty())
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

void MainWindow::open(const QUrl& link)
{
	// Links are expected in "filename:line" format
	QStringList path(link.toString().split(':'));

	if(path.size() == 2 && open(path.at(0), true))
	{
		bool ok;
		int line = path.at(1).toInt(&ok);

		TextEditor* editor = activeTextEditor();
		assert(editor != NULL);

		if(ok && line <= editor->blockCount())
		{
			// Three hours of my life to write the following line :-(
			editor->setTextCursor(QTextCursor(editor->document()->findBlockByNumber(line-1)));
			// editor->centerCursor();// TOOD: if it is not visible only
		}

		editor->setFocus();
	}
	else
	{
		assert("Should not be called" == NULL);
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


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::about()
{
	// TODO: update text, version
	QMessageBox::about(this, tr("About bbdgui"),
		tr("Graphs algorithms interpreter<br />SVN version ")
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

	m_tileAct = new QAction(tr("&Tile"), this);
	m_tileAct->setStatusTip(tr("Tile the windows"));
	connect(m_tileAct, SIGNAL(triggered()), m_mdiArea, SLOT(tileSubWindows()));

	m_cascadeAct = new QAction(tr("&Cascade"), this);
	m_cascadeAct->setStatusTip(tr("Cascade the windows"));
	connect(m_cascadeAct, SIGNAL(triggered()), m_mdiArea, SLOT(cascadeSubWindows()));

	m_nextAct = new QAction(tr("Ne&xt"), this);
	m_nextAct->setStatusTip(tr("Move the focus to the next window"));
	connect(m_nextAct, SIGNAL(triggered()), m_mdiArea, SLOT(activateNextSubWindow()));

	m_previousAct = new QAction(tr("Pre&vious"), this);
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
	m_runScriptAct->setShortcut(tr("Ctrl+R"));
	m_runScriptAct->setStatusTip(tr("Execute the script"));
	connect(m_runScriptAct, SIGNAL(triggered()), this, SLOT(runScript()));
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


	// View
	m_viewMenu = menuBar()->addMenu(tr("&View"));

	tmp = m_dockFiles->toggleViewAction();
	tmp->setText(tmp->text() + tr(" dock"));
	m_viewMenu->addAction(tmp);

	tmp = m_dockScriptOutput->toggleViewAction();
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
	m_fileToolBar->setObjectName("File");// TODO: Why is it needed by saveState()?
	m_fileToolBar->addAction(m_newAct);
	m_fileToolBar->addAction(m_openAct);
	m_fileToolBar->addAction(m_saveAct);
	m_fileToolBar->addAction(m_saveAsAct);
	m_fileToolBar->addAction(m_saveAllAct);
	m_fileToolBar->addAction(m_closeAct);

	m_editToolBar = addToolBar(tr("Edit"));
	m_editToolBar->setObjectName("Edit");// TODO: Why is it needed by saveState()?
	m_editToolBar->addAction(m_undoAct);
	m_editToolBar->addAction(m_redoAct);
	m_editToolBar->addAction(m_cutAct);
	m_editToolBar->addAction(m_copyAct);
	m_editToolBar->addAction(m_pasteAct);

	m_scriptToolBar = addToolBar(tr("Script"));
	m_scriptToolBar->setObjectName("Script");
	m_scriptToolBar->addAction(m_runScriptAct);
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
	m_dockFiles->setObjectName("Files");// TODO: Why is it needed by saveState()?
	addDockWidget(Qt::LeftDockWidgetArea, m_dockFiles);
	connect(m_dockFiles, SIGNAL(fileSelected(QString)),
			this, SLOT(fileSelected(QString)));
	connect(m_dockFiles, SIGNAL(directoryChanged(QString)),
			this, SLOT(statusBarMessageWithTimeout(QString)));


	// Script output
	m_dockScriptOutput = new DockScriptOutput(this);
	m_dockScriptOutput->setObjectName("ScriptOutput");// TODO: Why is it needed by saveState()?
	addDockWidget(Qt::BottomDockWidgetArea, m_dockScriptOutput);

	Logger* logger = ObjectCreator::getInstance().getLogger();
	connect(logger, SIGNAL(error(QString)), m_dockScriptOutput, SLOT(error(QString)));
	connect(logger, SIGNAL(error(QString, QString)), m_dockScriptOutput, SLOT(error(QString, QString)));
	connect(logger, SIGNAL(warn(QString)), m_dockScriptOutput, SLOT(warn(QString)));
	connect(logger, SIGNAL(warn(QString, QString)), m_dockScriptOutput, SLOT(warn(QString, QString)));
	connect(logger, SIGNAL(info(QString)), m_dockScriptOutput, SLOT(info(QString)));
	connect(logger, SIGNAL(scriptStdout(QString)), m_dockScriptOutput, SLOT(scriptStdout(QString)));
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
	saveAll();

	TextEditor* editor = activeTextEditor();
	if(editor == NULL)
	{
		m_dockScriptOutput->error(tr("No text editor is active!"));
		return;
	}

	if(!m_scriptThread->isRunning())
	{
		m_scriptThread->setScriptFilename(editor->currentFile());
		m_scriptThread->start();
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::scriptStarted(void)
{
	m_runScriptAct->setEnabled(false);
	m_dockScriptOutput->clear();
}

void MainWindow::scriptFinished(void)
{
	m_runScriptAct->setEnabled(true);
}

