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

#include "flameSensorGenerator.h"
#include "generatorBase/generatorCustomizer.h"

using namespace iotik::simple;
using namespace generatorBase::simple;
using namespace qReal;

FlameSensorGenerator::FlameSensorGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id,
					   repo.property(id, "Port").toString().at(0) == 'D' ?
						   "sensors/oneVariableOneDigitalPort.t" : "sensors/analogPort.t",
					   QList<Binding *>()
			<< Binding::createStatic("@@DRIVER@@", "FLAME")
			<< Binding::createConverting("@@PORT@@", "Port", customizer.factory()->portNameConverter())
			<< Binding::createStaticConverting("@@VARIABLE@@"
								, repo.property(id, "Variable").toString()
								, customizer.factory()->functionBlockConverter(id, "Variable"))
			, parent)
{
}
