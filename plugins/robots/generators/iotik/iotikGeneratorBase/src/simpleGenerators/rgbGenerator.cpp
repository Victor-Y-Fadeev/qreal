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

#include "rgbGenerator.h"

#include <generatorBase/generatorCustomizer.h>

using namespace iotik::simple;
using namespace generatorBase::simple;
using namespace qReal;

RgbGenerator::RgbGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "sensors/signalForSevenParameters.t", QList<Binding *>()
			<< Binding::createStatic("@@DRIVER@@", "RELAY")
			<< Binding::createConverting("@@PORT@@", "SCL", customizer.factory()->portNameConverter())
			<< Binding::createConverting("@@PORT_2@@", "SDA", customizer.factory()->portNameConverter())


			<< Binding::createConverting("@@PARAM@@", "Red"
					, customizer.factory()->intPropertyConverter(id, "Red"))

			<< Binding::createConverting("@@PARAM_2@@", "Green"
					, customizer.factory()->intPropertyConverter(id, "Green"))

			<< Binding::createConverting("@@PARAM_3@@", "Blue"
					, customizer.factory()->intPropertyConverter(id, "Blue"))

			<< Binding::createConverting("@@PARAM_4@@", "White"
					, customizer.factory()->intPropertyConverter(id, "White"))
			<< Binding::createConverting("@@PARAM_5@@", "White"
					, customizer.factory()->intPropertyConverter(id, "White"))

			<< Binding::createStaticConverting("@@PARAM_6@@"
					, repo.property(id, "UV").toString().compare("false") == 0 ? "0" : "255"
					, customizer.factory()->boolPropertyConverter(id, "UV", false))
			<< Binding::createStaticConverting("@@PARAM_7@@"
					, repo.property(id, "UV").toString().compare("false") == 0 ? "0" : "255"
					, customizer.factory()->boolPropertyConverter(id, "UV", false))
			, parent)
{
}
