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

#include "robotModel.h"

#include <qrkernel/settingsManager.h>

using namespace iotik::robotModel;
using namespace kitBase::robotModel;

RobotModel::RobotModel(const QString &kitId, const QString &robotId)
	: IotikRobotModelBase(kitId, robotId)
{
}

QString RobotModel::name() const
{
	return "IotikRobotModel";
}

QString RobotModel::friendlyName() const
{
	return tr("IoTik v1.0");
}

bool RobotModel::needsConnection() const
{
	return true;
}

int RobotModel::priority() const
{
	return 0;
}

robotParts::Device *RobotModel::createDevice(const PortInfo &port, const DeviceInfo &deviceInfo)
{
	return IotikRobotModelBase::createDevice(port, deviceInfo);
}
