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

/** @file NetworkDialog.cpp
	@brief */

#include <QFile>
#include <QVBoxLayout>
#include <QLabel>
#include <QTreeWidget>

#ifdef KNET_USE_BOOST
#include <boost/thread/thread.hpp>
#endif

#include "kNet/DebugMemoryLeakCheck.h"
#include "kNet/StatsEventHierarchy.h"
#include "kNet/qt/NetworkDialog.h"
#include "kNet/qt/MessageConnectionDialog.h"
#include "kNet/qt/GraphDialog.h"
#include "kNet/qt/ui/ui_NetworkDialog.h"

namespace kNet
{

/// Specifies in msecs how often we update NetworkDialog.
const int dialogUpdateInterval = 100;

NetworkDialog::NetworkDialog(QWidget *parent, Network *network_)
:network(network_), QWidget(parent)
{
	dialog = new Ui_NetworkDialog;
	dialog->setupUi(this);

	connect(dialog->connectionsTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(ItemDoubleClicked(QTreeWidgetItem *)));
	connect(dialog->treeStats, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(EventItemDoubleClicked(QTreeWidgetItem *)));

	Update();
}

NetworkDialog::~NetworkDialog()
{
	delete dialog;
}

class MessageConnectionTreeItem : public QTreeWidgetItem
{
public:
	MessageConnectionTreeItem(QTreeWidgetItem *parent, Ptr(MessageConnection) connection_)
	:QTreeWidgetItem(parent), connection(connection_)
	{
		UpdateText();
	}

	void UpdateText()
	{
		if (connection)
			setText(0, connection->ToString().c_str());
	}

	Ptr(MessageConnection) connection;
};

class StatsEventTreeItem : public QTreeWidgetItem
{
public:
	StatsEventTreeItem(QTreeWidgetItem *parent, const char *eventName_)
	:QTreeWidgetItem(parent), eventName(eventName_)
	{
	}

