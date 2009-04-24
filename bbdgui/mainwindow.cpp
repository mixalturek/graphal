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

#include <QtGui>
#include "mainwindow.h"
#include "texteditor.h"


/////////////////////////////////////////////////////////////////////////////
////

MainWindow::MainWindow()
{
	m_mdiArea = new QMdiArea;
	m_mdiArea->setViewMode(QMdiArea::TabbedView);
	setCentralWidget(m_mdiArea);

	connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)),
			this, SLOT(updateMenus()));

	m_windowMapper = new QSignalMapper(this);
	connect(m_windowMapper, SIGNAL(mapped(QWidget *)),
			this, SLOT(setActiveSubWindow(QWidget *)));

	createActions();
	createMenus();
	createToolBars();
	createStatusBar();
	updateMenus();

	readSettings();

	setWindowTitle(tr("bbdgui"));
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::closeEvent(QCloseEvent* event)
{
	m_mdiArea->closeAllSubWindows();

	if(activeTextEditor())
	{
		event->ignore();
	}
	else
	{
		writeSettings();
		event->accept();
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::newFile()
{
	TextEditor* child = createTextEditor();
	child->newFile();
	child->show();
}

void MainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this);

	if(!fileName.isEmpty())
	{
		QMdiSubWindow* existing = findTextEditor(fileName);

		if(existing)
		{
			m_mdiArea->setActiveSubWindow(existing);
			return;
		}

		TextEditor* child = createTextEditor();

		if(child->loadFile(fileName))
		{
			statusBar()->showMessage(tr("File loaded"), 2000);
			child->show();
		}
		else
		{
			child->close();
		}
	}
}

void MainWindow::save()
{
	if(activeTextEditor() && activeTextEditor()->save())
		statusBar()->showMessage(tr("File saved"), 2000);
}

void MainWindow::saveAs()
{
	if(activeTextEditor() && activeTextEditor()->saveAs())
		statusBar()->showMessage(tr("File saved"), 2000);
}

void MainWindow::saveAll()
{
	foreach(QMdiSubWindow *window, m_mdiArea->subWindowList())
	{
		TextEditor* textEditor = qobject_cast<TextEditor*>(window->widget());

		if(textEditor != 0)
			textEditor->save();
	}

	statusBar()->showMessage(tr("Files saved"), 2000);
}


/////////////////////////////////////////////////////////////////////////////
////

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
		tr("Graphs algorithms interpreter"));
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::updateMenus()
{
	bool hasTextEditor = (activeTextEditor() != 0);

	m_saveAct->setEnabled(hasTextEditor);
	m_saveAsAct->setEnabled(hasTextEditor);
	m_saveAllAct->setEnabled(hasTextEditor);
	m_pasteAct->setEnabled(hasTextEditor);
	m_closeAct->setEnabled(hasTextEditor);
	m_closeAllAct->setEnabled(hasTextEditor);
	m_tileAct->setEnabled(hasTextEditor);
	m_cascadeAct->setEnabled(hasTextEditor);
	m_nextAct->setEnabled(hasTextEditor);
	m_previousAct->setEnabled(hasTextEditor);
	m_separatorAct->setVisible(hasTextEditor);

	bool hasSelection = activeTextEditor()
		&& activeTextEditor()->textCursor().hasSelection();

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
		TextEditor* child = qobject_cast<TextEditor*>(windows.at(i)->widget());

		if(i < 9)
			text = tr("&%1 %2").arg(i + 1).arg(child->userFriendlyCurrentFile());
		else
			text = tr("%1 %2").arg(i + 1).arg(child->userFriendlyCurrentFile());

		QAction* action = m_windowMenu->addAction(text);
		action->setCheckable(true);
		action->setChecked(child == activeTextEditor());

		connect(action, SIGNAL(triggered()), m_windowMapper, SLOT(map()));

		m_windowMapper->setMapping(action, windows.at(i));
	}
}


/////////////////////////////////////////////////////////////////////////////
////

TextEditor* MainWindow::createTextEditor()
{
	TextEditor* child = new TextEditor;
	m_mdiArea->addSubWindow(child);

	connect(child, SIGNAL(copyAvailable(bool)), m_cutAct, SLOT(setEnabled(bool)));
	connect(child, SIGNAL(copyAvailable(bool)),	m_copyAct, SLOT(setEnabled(bool)));

	return child;
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

	m_exitAct = new QAction(tr("E&xit"), this);
	m_exitAct->setShortcut(tr("Ctrl+Q"));
	m_exitAct->setStatusTip(tr("Exit the application"));
	connect(m_exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

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
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::createMenus()
{
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
	m_fileMenu->addAction(m_exitAct);

	m_editMenu = menuBar()->addMenu(tr("&Edit"));
	m_editMenu->addAction(m_cutAct);
	m_editMenu->addAction(m_copyAct);
	m_editMenu->addAction(m_pasteAct);

	m_windowMenu = menuBar()->addMenu(tr("&Window"));
	updateWindowMenu();
	connect(m_windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

	menuBar()->addSeparator();

	m_helpMenu = menuBar()->addMenu(tr("&Help"));
	m_helpMenu->addAction(m_aboutAct);
	m_helpMenu->addAction(m_aboutQtAct);
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::createToolBars()
{
	m_fileToolBar = addToolBar(tr("File"));
	m_fileToolBar->addAction(m_newAct);
	m_fileToolBar->addAction(m_openAct);
	m_fileToolBar->addAction(m_saveAct);
	m_fileToolBar->addAction(m_saveAsAct);
	m_fileToolBar->addAction(m_closeAct);

	m_editToolBar = addToolBar(tr("Edit"));
	m_editToolBar->addAction(m_cutAct);
	m_editToolBar->addAction(m_copyAct);
	m_editToolBar->addAction(m_pasteAct);
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::createStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::readSettings()
{
	QSettings settings("bbdgui");

	move(settings.value("pos", QPoint(200, 200)).toPoint());
	resize(settings.value("size", QSize(400, 400)).toSize());
}

void MainWindow::writeSettings()
{
	QSettings settings("bbdgui");

	settings.setValue("pos", pos());
	settings.setValue("size", size());
}


/////////////////////////////////////////////////////////////////////////////
////

TextEditor *MainWindow::activeTextEditor()
{
	if(QMdiSubWindow* activeSubWindow = m_mdiArea->activeSubWindow())
		return qobject_cast<TextEditor *>(activeSubWindow->widget());

	return 0;
}

QMdiSubWindow *MainWindow::findTextEditor(const QString &fileName)
{
	QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

	foreach(QMdiSubWindow *window, m_mdiArea->subWindowList())
	{
		TextEditor* textEditor = qobject_cast<TextEditor*>(window->widget());

		if(textEditor->currentFile() == canonicalFilePath)
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
