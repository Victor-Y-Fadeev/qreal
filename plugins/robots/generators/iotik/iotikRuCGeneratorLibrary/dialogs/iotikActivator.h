/* Copyright 2018 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#pragma once

#include <QDialog>

#include <kitBase/kitPluginInterface.h>
#include <iotikKit/communication/usbRobotCommunicationThread.h>

namespace Ui {
class IotikActivator;
}

using namespace qReal;
namespace iotik {

class IotikActivator : public QDialog
{
	Q_OBJECT

public:
	explicit IotikActivator(ErrorReporterInterface *errorReporter, QWidget *parent = 0);
	~IotikActivator();

private slots:
	void on_activateButton_clicked();

private:
	ErrorReporterInterface *mErrorReporter;
	communication::UsbRobotCommunicationThread *mUsbCommunicator;
	Ui::IotikActivator *mUi;

	QString keyLine();
};

}
