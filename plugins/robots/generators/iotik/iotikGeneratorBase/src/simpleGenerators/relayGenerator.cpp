/* Copyright 2019 QReal Research Group
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

#include "relayGenerator.h"

#include <generatorBase/generatorCustomizer.h>

using namespace iotik::simple;
using namespace generatorBase::simple;
using namespace qReal;

const QString arrayName = "relay_";

RelayGenerator::RelayGenerator(int index
		, const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "sensors/signalForTwoPortFourParameters.t", QList<Binding *>()
			<< Binding::createStatic("@@DRIVER@@", "RELAY")
			<< Binding::createConverting("@@PORT@@", "SCL", customizer.factory()->portNameConverter())
			<< Binding::createConverting("@@PORT_2@@", "SDA", customizer.factory()->portNameConverter())

			<< Binding::createStaticConverting("@@JUST_FOR_ARRAY_INIT@@"
							, arrayName + QString::number(index) + " = { 0 }"
							, customizer.factory()->functionBlockConverter(id, "Variable"))
			<< Binding::createStaticConverting("@@ARRAY@@"
								, arrayName + QString::number(index)
								, customizer.factory()->functionBlockConverter(id, "Variable"))

			<< Binding::createConverting("@@PARAM@@", "First"
					, customizer.factory()->boolPropertyConverter(id, "First", false))

			<< Binding::createConverting("@@PARAM_2@@", "Second"
					, customizer.factory()->boolPropertyConverter(id, "Second", false))

			<< Binding::createConverting("@@PARAM_3@@", "Third"
					, customizer.factory()->boolPropertyConverter(id, "Third", false))

			<< Binding::createConverting("@@PARAM_4@@", "Fourth"
					, customizer.factory()->boolPropertyConverter(id, "Fourth", false))
			, parent)
{
}
