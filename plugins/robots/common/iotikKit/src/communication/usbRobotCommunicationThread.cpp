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
	: isConnected(false)
{
	mPort = new QextSerialPort();
}

UsbRobotCommunicationThread::~UsbRobotCommunicationThread()
{
	disconnect();
	delete mPort;
}

bool UsbRobotCommunicationThread::send(const QByteArray &buffer) const
{
	return isConnected && mPort->write(buffer) != -1;
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
	if (isConnected) {
		disconnect();
	}

	const QString portName = qReal::SettingsManager::value("IotikPortName").toString();
	mPort->setPortName(portName);
	mPort->setBaudRate(BAUD115200);
	mPort->setFlowControl(FLOW_OFF);
	mPort->setParity(PAR_NONE);
	mPort->setDataBits(DATA_8);
	mPort->setStopBits(STOP_1);
	mPort->setTimeout(0);

	if (mPort->open(QIODevice::ReadWrite | QIODevice::Unbuffered) && mPort->isOpen())
	{
		isConnected = true;
		return true;
	}

	return false;
}

void UsbRobotCommunicationThread::reconnect()
{
	connect();
}

void UsbRobotCommunicationThread::disconnect()
{
	if (isConnected) {
		mPort->close();
		QThread::msleep(waitDisconnected);  // Give port some time to close

		isConnected = false;
	}
}

void UsbRobotCommunicationThread::allowLongJobs(bool allow)
{
	Q_UNUSED(allow)
}

bool UsbRobotCommunicationThread::sendCommand(const QString command)
{
	bool result = send(QByteArray::fromStdString(command.toStdString()));
	QThread::msleep(writeCommand);

	return result;
}

bool UsbRobotCommunicationThread::sendFile(const QString filename)
{
	QFile sfile(filename);
	sfile.open(QIODevice::ReadOnly);

	long long size = sfile.size();
	int block = blockSize;

	QString command = "filereceive /fat/" + sfile.fileName() + " " + QString::number(size) + "\n";
	if (!sendCommand(command))
	{
		sfile.close();
		return false;
	}

	while (size > 0) {
			QByteArray data = sfile.read(size > block ? block : size);

			if (!send(data))
			{
				sfile.close();
				return false;
			}

			QThread::msleep(writeBlock);
			size -= block;
	}

	sfile.close();
	return true;
}
