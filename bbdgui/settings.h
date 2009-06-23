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

#ifndef SETTINGS_H
#define SETTINGS_H

#define SETTINGS Settings::getInstance()

class QSettings;

// Singleton
class Settings
{
public:
	static inline Settings& getInstance(void)
	{
		return m_instance;
	}

	void initSingleton(void);

	QByteArray getApplicationGeometry(void);
	void setApplicationGeometry(const QByteArray& geometry);

	QByteArray getApplicationState(void);
	void setApplicationState(const QByteArray& state);

	QString getDockFilesPath(void);
	void setDockFilesPath(const QString& path);

	QStringList getOpenedFiles(void);
	void setOpenedFiles(const QStringList& files);

	QStringList getIncludeDirectories(void);
	void setIncludeDirectories(const QStringList& dirs);

	QStringList getScriptParameters(void);
	void setScriptParameters(const QStringList& parameters);

private:
	Settings(void);
	~Settings(void);

	Settings(const Settings& object);
	Settings& operator=(const Settings& object);

private:
	static Settings m_instance;
	QSettings* m_settings;
};

#endif // SETTINGS_H
