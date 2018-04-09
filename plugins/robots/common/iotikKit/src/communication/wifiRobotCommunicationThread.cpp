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
	: mSocet(nullptr)
{
}

WifiRobotCommunicationThread::~WifiRobotCommunicationThread()
{
	disconnect();
}

bool WifiRobotCommunicationThread::send(const QByteArray &buffer) const
{
	return mSocet->write(buffer) > 0;
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
	if (mSocet) {
		disconnect();
		QThread::msleep(500);  // Give port some time to close
	}

	const QString hostName = qReal::SettingsManager::value("IotikTcpServer").toString();
	mSocet = new QTcpSocket();

	mSocet->connectToHost(hostName, 3000);
	mSocet->waitForConnected();
	emit connected(true, "Error!");

	return true;
}

void WifiRobotCommunicationThread::reconnect()
{
	connect();
}

void WifiRobotCommunicationThread::disconnect()
{
	if (mSocet) {
		mSocet->close();
		mSocet->waitForDisconnected();
		delete mSocet;
		mSocet = nullptr;
	}

	emit disconnected();
}

void WifiRobotCommunicationThread::allowLongJobs(bool allow)
{
	Q_UNUSED(allow)
}

void WifiRobotCommunicationThread::sendCommand(const QString command)
{
	mSocet->write(QByteArray::fromStdString(command.toStdString()));
	mSocet->waitForBytesWritten();
}

void WifiRobotCommunicationThread::sendFile(const QString filename)
{
	QFile sfile(filename);
	sfile.open(QIODevice::ReadOnly);

	int size = sfile.size();

	QString command = "filereceive /fat/" + sfile.fileName() + " " + QString::number(size) + "\n";
	sendCommand(command);

	QByteArray data = sfile.readAll();
	send(data);
	mSocet->waitForBytesWritten();

	sfile.close();
}

void WifiRobotCommunicationThread::checkForConnection()
{
	if (!mSocet || !mSocet->isOpen()) {
		return;
	}

	emit disconnected();
}
