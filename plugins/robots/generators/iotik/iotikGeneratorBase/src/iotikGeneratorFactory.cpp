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

#include <generatorBase/simpleGenerators/waitForButtonGenerator.h>

#include "simpleGenerators/detectorToVariableGenerator.h"
#include "simpleGenerators/waitForMessageGenerator.h"
#include "simpleGenerators/sendMessageGenerator.h"
#include "simpleGenerators/systemGenerator.h"
#include "simpleGenerators/iotikEnginesGenerator.h"
#include "simpleGenerators/waitForInfraredSensorGenerator.h"
#include "simpleGenerators/waitForMotionGenerator.h"
#include "parts/iotikDeviceVariables.h"

using namespace iotik;
using namespace iotik::simple;
using namespace generatorBase::simple;

IotikGeneratorFactory::IotikGeneratorFactory(const qrRepo::RepoApi &repo
		, qReal::ErrorReporterInterface &errorReporter
		, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
		, generatorBase::lua::LuaProcessor &luaProcessor
		, const QString &generatorName)
	: GeneratorFactoryBase(repo, errorReporter, robotModelManager, luaProcessor)
	, mGeneratorName(generatorName)
{
}

IotikGeneratorFactory::~IotikGeneratorFactory()
{
}

generatorBase::simple::AbstractSimpleGenerator *IotikGeneratorFactory::simpleGenerator(const qReal::Id &id
		, generatorBase::GeneratorCustomizer &customizer)
{
	QString const elementType = id.element();
	if (elementType.contains("EnginesForward")
			|| elementType.contains("EnginesBackward")
			|| elementType.contains("AngularServo"))
	{
		return new IotikEnginesGenerator(mRepo, customizer, id, elementType, this);
	/*} else if (elementType == "IotikSendMessage") {
		return new SendMessageGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikWaitForMessage") {
		return new WaitForMessageGenerator(mRepo, customizer, id, this);
	*/} else if (elementType == "IotikSystem") {
		return new SystemGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikDetectorToVariable") {
		return new DetectorToVariableGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikWaitForMotion") {
		return new WaitForMotionGenerator(mRepo, customizer, id, this);
	} else if (elementType == "IotikWaitForIRDistance") {
		return new WaitForInfraredSensorGenerator(mRepo, customizer, id, this);
	}

	return GeneratorFactoryBase::simpleGenerator(id, customizer);
}

QStringList IotikGeneratorFactory::pathsToTemplates() const
{
	return {":/" + mGeneratorName + "/templates"};
}

generatorBase::parts::DeviceVariables *IotikGeneratorFactory::deviceVariables() const
{
	return new iotik::parts::IotikDeviceVariables();
}
