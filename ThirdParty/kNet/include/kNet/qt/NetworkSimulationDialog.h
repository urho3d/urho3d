/* Copyright The kNet Project.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
#pragma once

/** @file NetworkSimulationDialog.h
	@brief Shows a UI for specifying parameters for network simulations. */

#include "kNetBuildConfig.h"

#ifdef KNET_USE_QT

#include <QObject>
#include <QWidget>
#include <QTimer>

#include "kNet/MessageConnection.h"
#include "kNet/SharedPtr.h"

class Ui_NetworkSimulationDialog;

namespace kNet
{

class NetworkSimulationDialog : public QWidget
{
	Q_OBJECT;

	Ptr(MessageConnection) connection;
	Ui_NetworkSimulationDialog *dialog;

public:
	NetworkSimulationDialog(QWidget *parent, Ptr(MessageConnection) connection);
	~NetworkSimulationDialog();

public slots:
	void ParameterChanged();
};

} // ~kNet

#endif
