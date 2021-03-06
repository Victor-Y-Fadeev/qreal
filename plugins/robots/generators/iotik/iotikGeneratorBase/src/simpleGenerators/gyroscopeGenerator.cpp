/* Copyright 2018 QReal Research Group
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

#include "gyroscopeGenerator.h"

#include <generatorBase/generatorCustomizer.h>

using namespace iotik::simple;
using namespace generatorBase::simple;
using namespace qReal;

GyroscopeGenerator::GyroscopeGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "sensors/threeVariableTwoDigitalPortWithDivision.t", QList<Binding *>()
			<< Binding::createStatic("@@DRIVER@@", "X_GYROSCOPE")
			<< Binding::createStatic("@@DRIVER_2@@", "Y_GYROSCOPE")
			<< Binding::createStatic("@@DRIVER_3@@", "Z_GYROSCOPE")
			<< Binding::createConverting("@@PORT@@", "SCL", customizer.factory()->portNameConverter())
			<< Binding::createConverting("@@PORT_2@@", "SDA", customizer.factory()->portNameConverter())

			<< Binding::createStaticConverting("@@JUST_FOR_VAR_INIT@@"
							, repo.property(id, "X").toString() + " = 0.0"
							, customizer.factory()->functionBlockConverter(id, "X"))
			<< Binding::createStaticConverting("@@VARIABLE@@"
								, repo.property(id, "X").toString()
								, customizer.factory()->functionBlockConverter(id, "X"))

			<< Binding::createStaticConverting("@@JUST_FOR_VAR_INIT@@"
							, repo.property(id, "Y").toString() + " = 0.0"
							, customizer.factory()->functionBlockConverter(id, "Y"))
			<< Binding::createStaticConverting("@@VARIABLE_2@@"
								, repo.property(id, "Y").toString()
								, customizer.factory()->functionBlockConverter(id, "Y"))

			<< Binding::createStaticConverting("@@JUST_FOR_VAR_INIT@@"
							, repo.property(id, "Z").toString() + " = 0.0"
							, customizer.factory()->functionBlockConverter(id, "Z"))
			<< Binding::createStaticConverting("@@VARIABLE_3@@"
								, repo.property(id, "Z").toString()
								, customizer.factory()->functionBlockConverter(id, "Z"))
			, parent)
{
}
