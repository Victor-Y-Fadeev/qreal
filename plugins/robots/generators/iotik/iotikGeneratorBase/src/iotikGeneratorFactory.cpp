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
#include "simpleGenerators/colorSensorToVariableGenerator.h"
#include "simpleGenerators/compassToVariableGenerator.h"
#include "simpleGenerators/lineDetectorToVariableGenerator.h"
#include "simpleGenerators/waitForTouchSensorGenerator.h"
#include "simpleGenerators/waitForInfraredSensorGenerator.h"
#include "simpleGenerators/waitForUltrasonicSensorGenerator.h"
#include "simpleGenerators/waitForFlameSensorGenerator.h"
#include "simpleGenerators/waitForSoundSensorGenerator.h"
#include "simpleGenerators/receiveMessageThreadsGenerator.h"
#include "simpleGenerators/forLoopGenerator.h"

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
	} else if (elementType == "IotikMosfet") {
		return new MosfetGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikLed") {
		return new LedGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikColorSensorToVariable") {
		return new ColorSensorToVariableGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikCompassToVariable") {
		return new CompassToVariableGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikLineDetectorToVariable") {
		return new LineDetectorToVariableGenerator(mRepo, customizer, id, this);

	} else if (elementType == "IotikReceiveMessageThreads") {
		return new ReceiveMessageThreadsGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikWaitForTouchSensor") {
		return new WaitForTouchSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikWaitForIRDistance") {
		return new WaitForInfraredSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikWaitForSonarDistance") {
		return new WaitForUltrasonicSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikWaitForFlame") {
		return new WaitForFlameSensorGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikWaitForSound") {
		return new WaitForSoundSensorGenerator(mRepo, customizer, id, this);
	}

	return GeneratorFactoryBase::simpleGenerator(id, customizer);
}

QStringList IotikGeneratorFactory::pathsToTemplates() const
{
	return mPathsToTemplates; //{":/" + mGeneratorName + "/templates"};
}
