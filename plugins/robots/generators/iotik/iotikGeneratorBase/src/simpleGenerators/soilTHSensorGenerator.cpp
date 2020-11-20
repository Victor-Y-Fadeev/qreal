/* Copyright 2020 QReal Research Group
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

#include "soilTHSensorGenerator.h"
#include <generatorBase/generatorCustomizer.h>

using namespace iotik::simple;
using namespace generatorBase::simple;
using namespace qReal;

SoilTHSensorGenerator::SoilTHSensorGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "sensors/twoVariablesTwoAnalogPorts.t", QList<Binding *>()
			<< Binding::createStatic("@@DRIVER@@", "TEMPERATURE")
			<< Binding::createStatic("@@DRIVER_2@@", "SOIL")
			<< Binding::createConverting("@@PORT@@", "A", customizer.factory()->portNameConverter())
			<< Binding::createConverting("@@PORT_2@@", "B", customizer.factory()->portNameConverter())

			<< Binding::createStaticConverting("@@JUST_FOR_VAR_INIT@@"
							, repo.property(id, "Temperature").toString() + " = 0"
							, customizer.factory()->functionBlockConverter(id, "Temperature"))
			<< Binding::createStaticConverting("@@VARIABLE@@"
								, repo.property(id, "Temperature").toString()
								, customizer.factory()->functionBlockConverter(id, "Temperature"))

			<< Binding::createStaticConverting("@@JUST_FOR_VAR_INIT@@"
							, repo.property(id, "Humidity").toString() + " = 0"
							, customizer.factory()->functionBlockConverter(id, "Humidity"))
			<< Binding::createStaticConverting("@@VARIABLE_2@@"
								, repo.property(id, "Humidity").toString()
								, customizer.factory()->functionBlockConverter(id, "Humidity"))
			, parent)
{
}
