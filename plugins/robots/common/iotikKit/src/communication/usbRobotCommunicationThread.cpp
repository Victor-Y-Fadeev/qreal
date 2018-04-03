/* Copyright 2017 QReal Research Group
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

#include "iotikKit/communication/usbRobotCommunicationThread.h"

#include <QtCore/QMetaType>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QtCore/QFile>

#include <qrkernel/settingsManager.h>
#include <plugins/robots/thirdparty/qextserialport/src/qextserialport.h>

using namespace iotik::communication;

UsbRobotCommunicationThread::UsbRobotCommunicationThread()
	: mPort(nullptr)
{
}

UsbRobotCommunicationThread::~UsbRobotCommunicationThread()
{
	disconnect();
}

bool UsbRobotCommunicationThread::send(const QByteArray &buffer) const
{
	return mPort->write(buffer) > 0;
}

bool UsbRobotCommunicationThread::send(QObject *addressee, const QByteArray &buffer, int responseSize)
{
	return send(buffer);
}

bool UsbRobotCommunicationThread::send(const QByteArray &buffer, int responseSize, QByteArray &outputBuffer)
{
	return send(buffer);
}

bool UsbRobotCommunicationThread::connect()
{
	if (mPort) {
		disconnect();
		QThread::msleep(500);  // Give port some time to close
	}

	const QString portName = qReal::SettingsManager::value("IotikPortName").toString();
	mPort = new QextSerialPort(portName);
	mPort->setBaudRate(BAUD115200);
	mPort->setFlowControl(FLOW_OFF);
	mPort->setParity(PAR_NONE);
	mPort->setDataBits(DATA_8);
	mPort->setStopBits(STOP_1);
	mPort->setTimeout(0);

	mPort->open(QIODevice::ReadWrite | QIODevice::Unbuffered);
	emit connected(true, "Error!");

	return true;
}

void UsbRobotCommunicationThread::reconnect()
{
	connect();
}

void UsbRobotCommunicationThread::disconnect()
{
	if (mPort) {
		mPort->close();
		delete mPort;
		mPort = nullptr;
	}

	emit disconnected();
}

void UsbRobotCommunicationThread::allowLongJobs(bool allow)
{
	Q_UNUSED(allow)
}

void UsbRobotCommunicationThread::sendCommand(const QString command)
{
	mPort->write(QByteArray::fromStdString(command.toStdString()));
	QThread::msleep(500);
}

bool UsbRobotCommunicationThread::response()
{
	char answer[256] = {'\0'};

	mPort->read(answer, 255);

	return (strlen(answer) >= 3) && (answer[strlen(answer) - 3] == '0');
}

void UsbRobotCommunicationThread::sendFile(const QString filename)
{
	QFile sfile(filename);
	sfile.open(QIODevice::ReadOnly);

	int size = sfile.size();
	int block = 32;

	QString command = "filereceive /fat/" + sfile.fileName() + " " + QString::number(size) + "\n";
	sendCommand(command);

	/*if (!response()) {
		block = size;
	}*/

	while (size > 0) {
			QByteArray data = sfile.read(size > block ? block : size);
			send(data);
			QThread::msleep(25);
			size -= block;
	}

	sfile.close();
}

void UsbRobotCommunicationThread::checkForConnection()
{
	if (!mPort || !mPort->isOpen()) {
		return;
	}

	emit disconnected();
}
