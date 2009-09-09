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


#ifndef VISUALIZATIONVIEW_H
#define VISUALIZATIONVIEW_H

#include <QObject>

class Visualization;

class VisualizationView : public QObject
{
	Q_OBJECT

public:
	VisualizationView(void);
	VisualizationView(const VisualizationView& object);
	~VisualizationView(void);

	VisualizationView& operator= (const VisualizationView& object);

	static void initInstance(Visualization* vis) { m_visualization = vis; }

	const QString& getName(void) const { return m_name; }
	void setName(const QString& name) { m_name = name; }

	float& getPosX(void) { return m_posx; }
	float& getPosY(void) { return m_posy; }
	float& getPosZ(void) { return m_posz; }
	float& getRotX(void) { return m_rotx; }
	float& getRotY(void) { return m_roty; }

	void setPosX(float pos) { m_posx = pos; }
	void setPosY(float pos) { m_posy = pos; }
	void setPosZ(float pos) { m_posz = pos; }
	void setRotX(float rot) { m_rotx = rot; }
	void setRotY(float rot) { m_roty = rot; }

	void clear(void);

	// Hack for connect()
	const VisualizationView* getMe(void) const { return this; }

public slots:
	void selected(void);

private:
	static Visualization* m_visualization;

	QString m_name;
	float m_posx;
	float m_posy;
	float m_posz;
	float m_rotx;
	float m_roty;
};

#endif // VISUALIZATIONVIEW_H
