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

#include <QFont>

#define SETTINGS Settings::getInstance()

// Singleton
class Settings
{
public:
	static inline Settings& getInstance(void)
	{
		return m_instance;
	}

	void init(void);

	const QByteArray& getApplicationGeometry(void) const { return m_applicationGeometry; }
	void setApplicationGeometry(const QByteArray& geometry);

	const QByteArray& getApplicationState(void) const { return m_aplicationState; }
	void setApplicationState(const QByteArray& state);

	const QString& getDockFilesPath(void) const { return m_dockFilesPath; }
	void setDockFilesPath(const QString& path);

	const QStringList& getOpenedFiles(void) const { return m_openedFiles; }
	void setOpenedFiles(const QStringList& files);

	const QStringList& getIncludeDirectories(void) const { return m_includeDirectories; }
	void setIncludeDirectories(const QStringList& dirs);

	const QStringList& getScriptParameters(void) const { return m_scriptParameters; }
	void setScriptParameters(const QStringList& parameters);

	const QFont& getEditorFont(void) const { return m_editorFont; }
	void setEditorFont(const QFont& font);

	float getVisualizationPointSize(void) const { return m_visualizationPointSize; }
	void setVisualizationPointSize(float size);

	float getVisualizationLineWidth(void) const { return m_visualizationLineWidth; }
	void setVisualizationLineWidth(float width);

	const QString& getScreenshotsDirectory(void) const { return m_screenshotsDirectory; }
	void setScreenshotsDirectory(const QString& directory);

	int getTabStopWidth(void) const { return m_tabStopWidth; }
	void setTabStopWidth(int width);

	int getVertLinePos(void) const { return m_vertLinePos; }
	void setVertLinePos(int pos);

	bool getWrapLines(void) const { return m_wrapLines; }
	void setWrapLines(bool wrap);

	bool getUseSpaces(void) const { return m_useSpaces; }
	void setUseSpaces(bool use);

	bool getRemoveTrailingSpaces(void) const { return m_removeTrailingSpaces; }
	void setRemoveTrailingSpaces(bool remove);

private:
	Settings(void);
	~Settings(void);

	Settings(const Settings& object);
	Settings& operator=(const Settings& object);

private:
	static Settings m_instance;

	QByteArray m_applicationGeometry;
	QByteArray m_aplicationState;
	QString m_dockFilesPath;
	QStringList m_openedFiles;
	QStringList m_includeDirectories;
	QStringList m_scriptParameters;
	QFont m_editorFont;
	float m_visualizationPointSize;
	float m_visualizationLineWidth;
	QString m_screenshotsDirectory;
	int m_tabStopWidth;
	int m_vertLinePos;// In characters
	bool m_wrapLines;
	bool m_useSpaces;
	bool m_removeTrailingSpaces;
};

#endif // SETTINGS_H
