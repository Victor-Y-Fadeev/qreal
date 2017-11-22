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

#include "waitForFlameSensorBlock.h"

#include "kitBase/robotModel/robotParts/rangeSensor.h"

using namespace iotik;
using namespace blocks::details;
using namespace kitBase::robotModel;

WaitForFlameSensorBlock::WaitForFlameSensorBlock(kitBase::robotModel::RobotModelInterface &robotModel
		, const kitBase::robotModel::DeviceInfo &device)
	: WaitForSensorBlock(robotModel)
	, mDevice(device)
{
}

void WaitForFlameSensorBlock::responseSlot(int reading)
{
	const int targetValue = eval<int>("Value");
	if (!errorsOccured()) {
		processResponce(reading, targetValue);
	}
}

kitBase::robotModel::DeviceInfo WaitForFlameSensorBlock::device() const
{
	return mDevice;
}
