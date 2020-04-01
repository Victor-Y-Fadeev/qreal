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

#include "iotikKit/communication/wifiRobotCommunicationThread.h"

#include <QtCore/QMetaType>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QtCore/QFile>

#include <QTcpSocket>

#include <qrkernel/settingsManager.h>

using namespace iotik::communication;

WifiRobotCommunicationThread::WifiRobotCommunicationThread()
	: isConnected(false)
{
	mSocket = new QTcpSocket(this);

	QObject::connect(mSocket, SIGNAL(connected()), this, SLOT(onConnected()));
	QObject::connect(mSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

WifiRobotCommunicationThread::~WifiRobotCommunicationThread()
{
	disconnect();
	delete mSocket;
}

bool WifiRobotCommunicationThread::send(const QByteArray &buffer) const
{
	if (!isConnected) {
		return false;
	}

	if (mSocket->write(buffer) == -1) {
		return false;
	}

	return mSocket->waitForBytesWritten(waitBytes);
}

bool WifiRobotCommunicationThread::send(QObject *addressee, const QByteArray &buffer, int responseSize)
{
	return send(buffer);
}

bool WifiRobotCommunicationThread::send(const QByteArray &buffer, int responseSize, QByteArray &outputBuffer)
{
	return send(buffer);
}

bool WifiRobotCommunicationThread::connect()
{
	if (isConnected) {
		disconnect();
	}

	const QString hostName = qReal::SettingsManager::value("IotikTcpServer").toString();
	mSocket->connectToHost(hostName, 3000);

	return mSocket->waitForConnected(waitConnected);
}

void WifiRobotCommunicationThread::reconnect()
{
	connect();
}

void WifiRobotCommunicationThread::disconnect()
{
	if (isConnected) {
		mSocket->close();
		mSocket->waitForDisconnected(waitDisconnected);  // Give port some time to close
	}
}

void WifiRobotCommunicationThread::allowLongJobs(bool allow)
{
	Q_UNUSED(allow)
}

bool WifiRobotCommunicationThread::sendCommand(const QString command)
{
	bool result = send(QByteArray::fromStdString(command.toStdString()));
	QThread::msleep(50);

	return result;
}

bool WifiRobotCommunicationThread::sendFile(const QString filename)
{
	QFile sfile(filename);
	sfile.open(QIODevice::ReadOnly);

	int size = sfile.size();
	int block = 1024;

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

			QThread::msleep(25);
			size -= block;
	}

	sfile.close();
	return true;
}

void WifiRobotCommunicationThread::onConnected()
{
	isConnected = true;
}

void WifiRobotCommunicationThread::onDisconnected()
{
	isConnected = false;
}
