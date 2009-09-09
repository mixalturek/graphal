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
#include "visualizationitemdata.h"
#include "visualizationview.h"


#define VIS_DATA_CONTAINER vector<VisualizationItemData>
#define VIS_VIEW_CONTAINER vector<VisualizationView>

class Visualization : public QGLWidget
{
	Q_OBJECT

public:
	Visualization(QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags flags = 0);
	virtual ~Visualization(void);

	void clear(void);
	bool hasVertices(void) const { return !m_vertexSets.empty(); }
	bool hasEdges(void) const { return !m_edgeSets.empty(); }
	const VIS_DATA_CONTAINER& getVertexSets(void) const { return m_vertexSets; }
	const VIS_DATA_CONTAINER& getEdgeSets(void) const { return m_edgeSets; }

	bool hasViews(void) const { return !m_views.empty(); }
	void setCurrentView(const VisualizationView& view) { m_currentView = view; }
	void saveCurrentView(const QString& name);
	const VIS_VIEW_CONTAINER& getViews(void) const { return m_views; }

signals:
	void containersChanged(void);

public slots:
	void visRegister(const VisualizationItemData& item);
	void resetView(void) { m_currentView.clear(); updateGL(); }

protected:
	void initializeGL(void);
	void resizeGL(int width, int height);
	void paintGL(void);

	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);

private:
	VIS_DATA_CONTAINER m_vertexSets;
	VIS_DATA_CONTAINER m_edgeSets;

	QPoint m_lastMousePos;
	VisualizationView m_currentView;
	VIS_VIEW_CONTAINER m_views;
};

#endif // VISUALIZATION_H
