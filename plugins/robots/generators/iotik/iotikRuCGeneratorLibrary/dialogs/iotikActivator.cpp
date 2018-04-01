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

#include "iotikActivator.h"
#include "ui_iotikActivator.h"

#include <iotikKit/communication/usbRobotCommunicationThread.h>

using namespace qReal::gui;
using namespace iotik::communication;
using namespace iotik;

IotikActivator::IotikActivator(
		qReal::ErrorReporterInterface *errorReporter
		, QWidget *parent)
	: QDialog(parent)
	, mErrorReporter(errorReporter)
	, mUsbCommunicator(new UsbRobotCommunicationThread())
	, mUi(new Ui::IotikActivator)
{
	mUi->setupUi(this);
}

IotikActivator::~IotikActivator()
{
	delete mUi;
}

QString IotikActivator::keyLine()
{
	return mUi->keyLine->text();
}

void IotikActivator::on_activateButton_clicked()
{
	mUsbCommunicator->connect();
	mUsbCommunicator->sendCommand("auth " + keyLine());
	mUsbCommunicator->disconnect();
	this->close();
}
