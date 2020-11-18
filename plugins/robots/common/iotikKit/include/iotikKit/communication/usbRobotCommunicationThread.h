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

#pragma once

#include <utils/robotCommunication/robotCommunicationThreadInterface.h>

class QextSerialPort;
class QTimer;

namespace iotik {
namespace communication {

class UsbRobotCommunicationThread : public utils::robotCommunication::RobotCommunicationThreadInterface
{
	Q_OBJECT

public:
	UsbRobotCommunicationThread();
	~UsbRobotCommunicationThread();

public slots:
	bool send(const QByteArray &buffer) const;
	bool connect() override;
	void reconnect() override;
	void disconnect() override;

	void allowLongJobs(bool allow = true) override;

	bool sendCommand(const QString command);
	bool sendFile(const QString filename);

private:
	bool send(QObject *addressee, const QByteArray &buffer, int responseSize) override;
	bool send(const QByteArray &buffer, int responseSize, QByteArray &outputBuffer) override;

	QextSerialPort *mPort;
	bool isConnected;

	const unsigned long waitDisconnected = 250;

	const int blockSize = 128;

	const unsigned long writeCommand = 50;
	const unsigned long writeBlock = 50;
};

}
}
