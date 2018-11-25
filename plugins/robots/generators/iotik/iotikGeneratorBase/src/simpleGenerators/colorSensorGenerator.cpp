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

#include "colorSensorGenerator.h"

#include <generatorBase/generatorCustomizer.h>

using namespace iotik::simple;
using namespace generatorBase::simple;
using namespace qReal;

ColorSensorGenerator::ColorSensorGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "sensors/threeVariableFiveDigitalPort.t", QList<Binding *>()
			<< Binding::createStatic("@@DRIVER@@", "RED_COLOR")
			<< Binding::createStatic("@@DRIVER_2@@", "GREEN_COLOR")
			<< Binding::createStatic("@@DRIVER_3@@", "BLUE_COLOR")
			<< Binding::createConverting("@@PORT@@", "S0", customizer.factory()->portNameConverter())
			<< Binding::createConverting("@@PORT_2@@", "S1", customizer.factory()->portNameConverter())
			<< Binding::createConverting("@@PORT_3@@", "S2", customizer.factory()->portNameConverter())
			<< Binding::createConverting("@@PORT_4@@", "S3", customizer.factory()->portNameConverter())
			<< Binding::createConverting("@@PORT_5@@", "OUT", customizer.factory()->portNameConverter())

			<< Binding::createStaticConverting("@@JUST_FOR_VAR_INIT@@"
							, repo.property(id, "Red").toString() + " = 0"
							, customizer.factory()->functionBlockConverter(id, "Red"))
			<< Binding::createStaticConverting("@@VARIABLE@@"
								, repo.property(id, "Red").toString()
								, customizer.factory()->functionBlockConverter(id, "Red"))

			<< Binding::createStaticConverting("@@JUST_FOR_VAR_INIT@@"
							, repo.property(id, "Green").toString() + " = 0"
							, customizer.factory()->functionBlockConverter(id, "Green"))
			<< Binding::createStaticConverting("@@VARIABLE_2@@"
								, repo.property(id, "Green").toString()
								, customizer.factory()->functionBlockConverter(id, "Green"))

			<< Binding::createStaticConverting("@@JUST_FOR_VAR_INIT@@"
							, repo.property(id, "Blue").toString() + " = 0"
							, customizer.factory()->functionBlockConverter(id, "Blue"))
			<< Binding::createStaticConverting("@@VARIABLE_3@@"
								, repo.property(id, "Blue").toString()
								, customizer.factory()->functionBlockConverter(id, "Blue"))
			, parent)
{
}
