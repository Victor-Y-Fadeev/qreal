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

#include "iotikKit/blocks/iotikBlocksFactory.h"
#include "iotikKit/robotModel/parts/iotikMosfet.h"
#include "iotikKit/robotModel/parts/iotikLed.h"
#include "iotikKit/robotModel/parts/iotikColorSensor.h"
#include "iotikKit/robotModel/parts/iotikAccelerometer.h"
#include "iotikKit/robotModel/parts/iotikCompass.h"
#include "iotikKit/robotModel/parts/iotikGyroscope.h"
#include "iotikKit/robotModel/parts/iotikLineSensor.h"
#include "iotikKit/robotModel/parts/iotikSoilSensor.h"
#include "iotikKit/robotModel/parts/iotikWaterSensor.h"
#include "iotikKit/robotModel/parts/iotikFlowSensor.h"
#include "iotikKit/robotModel/parts/iotikInfraredSensor.h"
#include "iotikKit/robotModel/parts/iotikTemperatureSensor.h"
#include "iotikKit/robotModel/parts/iotikSonarSensor.h"
#include "iotikKit/robotModel/parts/iotikLaserSensor.h"
#include "iotikKit/robotModel/parts/iotikFlameSensor.h"

#include "iotikKit/robotModel/parts/iotikWifi.h"
#include "iotikKit/robotModel/parts/iotikBlynkAuthorization.h"
#include "iotikKit/robotModel/parts/iotikBlynkLCD.h"
#include "iotikKit/robotModel/parts/iotikBlynkLed.h"
#include "iotikKit/robotModel/parts/iotikBlynkNotification.h"
#include "iotikKit/robotModel/parts/iotikBlynkProperty.h"
#include "iotikKit/robotModel/parts/iotikBlynkReceive.h"
#include "iotikKit/robotModel/parts/iotikBlynkSend.h"
#include "iotikKit/robotModel/parts/iotikBlynkTerminal.h"

#include <kitBase/robotModel/robotParts/rangeSensor.h>
#include <kitBase/blocksBase/common/enginesStopBlock.h>
#include <kitBase/blocksBase/common/waitForTouchSensorBlock.h>
#include <kitBase/blocksBase/common/waitForSonarDistanceBlock.h>
#include <kitBase/blocksBase/common/waitForSoundSensorBlock.h>

#include <qrutils/interpreter/blocks/emptyBlock.h>

#include "details/iotikEnginesBackwardBlock.h"
#include "details/iotikEnginesForwardBlock.h"
#include "details/mosfetBlock.h"
#include "details/ledBlock.h"
#include "details/soilSensorToVariable.h"
#include "details/waterSensorToVariable.h"
#include "details/flowSensorToVariable.h"
#include "details/waitForTemperatureSensorBlock.h"
#include "details/colorSensor.h"
#include "details/accelerometer.h"
#include "details/compass.h"
#include "details/gyroscope.h"
#include "details/lineDetector.h"
#include "details/flameSensorBlock.h"
#include "details/soundSensorBlock.h"
#include "details/laserDistanceBlock.h"

#include "details/wifi.h"
#include "details/blynkAuthorization.h"
#include "details/blynkLCD.h"
#include "details/blynkLed.h"
#include "details/blynkNotification.h"
#include "details/blynkProperty.h"
#include "details/blynkReceive.h"
#include "details/blynkSend.h"
#include "details/blynkTerminal.h"

using namespace iotik::blocks;
using namespace iotik::blocks::details;
using namespace kitBase::blocksBase::common;