	std::string eventName;
};

QTreeWidgetItem *NewTreeItemFromString(QTreeWidget *parent, const char *str)
{
	QTreeWidgetItem *item = new QTreeWidgetItem(parent);
	item->setText(0, str);
	return item;
}

void GetItems(QTreeWidgetItem *widget, QList<QTreeWidgetItem *> &items)
{
	for(int i = 0; i < widget->childCount(); ++i)
	{
		items.append(widget->child(i));
		GetItems(widget->child(i), items);
	}
}

QTreeWidgetItem *FindItem(QList<QTreeWidgetItem *> &items, void *data)
{
	foreach(QTreeWidgetItem *item, items)
		if (item->data(0, Qt::UserRole).value<void*>() == data)
			return item;
	return 0;
}

void NetworkDialog::Update()
{
	if (!network)
		return;

	QLabel *machineIp = findChild<QLabel*>("machineIP");
	if (!machineIp)
		return;
	QLabel *numRunningThreads = findChild<QLabel*>("numRunningThreads");
	if (!numRunningThreads)
		return;
	QTreeWidget *connectionsTree = findChild<QTreeWidget*>("connectionsTree");
	if (!connectionsTree)
		return;

	machineIp->setText(network->LocalAddress());
	numRunningThreads->setText(QString::number(network->NumWorkerThreads()));

	QList<QTreeWidgetItem *> items;
	GetItems(connectionsTree->invisibleRootItem(), items);
//	connectionsTree->clear();

	Ptr(NetworkServer) server = network->GetServer();
	if (server)
	{
		setWindowTitle("kNet Server");
		QTreeWidgetItem *serverItem = FindItem(items, (void*)server.ptr());
		if (!serverItem)
		{
			serverItem = NewTreeItemFromString(connectionsTree, server->ToString().c_str());
			connectionsTree->addTopLevelItem(serverItem);
		}
		else
			items.removeOne(serverItem);
		serverItem->setData(0, Qt::UserRole, QVariant::fromValue<void*>(server.ptr()));

		NetworkServer::ConnectionMap connections = server->GetConnections();
		for(NetworkServer::ConnectionMap::iterator iter = connections.begin(); iter != connections.end(); ++iter)
		{
			QTreeWidgetItem *connectionItem = FindItem(items, (void*)iter->second.ptr());
			if (!connectionItem)
			{
				connectionItem = new MessageConnectionTreeItem(serverItem, iter->second);
				serverItem->addChild(connectionItem);
				connectionItem->setData(0, Qt::UserRole, QVariant::fromValue<void*>((void*)iter->second.ptr()));
			}
			else
				items.removeOne(connectionItem);
			serverItem->setExpanded(true);
		}
	}
	else
		setWindowTitle("kNet Client");

	std::set<MessageConnection*> connections = network->Connections();
	for(std::set<MessageConnection*>::iterator iter = connections.begin(); iter != connections.end(); ++iter)
		if ((*iter)->GetSocket() && (*iter)->GetSocket()->Type() == ClientSocket)
		{
			QTreeWidgetItem *existingItem = FindItem(items, (void*)*iter);
			if (existingItem && dynamic_cast<MessageConnectionTreeItem*>(existingItem))
			{
				dynamic_cast<MessageConnectionTreeItem*>(existingItem)->UpdateText();
				items.removeOne(existingItem);
			}
			else
			{
				MessageConnectionTreeItem* item = new MessageConnectionTreeItem(connectionsTree->invisibleRootItem(), *iter);
				item->setData(0, Qt::UserRole, QVariant::fromValue<void*>((void*)*iter));
			}
		}

	PopulateStatsTree();

	// Clear all old items from the connection list.
	while(items.size() > 0)
	{
		delete items.back();
		items.pop_back();
	}

	QTimer::singleShot(dialogUpdateInterval, this, SLOT(Update()));
}

QTreeWidgetItem *FindChild(QTreeWidgetItem *parent, int column, QString text)
{
	for(int i = 0; i < parent->childCount(); ++i)
	{
		QTreeWidgetItem *child = parent->child(i);
		if (child->text(column) == text)
			return child;
	}
	return 0;
}

void PopulateStatsTreeNode(QTreeWidgetItem *parent, StatsEventHierarchyNode &statsNode, int timeMSecs, std::string parentNodeName)
{
	for(StatsEventHierarchyNode::NodeMap::iterator iter = statsNode.children.begin(); iter != statsNode.children.end();
		++iter)
	{
		QTreeWidgetItem *child = FindChild(parent, 0, iter->first.c_str());
		std::string childNodeName = parentNodeName.empty() ? iter->first : (parentNodeName + "." + iter->first);
		if (!child)
		{
			child = new StatsEventTreeItem(parent, childNodeName.c_str());
			child->setText(0, iter->first.c_str());
		}
		StatsEventHierarchyNode &node = iter->second;
		bool hasChildren = node.children.size() > 0;

		int totalCountThisLevel = hasChildren ? node.AccumulateTotalCountThisLevel() : 0;
		int totalCountHierarchy = node.AccumulateTotalCountHierarchy();
		float totalValueThisLevel = hasChildren ? node.AccumulateTotalValueThisLevel() : 0.f;
		float totalValueHierarchy = node.AccumulateTotalValueHierarchy();
		float timeSpan = timeMSecs / 1000.f;

		QString totalCountHierarchyStr = (totalCountHierarchy == 0) ? "-" : QString::number(totalCountHierarchy);
		QString totalValueHierarchyStr = (totalCountHierarchy == 0) ? "-" : 
			(node.valueType == "bytes" ? FormatBytes(totalValueHierarchy).c_str() : QString::number(totalValueHierarchy));

		QString totalCountHierarchyPerTimeStr = (totalCountHierarchy == 0) ? "-" : 
			(QString::number(totalCountHierarchy / timeSpan, 'f', 2) + "/sec");
		QString totalValueHierarchyPerTimeStr = (totalCountHierarchy == 0) ? "-" : 
			(node.valueType == "bytes" ? (FormatBytes((double)totalValueHierarchy / timeSpan).c_str() + QString("/sec")) : (QString::number(totalValueHierarchy / timeSpan, 'f', 2) + "/sec"));

		QString totalValueHierarchyPerCountStr = (totalCountHierarchy == 0) ? "-" : 
			(node.valueType == "bytes" ? FormatBytes((double)totalValueHierarchy / totalCountHierarchy).c_str() : QString::number((float)totalValueHierarchy / totalCountHierarchy, 'f', 2));

		if (hasChildren && totalCountThisLevel > 0)
		{
			QString totalCountThisLevelStr = (totalCountThisLevel == 0) ? "-" : QString::number(totalCountThisLevel);
			QString totalValueThisLevelStr = (totalCountThisLevel == 0) ? "-" : 
				(node.valueType == "bytes" ? FormatBytes(totalValueThisLevel).c_str() : QString::number(totalValueThisLevel));

			QString totalCountThisLevelPerTimeStr = (totalCountThisLevel == 0) ? "-" : 
				(QString::number(totalCountThisLevel / timeSpan, 'f', 2) + "/sec");
			QString totalValueThisLevelPerTimeStr = (totalCountThisLevel == 0) ? "-" : 
				(node.valueType == "bytes" ? (FormatBytes((double)totalValueThisLevel / timeSpan).c_str() + QString("/sec")) : (QString::number(totalValueThisLevel / timeSpan, 'f', 2) + "/sec"));

			QString totalValueThisLevelPerCountStr = (totalCountThisLevel == 0) ? "-" : 
				(node.valueType == "bytes" ? FormatBytes((double)totalValueThisLevel / totalCountThisLevel).c_str() : QString::number((float)totalValueThisLevel / totalCountThisLevel, 'f', 2));

			child->setText(1, QString("%1 (%2)").arg(totalCountHierarchyStr).arg(totalCountThisLevelStr));
			child->setText(2, QString("%1 (%2)").arg(totalValueHierarchyStr).arg(totalValueThisLevelStr));
			child->setText(3, QString("%1 (%2)").arg(totalCountHierarchyPerTimeStr).arg(totalCountThisLevelPerTimeStr));
			child->setText(4, QString("%1 (%2)").arg(totalValueHierarchyPerTimeStr).arg(totalValueThisLevelPerTimeStr));
			child->setText(5, QString("%1 (%2)").arg(totalValueHierarchyPerCountStr).arg(totalValueThisLevelPerCountStr));
		}
		else
		{
			child->setText(1, QString("%1").arg(totalCountHierarchyStr));
			child->setText(2, QString("%1").arg(totalValueHierarchyStr));
			child->setText(3, QString("%1").arg(totalCountHierarchyPerTimeStr));
			child->setText(4, QString("%1").arg(totalValueHierarchyPerTimeStr));
			child->setText(5, QString("%1").arg(totalValueHierarchyPerCountStr));
		}
		if (totalCountThisLevel == 0 && hasChildren)
			child->setText(6, "-");
		else if (node.valueType == "bytes")
			child->setText(6, FormatBytes(node.LatestValue()).c_str());
		else
			child->setText(6, QString("%1").arg(node.LatestValue()));

		PopulateStatsTreeNode(child, node, timeMSecs, childNodeName);
	}
}

void NetworkDialog::PopulateStatsTree()
{
	// Make a deep copy of all profiling data so that we don't stall the network worker threads with a lock.
	StatsEventHierarchyNode statistics;

	int timeMSecs = 60 * 1000;
	if (dialog->comboTimePeriod->currentIndex() == 0) timeMSecs = 5 * 1000;
	else if (dialog->comboTimePeriod->currentIndex() == 1) timeMSecs = 15 * 1000;
	else if (dialog->comboTimePeriod->currentIndex() == 2) timeMSecs = 30 * 1000;

	{
		Lock<StatsEventHierarchyNode> stats = network->Statistics();
		stats->PruneOldEventsHierarchy(timeMSecs);
		statistics = *stats;
	}

	PopulateStatsTreeNode(dialog->treeStats->invisibleRootItem(), statistics, timeMSecs, "");
	for(int i = 0; i < 7; ++i)
		dialog->treeStats->resizeColumnToContents(i);

	for(GraphMap::iterator iter = graphs.begin(); iter != graphs.end();)
	{
		StatsEventHierarchyNode *node = statistics.FindChild(iter->first.c_str());
		if (node && iter->second)
		{
			iter->second->Update(*node, timeMSecs);
			++iter;
		}
		else
		{
			iter = graphs.erase(iter);
		}
	}
}

void NetworkDialog::ItemDoubleClicked(QTreeWidgetItem *item)
{
	MessageConnectionTreeItem *msgItem = dynamic_cast<MessageConnectionTreeItem*>(item);
	if (!msgItem)
		return;

	MessageConnectionDialog *dialog = new MessageConnectionDialog(0, msgItem->connection);
	dialog->show();
	dialog->setAttribute(Qt::WA_DeleteOnClose);
}

void NetworkDialog::EventItemDoubleClicked(QTreeWidgetItem *item)
{
	StatsEventTreeItem *msgItem = dynamic_cast<StatsEventTreeItem*>(item);
	if (!msgItem)
		return;

	GraphMap::iterator iter = graphs.find(msgItem->eventName);
	if (iter != graphs.end() && iter->second)
	{
		iter->second->activateWindow();
		return;
	}

	QPointer<GraphDialog> graphDialog = new GraphDialog(0, msgItem->eventName.c_str());
	graphDialog->show();
	graphDialog->setAttribute(Qt::WA_DeleteOnClose);
	graphs[msgItem->eventName] = graphDialog;
}

} // ~kNet
