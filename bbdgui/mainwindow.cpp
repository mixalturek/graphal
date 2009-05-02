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
#include "settings.h"


/////////////////////////////////////////////////////////////////////////////
////

MainWindow::MainWindow()
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
	createDockFiles();
	createMenus();
	createToolBars();
	createStatusBar();
	updateMenus();
	readSettings();

	m_mdiArea->setViewMode(QMdiArea::TabbedView);
	setWindowTitle(tr("bbdgui"));
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
	QMdiSubWindow* subWindow = createTextEditor();
	TextEditor* editor = qobject_cast<TextEditor*>(subWindow->widget());
	assert(editor != NULL);

	editor->newFile();
	subWindow->show();
}

void MainWindow::open()
{
	// TODO: save path to the settings
	QStringList fileName = QFileDialog::getOpenFileNames(this);
	foreach(QString str, fileName)
		open(str, true);
}

void MainWindow::open(const QString& fileName, bool warnIfNotFound)
{
	if(!fileName.isEmpty())
	{
		QMdiSubWindow* existing = findTextEditor(fileName);

		if(existing)
		{
			m_mdiArea->setActiveSubWindow(existing);
			return;
		}

		QMdiSubWindow* subWindow = createTextEditor();
		TextEditor* editor = qobject_cast<TextEditor*>(subWindow->widget());
		assert(editor != NULL);

		if(editor->loadFile(fileName, warnIfNotFound))
		{
			statusBar()->showMessage(tr("File loaded"), 2000);
			subWindow->show();
		}
		else
			subWindow->close();
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
		tr("Graphs algorithms interpreter"));
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

QMdiSubWindow* MainWindow::createTextEditor()
{
	QMdiSubWindow* subWindow = new QMdiSubWindow(m_mdiArea);
	TextEditor* editor = new TextEditor(subWindow);

	subWindow->setAttribute(Qt::WA_DeleteOnClose);
	subWindow->setWidget(editor);

	connect(editor, SIGNAL(copyAvailable(bool)), m_cutAct, SLOT(setEnabled(bool)));
	connect(editor, SIGNAL(copyAvailable(bool)), m_copyAct, SLOT(setEnabled(bool)));

	connect(editor, SIGNAL(undoAvailable(bool)), m_undoAct, SLOT(setEnabled(bool)));
	connect(editor, SIGNAL(redoAvailable(bool)), m_redoAct, SLOT(setEnabled(bool)));

	return m_mdiArea->addSubWindow(subWindow);
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
	m_fileMenu->addAction(m_loadLayoutAct);
	m_fileMenu->addAction(m_saveLayoutAct);
	m_fileMenu->addSeparator();
	m_fileMenu->addAction(m_exitAct);

	m_editMenu = menuBar()->addMenu(tr("&Edit"));
	m_editMenu->addAction(m_undoAct);
	m_editMenu->addAction(m_redoAct);
	m_editMenu->addSeparator();
	m_editMenu->addAction(m_cutAct);
	m_editMenu->addAction(m_copyAct);
	m_editMenu->addAction(m_pasteAct);

	m_viewMenu = menuBar()->addMenu(tr("&View"));
//	QMenu* docks = m_viewMenu->addMenu(tr("&Docks"));
	m_viewMenu->addAction(m_dockFiles->toggleViewAction());


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
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::createStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
}


/////////////////////////////////////////////////////////////////////////////
////


void MainWindow::createDockFiles()
{
	m_dockFiles = new QDockWidget(tr("Files"), this);
	m_dockFiles->setObjectName("Files");// TODO: Why is it needed by saveState()?

	QListView* lview = new QListView(m_dockFiles);
	QDirModel* model = new QDirModel(lview);

	model->setFilter(QDir::AllEntries);
	model->setSorting(QDir::DirsFirst);
	lview->setModel(model);

	connect(lview, SIGNAL(doubleClicked(const QModelIndex &)),
			this, SLOT(fileSelected(const QModelIndex &)));

	m_dockFiles->setWidget(lview);
	addDockWidget(Qt::LeftDockWidgetArea, m_dockFiles);
}


/////////////////////////////////////////////////////////////////////////////
////

void MainWindow::readSettings()
{
	restoreGeometry(SETTINGS.getApplicationGeometry());
	restoreState(SETTINGS.getApplicationState());

	QListView* lview = qobject_cast<QListView*>(m_dockFiles->widget());
	QDirModel* model = qobject_cast<QDirModel*>(lview->model());
	assert(lview != NULL);
	assert(model != NULL);
	lview->setRootIndex(model->index(SETTINGS.getDockFilesPath()));

	foreach(QString path, SETTINGS.getOpenedFiles())
		open(path, false);
}

void MainWindow::writeSettings()
{
	SETTINGS.setApplicationGeometry(saveGeometry());
	SETTINGS.setApplicationState(saveState());

	QListView* lview = qobject_cast<QListView*>(m_dockFiles->widget());
	QDirModel* model = qobject_cast<QDirModel*>(lview->model());
	assert(lview != NULL);
	assert(model != NULL);
	SETTINGS.setDockFilesPath(model->filePath(lview->rootIndex()));

	// Opened files
	QStringList openedFiles;

	foreach(QMdiSubWindow* wnd, m_mdiArea->subWindowList(QMdiArea::StackingOrder))
	{
		TextEditor* editor = qobject_cast<TextEditor *>(wnd->widget());
		assert(editor != NULL);

		if(!editor->isUntitled())
			openedFiles << editor->currentFile();
	}

	SETTINGS.setOpenedFiles(openedFiles);
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

void MainWindow::fileSelected(const QModelIndex& index)
{
	QListView* lview = qobject_cast<QListView*>(m_dockFiles->widget());
	QDirModel* model = qobject_cast<QDirModel*>(lview->model());
	assert(lview != NULL);
	assert(model != NULL);

	if(model->isDir(index))
	{
		lview->setRootIndex(index);
		statusBar()->showMessage(model->filePath(index), 2000);
	}
	else
		open(model->filePath(index), true);
}