qReal::interpretation::Block *IotikBlocksFactory::produceBlock(const qReal::Id &element)
{
	if (elementMetatypeIs(element, "IotikEnginesForward")) {
		return new details::IotikEnginesForwardBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikEnginesBackward")) {
		return new details::IotikEnginesBackwardBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikEnginesStop")) {
		return new EnginesStopBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikAngularServo")) {
		// AngularServo and EnginesForward are synonyms since angular and radial servos are controlled the same way.
		return new details::IotikEnginesForwardBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikLed")) {
		return new LedBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikMosfet")) {
		return new MosfetBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikSoilSensorToVariable")) {
		return new SoilSensorToVariableBlock();
	} else if (elementMetatypeIs(element, "IotikWaterSensorToVariable")) {
		return new WaterSensorToVariableBlock();
	} else if (elementMetatypeIs(element, "IotikFlowSensorToVariable")) {
		return new FlowSensorToVariableBlock();

	} else if (elementMetatypeIs(element, "IotikWaitForTouchSensor")) {
		return new WaitForTouchSensorBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikWaitForIRDistance")) {
		return new WaitForSonarDistanceBlock(mRobotModelManager->model()
				, kitBase::robotModel::DeviceInfo::create<robotModel::parts::IotikInfraredSensor>());
	} else if (elementMetatypeIs(element, "IotikWaitForSonarDistance")) {
		return new WaitForSonarDistanceBlock(mRobotModelManager->model()
				, kitBase::robotModel::DeviceInfo::create<robotModel::parts::IotikSonarSensor>());
	} else if (elementMetatypeIs(element, "IotikWaitForTemperature")) {
		return new WaitForTemperatureSensorBlock(mRobotModelManager->model()
				, kitBase::robotModel::DeviceInfo::create<robotModel::parts::IotikTemperatureSensor>());

	} else if (elementMetatypeIs(element, "IotikAccelerometer")) {
		return new AccelerometerBlock();
	} else if (elementMetatypeIs(element, "IotikCompass")) {
		return new CompassBlock();
	} else if (elementMetatypeIs(element, "IotikGyroscope")) {
		return new GyroscopeBlock();
	} else if (elementMetatypeIs(element, "IotikColorSensor")) {
		return new ColorSensorBlock();
	} else if (elementMetatypeIs(element, "IotikLineDetector")) {
		return new LineDetectorBlock();
	} else if (elementMetatypeIs(element, "IotikLaserDistance")) {
		return new LaserDistanceBlock();
	} else if (elementMetatypeIs(element, "IotikFlame")) {
		return new FlameSensorBlock();
	} else if (elementMetatypeIs(element, "IotikSound")) {
		return new SoundSensorBlock();

	} else if (elementMetatypeIs(element, "IotikWifi")) {
		return new WifiBlock();
	} else if (elementMetatypeIs(element, "IotikBlynkAuthorization")) {
		return new BlynkAuthorizationBlock();
	} else if (elementMetatypeIs(element, "IotikBlynkLed")) {
		return new BlynkLedBlock();
	} else if (elementMetatypeIs(element, "IotikBlynkSend")) {
		return new BlynkSendBlock();
	} else if (elementMetatypeIs(element, "IotikBlynkReceive")) {
		return new BlynkReceiveBlock();
	} else if (elementMetatypeIs(element, "IotikBlynkNotification")) {
		return new BlynkNotificationBlock();
	} else if (elementMetatypeIs(element, "IotikBlynkProperty")) {
		return new BlynkPropertyBlock();
	} else if (elementMetatypeIs(element, "IotikBlynkLCD")) {
		return new BlynkLCDBlock();
	} else if (elementMetatypeIs(element, "IotikBlynkTerminal")) {
		return new BlynkTerminalBlock();
	}

	return nullptr;
}

qReal::IdList IotikBlocksFactory::providedBlocks() const
{
	return {
				id("IotikEnginesBackward")
				, id("IotikEnginesForward")
				, id("IotikEnginesStop")
				, id("IotikAngularServo")
				, id("IotikLed")
				, id("IotikMosfet")
				, id("IotikSoilSensorToVariable")
				, id("IotikWaterSensorToVariable")
				, id("IotikFlowSensorToVariable")

				, id("IotikWaitForTouchSensor")
				, id("IotikWaitForIRDistance")
				, id("IotikWaitForSonarDistance")
				, id("IotikWaitForTemperature")

				, id("IotikAccelerometer")
				, id("IotikCompass")
				, id("IotikGyroscope")
				, id("IotikColorSensor")
				, id("IotikLineDetector")
				, id("IotikLaserDistance")
				, id("IotikFlame")
				, id("IotikSound")

				, id("IotikWifi")
				, id("IotikBlynkAuthorization")
				, id("IotikBlynkLed")
				, id("IotikBlynkSend")
				, id("IotikBlynkReceive")
				, id("IotikBlynkNotification")
				, id("IotikBlynkProperty")
				, id("IotikBlynkLCD")
				, id("IotikBlynkTerminal")
	};
}

qReal::IdList IotikBlocksFactory::blocksToDisable() const
{
	return {
				id("PrintText")
				, id("ClearScreen")
				, id("MarkerDown")
				, id("MarkerUp")
	};
}

qReal::IdList IotikBlocksFactory::blocksToHide() const
{
	return {
				id("PrintText")
				, id("ClearScreen")
				, id("MarkerDown")
				, id("MarkerUp")
	};
}
