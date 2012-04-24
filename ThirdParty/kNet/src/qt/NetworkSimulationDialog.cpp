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

/** @file MessageConnectionDialog.cpp
	@brief */

#include "kNet/qt/NetworkSimulationDialog.h"
#include "kNet/qt/ui/ui_NetworkSimulationDialog.h"

namespace kNet
{

NetworkSimulationDialog::NetworkSimulationDialog(QWidget *parent, Ptr(MessageConnection) connection_)
:connection(connection_), QWidget(parent)
{
	dialog = new Ui_NetworkSimulationDialog;
	dialog->setupUi(this);

	NetworkSimulator &s = connection->NetworkSendSimulator();

	dialog->labelConnectionName->setText(connection->ToString().c_str());
	dialog->checkBoxPacketDelayEnabled->setChecked(s.enabled && (s.constantPacketSendDelay > 0 || s.uniformRandomPacketSendDelay > 0));
	dialog->checkBoxPacketLossEnabled->setChecked(s.enabled && s.packetLossRate > 0);
	dialog->spinBoxConstantDelay->setValue(s.constantPacketSendDelay);
	dialog->spinBoxRandomDelay->setValue(s.uniformRandomPacketSendDelay);
	dialog->spinBoxUniformLoss->setValue(s.packetLossRate * 100.f);

	connect(dialog->checkBoxPacketDelayEnabled, SIGNAL(toggled(bool)), this, SLOT(ParameterChanged()));
	connect(dialog->checkBoxPacketLossEnabled, SIGNAL(toggled(bool)), this, SLOT(ParameterChanged()));
	connect(dialog->checkBoxPacketDuplicationEnabled, SIGNAL(toggled(bool)), this, SLOT(ParameterChanged()));
	connect(dialog->checkBoxPacketCorruptionEnabled, SIGNAL(toggled(bool)), this, SLOT(ParameterChanged()));
	connect(dialog->checkBoxCorruptPayload, SIGNAL(toggled(bool)), this, SLOT(ParameterChanged()));
	connect(dialog->checkBoxBurstsEnabled, SIGNAL(toggled(bool)), this, SLOT(ParameterChanged()));
	connect(dialog->spinBoxConstantDelay, SIGNAL(valueChanged(int)), this, SLOT(ParameterChanged()));
	connect(dialog->spinBoxRandomDelay, SIGNAL(valueChanged(int)), this, SLOT(ParameterChanged()));
	connect(dialog->spinBoxNormalMean, SIGNAL(valueChanged(int)), this, SLOT(ParameterChanged()));
	connect(dialog->doubleSpinBoxNormalVar, SIGNAL(valueChanged(double)), this, SLOT(ParameterChanged()));
	connect(dialog->spinBoxUniformLoss, SIGNAL(valueChanged(int)), this, SLOT(ParameterChanged()));
	connect(dialog->spinBoxUniformDuplication, SIGNAL(valueChanged(int)), this, SLOT(ParameterChanged()));
	connect(dialog->spinBoxToggleBitsPr, SIGNAL(valueChanged(int)), this, SLOT(ParameterChanged()));
	connect(dialog->spinBoxBitsMin, SIGNAL(valueChanged(int)), this, SLOT(ParameterChanged()));
	connect(dialog->spinBoxBitsMax, SIGNAL(valueChanged(int)), this, SLOT(ParameterChanged()));
	connect(dialog->spinBoxBurstInterval, SIGNAL(valueChanged(int)), this, SLOT(ParameterChanged()));
	connect(dialog->spinBoxBurstLength, SIGNAL(valueChanged(int)), this, SLOT(ParameterChanged()));
}

NetworkSimulationDialog::~NetworkSimulationDialog()
{
	delete dialog;
}

void NetworkSimulationDialog::ParameterChanged()
{
	if (!connection)
		return;
	
	NetworkSimulator &s = connection->NetworkSendSimulator();
	s.enabled = dialog->checkBoxPacketDelayEnabled->isChecked() || dialog->checkBoxPacketLossEnabled->isChecked()
		|| dialog->checkBoxPacketCorruptionEnabled->isChecked() || dialog->checkBoxPacketDuplicationEnabled->isChecked();

	if (dialog->checkBoxPacketDelayEnabled->isChecked())
	{
		s.constantPacketSendDelay = dialog->spinBoxConstantDelay->value();
		s.uniformRandomPacketSendDelay = dialog->spinBoxRandomDelay->value();
	}
	else
	{
		s.constantPacketSendDelay = 0;
		s.uniformRandomPacketSendDelay = 0;
	}

	if (dialog->checkBoxPacketLossEnabled->isChecked())
		s.packetLossRate = dialog->spinBoxUniformLoss->value() / 100.f;
	else
		s.packetLossRate = 0;
}


} // ~kNet
