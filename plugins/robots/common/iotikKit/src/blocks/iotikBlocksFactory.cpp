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
#include "iotikKit/robotModel/parts/iotikLightSensor.h"
#include "iotikKit/robotModel/parts/iotikHumiditySensor.h"
#include "iotikKit/robotModel/parts/iotikPressureSensor.h"
#include "iotikKit/robotModel/parts/iotikUltravioletSensor.h"
#include "iotikKit/robotModel/parts/iotikCapacitiveSensor.h"
#include "iotikKit/robotModel/parts/iotikRgb.h"
#include "iotikKit/robotModel/parts/iotikMatrix.h"
#include "iotikKit/robotModel/parts/iotikRelay.h"
#include "iotikKit/robotModel/parts/iotikEngines.h"
#include "iotikKit/robotModel/parts/iotikSoilTHSensor.h"

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
#include "details/lightSensor.h"
#include "details/temperature.h"
#include "details/humidity.h"
#include "details/pressure.h"
#include "details/ultraviolet.h"
#include "details/capacitive.h"
#include "details/rgb.h"
#include "details/matrix.h"
#include "details/relay.h"
#include "details/engines.h"
#include "details/soilTHSensor.h"

#include "details/printString.h"
#include "details/clearDisplay.h"
#include "details/drawPixelBlock.h"
#include "details/drawLineBlock.h"
#include "details/drawRectBlock.h"
#include "details/drawEllipseBlock.h"
#include "details/drawIconBlock.h"

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
	} else if (elementMetatypeIs(element, "IotikLightSensor")) {
		return new LightSensorBlock();
	} else if (elementMetatypeIs(element, "IotikColorSensor")) {
		return new ColorSensorBlock();
	} else if (elementMetatypeIs(element, "IotikLineDetector")) {
		return new LineDetectorBlock();
	} else if (elementMetatypeIs(element, "IotikLaserDistance")) {
		return new LaserDistanceBlock();
	} else if (elementMetatypeIs(element, "IotikSound")) {
		return new SoundSensorBlock();
	} else if (elementMetatypeIs(element, "IotikFlame")) {
		return new FlameSensorBlock();
	} else if (elementMetatypeIs(element, "IotikTemperature")) {
		return new TemperatureSensorBlock();
	} else if (elementMetatypeIs(element, "IotikHumidity")) {
		return new HumiditySensorBlock();
	} else if (elementMetatypeIs(element, "IotikPressure")) {
		return new PressureSensorBlock();
	} else if (elementMetatypeIs(element, "IotikUltraviolet")) {
		return new UltravioletSensorBlock();
	} else if (elementMetatypeIs(element, "IotikCapacitive")) {
		return new CapacitiveSensorBlock();
	} else if (elementMetatypeIs(element, "IotikRgb")) {
		return new RgbBlock();
	} else if (elementMetatypeIs(element, "IotikMatrix")) {
		return new MatrixBlock();
	} else if (elementMetatypeIs(element, "IotikRelay")) {
		return new RelayBlock();
	} else if (elementMetatypeIs(element, "IotikEngines")) {
		return new EnginesBlock();
	} else if (elementMetatypeIs(element, "IotikSoilTH")) {
		return new SoilTHSensorBlock();

	} else if (elementMetatypeIs(element, "IotikPrintString")) {
		return new PrintString(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikClearDisplay")) {
		return new ClearDisplay(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikDrawPixel")) {
		return new DrawPixelBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikDrawLine")) {
		return new DrawLineBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikDrawRect")) {
		return new DrawRectBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikDrawEllipse")) {
		return new DrawEllipseBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikDrawIcon")) {
		return new DrawIconBlock(mRobotModelManager->model());

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
				, id("IotikLightSensor")
				, id("IotikColorSensor")
				, id("IotikLineDetector")
				, id("IotikLaserDistance")
				, id("IotikSound")
				, id("IotikFlame")
				, id("IotikTemperature")
				, id("IotikHumidity")
				, id("IotikPressure")
				, id("IotikUltraviolet")
				, id("IotikCapacitive")
				, id("IotikRgb")
				, id("IotikMatrix")
				, id("IotikRelay")
				, id("IotikEngines")
				, id("IotikSoilTH")

				, id("IotikPrintString")
				, id("IotikClearDisplay")
				, id("IotikDrawPixel")
				, id("IotikDrawLine")
				, id("IotikDrawRect")
				, id("IotikDrawEllipse")
				, id("IotikDrawIcon")

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
