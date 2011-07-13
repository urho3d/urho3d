/* Copyright 2010 Jukka Jylänki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

/** @file GraphDialog.cpp
	@brief */

#include <QUiLoader>
#include <QFile>
#include <QVBoxLayout>
#include <QLabel>
#include <QTreeWidget>
#include <QPainter>
#include <sstream>

#ifdef KNET_USE_BOOST
#include <boost/thread/thread.hpp>
#endif

#include "kNet/DebugMemoryLeakCheck.h"
#include "kNet/Network.h"
#include "kNet/qt/GraphDialog.h"
#include "kNet/qt/ui/ui_Graph.h"

namespace kNet
{

/// Specifies in msecs how often we update MessageConnectionDialog.
const int dialogUpdateInterval = 200;

GraphDialog::GraphDialog(QWidget *parent, const char *hierarchyNodeName_)
:QWidget(parent), hierarchyNodeName(hierarchyNodeName_)
{
	dialog = new Ui_GraphDialog;
	dialog->setupUi(this);

	setWindowTitle(hierarchyNodeName.c_str());
}

GraphDialog::~GraphDialog()
{
	delete dialog;
}

QPointF MapPoint(tick_t x, float y, tick_t minX, tick_t maxX, float minY, float maxY, const QPointF &topLeft, const QPointF &bottomRight)
{
	float mappedX = topLeft.x() + (bottomRight.x() - topLeft.x()) * (float)(x - minX) / (maxX - minX);
	float mappedY = bottomRight.y() - (bottomRight.y() - topLeft.y()) * (float)(y - minY) / (maxY - minY);
	return QPointF(mappedX, mappedY);
}

void GraphDialog::Update(StatsEventHierarchyNode &node, int timeMSecs)
{
	QPixmap *image = new QPixmap(dialog->graphLabel->width(), dialog->graphLabel->height());
	{
		QPainter painter(image);
		painter.fillRect(0, 0, image->width(), image->height(), QColor(255, 255, 255, 255));
		painter.setRenderHint(QPainter::Antialiasing, true);

		const QPointF topLeft(5, 5);
		const QPointF bottomRight(image->width() - 5, image->height() - 5);
		const tick_t rightX = Clock::Tick();
		const tick_t leftX = rightX - timeMSecs * Clock::TicksPerSec() / 1000;
		const float minY = 0.f;
		float maxY = 0.f;
		for(int i = 0; i < node.events.Size(); ++i)
		{
			StatsEvent *e = node.events.ItemAt(i);
			if (Clock::IsNewer(e->time, leftX) && Clock::IsNewer(rightX, e->time))
				maxY = max(maxY, e->value);
		}

		painter.setPen(QPen(QColor(0,0,0)));
		for(int i = 0; i+1 < node.events.Size(); ++i)
		{
			StatsEvent *e = node.events.ItemAt(i);
			StatsEvent *e2 = node.events.ItemAt(i+1);
			QPointF pt1 = MapPoint(e->time, e->value, leftX, rightX, minY, maxY, topLeft, bottomRight);
			QPointF pt2 = MapPoint(e2->time, e2->value, leftX, rightX, minY, maxY, topLeft, bottomRight);
			painter.drawLine(pt1, pt2);
		}
	}

	dialog->graphLabel->setPixmap(*image);
}

} // ~kNet
