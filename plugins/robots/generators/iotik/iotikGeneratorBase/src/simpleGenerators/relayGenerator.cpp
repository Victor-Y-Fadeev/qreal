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

RelayGenerator::RelayGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "sensors/signalForFourParameters.t", QList<Binding *>()
			<< Binding::createStatic("@@DRIVER@@", "RELAY")
			<< Binding::createStaticConverting("@@PARAM@@"
					, repo.property(id, "First").toString().compare("false") == 0 ? "0" : "1"
					, customizer.factory()->boolPropertyConverter(id, "First", false))

			<< Binding::createStaticConverting("@@PARAM_2@@"
					, repo.property(id, "Second").toString().compare("false") == 0 ? "0" : "1"
					, customizer.factory()->boolPropertyConverter(id, "Second", false))

			<< Binding::createStaticConverting("@@PARAM_3@@"
					, repo.property(id, "Third").toString().compare("false") == 0 ? "0" : "1"
					, customizer.factory()->boolPropertyConverter(id, "Third", false))

			<< Binding::createStaticConverting("@@PARAM_4@@"
					, repo.property(id, "Fourth").toString().compare("false") == 0 ? "0" : "1"
					, customizer.factory()->boolPropertyConverter(id, "Fourth", false))
			, parent)
{
}
