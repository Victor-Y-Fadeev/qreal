/* Copyright 2019 QReal Research Group
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

#include <kitBase/robotModel/robotParts/vectorSensor.h>

namespace iotik {
namespace robotModel {
namespace parts {

class IotikLightSensor : public kitBase::robotModel::robotParts::VectorSensor
{
	Q_OBJECT
	Q_CLASSINFO("name", "iotikLightSensor")
	Q_CLASSINFO("friendlyName", tr("Light Sensor"))

public:
	IotikLightSensor(const kitBase::robotModel::DeviceInfo &info, const kitBase::robotModel::PortInfo &port);

	virtual void init() = 0;
};

}
}
}
