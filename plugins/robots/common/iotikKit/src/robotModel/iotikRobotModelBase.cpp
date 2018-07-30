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

#include "iotikKit/robotModel/iotikRobotModelBase.h"
#include <kitBase/robotModel/robotParts/rangeSensor.h>

#include "iotikKit/robotModel/parts/iotikMotor.h"

using namespace iotik::robotModel;
using namespace kitBase::robotModel;

IotikRobotModelBase::IotikRobotModelBase(const QString &kitId, const QString &robotId)
	: CommonRobotModel(kitId, robotId)
{
	addAllowedConnection(PortInfo("MA", output, { "МA" }), { motorInfo() });
	addAllowedConnection(PortInfo("MB", output, { "МB" }), { motorInfo() });
}

QList<PortInfo> IotikRobotModelBase::configurablePorts() const
{
	return CommonRobotModel::configurablePorts();
}

QList<DeviceInfo> IotikRobotModelBase::convertibleBases() const
{
	return {};
}

DeviceInfo IotikRobotModelBase::motorInfo() const
{
	return DeviceInfo::create<iotik::robotModel::parts::IotikMotor>();
}
