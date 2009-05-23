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
#include "settings.h"


/////////////////////////////////////////////////////////////////////////////
////

// TODO: static object initialization
Settings Settings::m_instance;


/////////////////////////////////////////////////////////////////////////////
////

Settings::Settings()
	: m_settings(NULL)
{

}

Settings::~Settings()
{
	assert(m_settings != NULL);
	delete m_settings;
	m_settings = NULL;
}

void Settings::initSingleton(void)
{
	assert(m_settings == NULL);// Verify initSingleton() is called just once
	m_settings = new QSettings();
}


/////////////////////////////////////////////////////////////////////////////
////

QByteArray Settings::getApplicationGeometry(void)
{
	return m_settings->value("geometry", QByteArray()).toByteArray();
}

void Settings::setApplicationGeometry(const QByteArray& geometry)
{
	m_settings->setValue("geometry", geometry);
}


/////////////////////////////////////////////////////////////////////////////
////

QByteArray Settings::getApplicationState(void)
{
	return m_settings->value("state", QByteArray()).toByteArray();
}

void Settings::setApplicationState(const QByteArray& state)
{
	m_settings->setValue("state", state);
}


/////////////////////////////////////////////////////////////////////////////
////

QString Settings::getDockFilesPath(void)
{
	return m_settings->value("dockfilespath", QDir::homePath()).toString();
}

void Settings::setDockFilesPath(const QString& path)
{
	m_settings->setValue("dockfilespath", path);
}


/////////////////////////////////////////////////////////////////////////////
////

QStringList Settings::getOpenedFiles(void)
{
	return m_settings->value("openedfiles", QStringList()).toStringList();
}

void Settings::setOpenedFiles(const QStringList& files)
{
	m_settings->setValue("openedfiles", files);
}


/////////////////////////////////////////////////////////////////////////////
////

QStringList Settings::getIncludeDirectories(void)
{
	return m_settings->value("includedirectories", QStringList()).toStringList();
}

void Settings::setIncludeDirectories(const QStringList& files)
{
	m_settings->setValue("includedirectories", files);
}
