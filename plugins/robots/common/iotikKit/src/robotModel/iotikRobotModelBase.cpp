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

#include "iotikKit/robotModel/parts/iotikInfraredSensor.h"
#include "iotikKit/robotModel/parts/iotikSonarSensor.h"
#include "iotikKit/robotModel/parts/iotikLineSensor.h"

using namespace iotik::robotModel;
using namespace kitBase::robotModel;

IotikRobotModelBase::IotikRobotModelBase(const QString &kitId, const QString &robotId)
	: CommonRobotModel(kitId, robotId)
{
	QList<DeviceInfo> const analogPortConnections = {
		infraredSensorInfo(),
		lineSensorInfo()
	};

	addAllowedConnection(PortInfo("M1", output, { "М1" }), { motorInfo() });
	addAllowedConnection(PortInfo("M2", output, { "М2" }), { motorInfo() });

	addAllowedConnection(PortInfo("A1", input, { "А1" }, "sensorA1"), analogPortConnections);

	addAllowedConnection(PortInfo("D1", input, {}, "sensorD1"), { sonarSensorInfo() });
}

QList<PortInfo> IotikRobotModelBase::configurablePorts() const
{
	QList<PortInfo> const digitalPorts = {
				PortInfo("D1", input, {}, "sensorD1")
	};

	return CommonRobotModel::configurablePorts() + digitalPorts;
}

QList<DeviceInfo> IotikRobotModelBase::convertibleBases() const
{
	return { DeviceInfo::create<parts::IotikInfraredSensor>()
		, DeviceInfo::create<parts::IotikSonarSensor>()
		, DeviceInfo::create<parts::IotikLineSensor>()
	};
}

DeviceInfo IotikRobotModelBase::motorInfo() const
{
	return DeviceInfo::create<iotik::robotModel::parts::IotikMotor>();
}

DeviceInfo IotikRobotModelBase::infraredSensorInfo() const
{
	return DeviceInfo::create<parts::IotikInfraredSensor>();
}

DeviceInfo IotikRobotModelBase::sonarSensorInfo() const
{
	return DeviceInfo::create<parts::IotikSonarSensor>();
}

DeviceInfo IotikRobotModelBase::lineSensorInfo() const
{
	return DeviceInfo::create<parts::IotikLineSensor>();
}
