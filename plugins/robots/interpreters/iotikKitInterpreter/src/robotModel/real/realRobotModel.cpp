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

#include "realRobotModel.h"

#include <qrkernel/settingsManager.h>

using namespace iotik::robotModel::real;
using namespace utils::robotCommunication;
using namespace kitBase::robotModel;

RealRobotModel::RealRobotModel(const QString &kitId, const QString &robotId
        , utils::robotCommunication::RobotCommunicationThreadInterface *communicationThread)
    : IotikRobotModelBase(kitId, robotId)
    , mRobotCommunicator(new RobotCommunicator(this))
{
    connect(mRobotCommunicator, &RobotCommunicator::connected, this, &RealRobotModel::connected);
    connect(mRobotCommunicator, &RobotCommunicator::disconnected, this, &RealRobotModel::disconnected);
    connect(mRobotCommunicator, &RobotCommunicator::errorOccured, this, &RealRobotModel::errorOccured);
    connect(mRobotCommunicator, &RobotCommunicator::messageArrived, this, &RealRobotModel::messageArrived);
    mRobotCommunicator->setRobotCommunicationThreadObject(communicationThread);
}

QString RealRobotModel::name() const
{
    return "iotikKit";
}

QString RealRobotModel::friendlyName() const
{
    return tr("IoTik v1.0");
}

bool RealRobotModel::needsConnection() const
{
    return true;
}

int RealRobotModel::priority() const
{
    return 0;
}

void RealRobotModel::connectToRobot()
{
    mRobotCommunicator->connect();
}

void RealRobotModel::disconnectFromRobot()
{
    mRobotCommunicator->disconnect();
}

robotParts::Device *RealRobotModel::createDevice(const PortInfo &port, const DeviceInfo &deviceInfo)
{
    return IotikRobotModelBase::createDevice(port, deviceInfo);
}
