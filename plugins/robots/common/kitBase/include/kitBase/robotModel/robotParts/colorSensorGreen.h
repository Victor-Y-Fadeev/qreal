/* Copyright 2007-2015 QReal Research Group
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

#include "colorSensor.h"

#include "kitBase/kitBaseDeclSpec.h"

namespace kitBase {
namespace robotModel {
namespace robotParts {

/// Base class for sensor that returns intensity of green color under it.
class ROBOTS_KIT_BASE_EXPORT ColorSensorGreen : public ColorSensor
{
	Q_OBJECT
	Q_CLASSINFO("name", "colorGreen")
	Q_CLASSINFO("friendlyName", tr("Color sensor (green)"))
	Q_CLASSINFO("simulated", "true")

public:
	/// Constructor, takes device type info and port on which this sensor is configured.
	ColorSensorGreen(const DeviceInfo &info, const PortInfo &port);
};

}
}
}
