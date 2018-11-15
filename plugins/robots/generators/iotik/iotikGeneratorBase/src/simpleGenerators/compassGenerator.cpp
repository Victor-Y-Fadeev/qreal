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

#include "compassGenerator.h"

#include <generatorBase/generatorCustomizer.h>

using namespace iotik::simple;
using namespace generatorBase::simple;
using namespace qReal;

CompassGenerator::CompassGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "sensors/threeVariableTwoDigitalPort.t", QList<Binding *>()
			<< Binding::createStatic("@@DRIVER@@", "X_COMPASS")
			<< Binding::createStatic("@@DRIVER_2@@", "Y_COMPASS")
			<< Binding::createStatic("@@DRIVER_3@@", "Z_COMPASS")
			<< Binding::createConverting("@@PORT@@", "SCL", customizer.factory()->portNameConverter())
			<< Binding::createConverting("@@PORT_2@@", "SDA", customizer.factory()->portNameConverter())
			<< Binding::createStaticConverting("@@VARIABLE@@"
								, repo.property(id, "X").toString()
								, customizer.factory()->functionBlockConverter(id, "Variable"))
			<< Binding::createStaticConverting("@@VARIABLE_2@@"
								, repo.property(id, "Y").toString()
								, customizer.factory()->functionBlockConverter(id, "Variable"))
			<< Binding::createStaticConverting("@@VARIABLE_3@@"
								, repo.property(id, "Z").toString()
								, customizer.factory()->functionBlockConverter(id, "Variable"))
			, parent)
{
}
