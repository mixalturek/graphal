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


#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <QGLWidget>
#include "countptr.hpp"
#include "value.hpp"

class ITEM
{
public:
	ITEM(CountPtr<Value> value, const QColor& color) : m_value(value), m_color(color) {}
	CountPtr<Value> getValue(void) const { return m_value; }
	QColor getColor(void) const { return m_color; }

private:
	CountPtr<Value> m_value;
	QColor m_color;
};

#define DATA_CONTAINER vector<ITEM>

class Visualization : public QGLWidget
{
	Q_OBJECT

public:
	Visualization(QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags flags = 0);
	virtual ~Visualization(void);

	void clear(void);

public slots:
	void visRegister(CountPtr<Value> object);

protected:
	void initializeGL(void);
	void resizeGL(int width, int height);
	void paintGL(void);

	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);

private:
	DATA_CONTAINER m_vertexSets;
	DATA_CONTAINER m_edgeSets;

	QPoint m_lastMousePos;
	float m_posx;
	float m_posy;
	float m_posz;
	float m_rotx;
	float m_roty;
};

#endif // VISUALIZATION_H
