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

#include "iotikGeneratorFactory.h"

#include "src/simpleGenerators/receiveMessageThreadsGenerator.h"

#include "simpleGenerators/iotikEnginesGenerator.h"
#include "simpleGenerators/mosfetGenerator.h"
#include "simpleGenerators/ledGenerator.h"
#include "simpleGenerators/soilSensorToVariableGenerator.h"
#include "simpleGenerators/waterSensorToVariableGenerator.h"
#include "simpleGenerators/flowSensorToVariableGenerator.h"
#include "simpleGenerators/waitForTouchSensorGenerator.h"
#include "simpleGenerators/waitForInfraredSensorGenerator.h"
#include "simpleGenerators/waitForTemperatureSensorGenerator.h"
#include "simpleGenerators/waitForUltrasonicSensorGenerator.h"
#include "simpleGenerators/lightSensorGenerator.h"
#include "simpleGenerators/colorSensorGenerator.h"
#include "simpleGenerators/accelerometerGenerator.h"
#include "simpleGenerators/compassGenerator.h"
#include "simpleGenerators/gyroscopeGenerator.h"
#include "simpleGenerators/lineDetectorGenerator.h"
#include "simpleGenerators/laserSensorGenerator.h"
#include "simpleGenerators/flameSensorGenerator.h"
#include "simpleGenerators/soundSensorGenerator.h"
#include "simpleGenerators/heatingSensorGenerator.h"
#include "simpleGenerators/humiditySensorGenerator.h"
#include "simpleGenerators/pressureSensorGenerator.h"
#include "simpleGenerators/ultravioletGenerator.h"
#include "simpleGenerators/capacitiveGenerator.h"

#include "simpleGenerators/rgbGenerator.h"
#include "simpleGenerators/matrixGenerator.h"
#include "simpleGenerators/relayGenerator.h"

#include "simpleGenerators/printStringGenerator.h"
#include "simpleGenerators/clearDisplayGenerator.h"
#include "simpleGenerators/drawPixelGenerator.h"
#include "simpleGenerators/drawLineGenerator.h"
#include "simpleGenerators/drawRectGenerator.h"
#include "simpleGenerators/drawEllipseGenerator.h"
#include "simpleGenerators/drawIconGenerator.h"

#include "simpleGenerators/forLoopGenerator.h"
#include "simpleGenerators/wifiGenerator.h"
#include "simpleGenerators/blynkAuthorizationGenerator.h"
#include "simpleGenerators/blynkLedGenerator.h"
#include "simpleGenerators/blynkSendGenerator.h"
#include "simpleGenerators/blynkReceiveGenerator.h"
#include "simpleGenerators/blynkNotificationGenerator.h"
#include "simpleGenerators/blynkPropertyGenerator.h"
#include "simpleGenerators/blynkLCDGenerator.h"
#include "simpleGenerators/blynkTerminalGenerator.h"

using namespace iotik;
using namespace iotik::simple;
using namespace generatorBase;
using namespace generatorBase::simple;

IotikGeneratorFactory::IotikGeneratorFactory(const qrRepo::RepoApi &repo
		, qReal::ErrorReporterInterface &errorReporter
		, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
		, lua::LuaProcessor &luaProcessor
		, const QStringList &pathsToTemplates)
	: GeneratorFactoryBase(repo, errorReporter, robotModelManager, luaProcessor)
	, mPathsToTemplates(pathsToTemplates)
{
}

IotikGeneratorFactory::~IotikGeneratorFactory()
{
}

AbstractSimpleGenerator *IotikGeneratorFactory::forLoopGenerator(const qReal::Id &id
		, GeneratorCustomizer &customizer)
{
	return new ForLoopGenerator(++mLoopGeneratorIndex, mRepo, customizer, id, this);
}

AbstractSimpleGenerator *IotikGeneratorFactory::simpleGenerator(const qReal::Id &id
		, GeneratorCustomizer &customizer)
{
	QString const elementType = id.element();
	if (elementType.contains("EnginesForward")
			|| elementType.contains("EnginesBackward")
			|| elementType.contains("AngularServo"))
	{
		return new IotikEnginesGenerator(mRepo, customizer, id, elementType, this);
	} else if (elementType == "IotikLed") {
		return new LedGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikMosfet") {
		return new MosfetGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikSoilSensorToVariable") {
		return new SoilSensorToVariableGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikWaterSensorToVariable") {
		return new WaterSensorToVariableGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikFlowSensorToVariable") {
		return new FlowSensorToVariableGenerator(mRepo, customizer, id, this);

	} else if (elementType == "IotikWaitForTouchSensor") {
		return new WaitForTouchSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikWaitForIRDistance") {
		return new WaitForInfraredSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikWaitForSonarDistance") {
		return new WaitForUltrasonicSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikWaitForTemperature") {
		return new WaitForTemperatureSensorGenerator(mRepo, customizer, id, this);

	} else if (elementType == "IotikAccelerometer") {
		return new AccelerometerGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikCompass") {
		return new CompassGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikGyroscope") {
		return new GyroscopeGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikLightSensor") {
		return new LightSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikColorSensor") {
		return new ColorSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikLineDetector") {
		return new LineDetectorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikLaserDistance") {
		return new LaserSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikFlame") {
		return new FlameSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikSound") {
		return new SoundSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikTemperature") {
		return new HeatingSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikHumidity") {
		return new HumiditySensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikPressure") {
		return new PressureSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikUltraviolet") {
		return new UltravioletGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikCapacitive") {
		return new CapacitiveGenerator(mRepo, customizer, id, this);

	} else if (elementType == "IotikRgb") {
		return new RgbGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikMatrix") {
		return new MatrixGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikRelay") {
		return new RelayGenerator(mRepo, customizer, id, this);

	} else if (elementType == "IotikPrintString") {
		return new PrintStringGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikClearDisplay") {
		return new ClearDisplayGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikDrawLine") {
		return new DrawLineGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikDrawPixel") {
		return new DrawPixelGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikDrawRect") {
		return new DrawRectGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikDrawEllipse") {
		return new DrawEllipseGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikDrawIcon") {
		return new DrawIconGenerator(mRepo, customizer, id, this);

	} else if (elementType == "IotikWifi") {
		return new WifiGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikBlynkAuthorization") {
		return new BlynkAuthorizationGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikBlynkLed") {
		return new BlynkLedGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikBlynkSend") {
		return new BlynkSendGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikBlynkReceive") {
		return new BlynkReceiveGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikBlynkNotification") {
		return new BlynkNotificationGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikBlynkProperty") {
		return new BlynkPropertyGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikBlynkLCD") {
		return new BlynkLCDGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikBlynkTerminal") {
		return new BlynkTerminalGenerator(mRepo, customizer, id, this);
	}

	return GeneratorFactoryBase::simpleGenerator(id, customizer);
}

QStringList IotikGeneratorFactory::pathsToTemplates() const
{
	return mPathsToTemplates; //{":/" + mGeneratorName + "/templates"};
}
