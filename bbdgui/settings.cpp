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
#include <QSettings>
#include <QDir>
#include <QFont>
#include "settings.h"


/////////////////////////////////////////////////////////////////////////////
////

Settings Settings::m_instance;


/////////////////////////////////////////////////////////////////////////////
////

Settings::Settings()
	: m_applicationGeometry(),
	m_aplicationState(),
	m_dockFilesPath(""),
	m_openedFiles(),
	m_includeDirectories(),
	m_scriptParameters(),
	m_editorFont(),
	m_visualizationPointSize(10.0f),
	m_visualizationLineWidth(1.0f),
	m_screenshotsDirectory(""),
	m_tabStopWidth(4),
	m_vertLinePos(80),
	m_wrapLines(false),
	m_useSpaces(false)
{

}

Settings::~Settings()
{

}

void Settings::init(void)
{
	QSettings settings;
	bool ok;

	m_applicationGeometry = settings.value("geometry", QByteArray()).toByteArray();
	m_aplicationState = settings.value("state", QByteArray()).toByteArray();
	m_dockFilesPath = settings.value("dockfilespath", QDir::homePath()).toString();
	m_openedFiles = settings.value("openedfiles", QStringList()).toStringList();
	m_includeDirectories = settings.value("includedirectories", QStringList()).toStringList();
	m_scriptParameters = settings.value("scriptparameters", QStringList()).toStringList();

	m_editorFont = QFont(settings.value("editorfontfamily", "Monospace").toString(),
		settings.value("editorfontpointsize", 9).toInt());
	m_editorFont.setStyleHint(QFont::TypeWriter);

	m_visualizationPointSize = settings.value("visualizationpointsize", 10.0f).toDouble(&ok);
	if(!ok)
		m_visualizationPointSize = 10.0f;

	m_visualizationLineWidth = settings.value("visualizationlinewidth", 1.0f).toDouble(&ok);
	if(!ok)
		m_visualizationLineWidth = 1.0f;

	m_screenshotsDirectory = settings.value("screenshotsdirectory", QDir::homePath()).toString();

	m_tabStopWidth = settings.value("tabstopwidth", 4).toInt(&ok);
	if(!ok)
		m_tabStopWidth = 4;

	m_vertLinePos = settings.value("vertlinepos", 80).toInt(&ok);
	if(!ok)
		m_vertLinePos = 80;

	m_wrapLines = settings.value("wraplines", false).toBool();
	m_useSpaces = settings.value("usespaces", false).toBool();
}


/////////////////////////////////////////////////////////////////////////////
////

void Settings::setApplicationGeometry(const QByteArray& geometry)
{
	QSettings settings;
	m_applicationGeometry = geometry;
	settings.setValue("geometry", geometry);
}


/////////////////////////////////////////////////////////////////////////////
////

void Settings::setApplicationState(const QByteArray& state)
{
	QSettings settings;
	m_aplicationState = state;
	settings.setValue("state", state);
}


/////////////////////////////////////////////////////////////////////////////
////

void Settings::setDockFilesPath(const QString& path)
{
	QSettings settings;
	m_dockFilesPath = path;
	settings.setValue("dockfilespath", path);
}


/////////////////////////////////////////////////////////////////////////////
////

void Settings::setOpenedFiles(const QStringList& files)
{
	QSettings settings;
	m_openedFiles = files;
	settings.setValue("openedfiles", files);
}


/////////////////////////////////////////////////////////////////////////////
////

void Settings::setIncludeDirectories(const QStringList& dirs)
{
	QSettings settings;
	m_includeDirectories = dirs;
	settings.setValue("includedirectories", dirs);
}


/////////////////////////////////////////////////////////////////////////////
////

void Settings::setScriptParameters(const QStringList& parameters)
{
	QSettings settings;
	m_scriptParameters = parameters;
	settings.setValue("scriptparameters", parameters);
}


/////////////////////////////////////////////////////////////////////////////
////

void Settings::setEditorFont(const QFont& font)
{
	QSettings settings;
	m_editorFont = font;
	settings.setValue("editorfontfamily", font.family());
	settings.setValue("editorfontpointsize", font.pointSize());
}


/////////////////////////////////////////////////////////////////////////////
////

void Settings::setVisualizationPointSize(float size)
{
	QSettings settings;
	m_visualizationPointSize = size;
	settings.setValue("visualizationpointsize", size);
}


/////////////////////////////////////////////////////////////////////////////
////

void Settings::setVisualizationLineWidth(float width)
{
	QSettings settings;
	m_visualizationLineWidth = width;
	settings.setValue("visualizationlinewidth", width);
}


/////////////////////////////////////////////////////////////////////////////
////

void Settings::setScreenshotsDirectory(const QString& directory)
{
	QSettings settings;
	m_screenshotsDirectory = directory;
	settings.setValue("screenshotsdirectory", directory);
}


/////////////////////////////////////////////////////////////////////////////
////

void Settings::setTabStopWidth(int width)
{
	QSettings settings;
	m_tabStopWidth = width;
	settings.setValue("tabstopwidth", width);
}


/////////////////////////////////////////////////////////////////////////////
////

void Settings::setVertLinePos(int pos)
{
	QSettings settings;
	m_vertLinePos = pos;
	settings.setValue("vertlinepos", pos);
}


/////////////////////////////////////////////////////////////////////////////
////

void Settings::setWrapLines(bool wrap)
{
	QSettings settings;
	m_wrapLines = wrap;
	settings.setValue("wraplines", wrap);
}


/////////////////////////////////////////////////////////////////////////////
////

void Settings::setUseSpaces(bool use)
{
	QSettings settings;
	m_useSpaces = use;
	settings.setValue("usespaces", use);
}
