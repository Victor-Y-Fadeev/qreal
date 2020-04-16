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

#include "blynkLedGenerator.h"

#include <generatorBase/generatorCustomizer.h>

using namespace iotik::simple;
using namespace generatorBase::simple;
using namespace qReal;

BlynkLedGenerator::BlynkLedGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id,
					   repo.property(id, "Color").toString().compare("off") == 0 ?
						   "network/send.t" : "network/led.t",
					   QList<Binding *>()
			<< Binding::createConverting("@@PORT@@", "Port", customizer.factory()->portNameConverter())
			<< Binding::createStaticConverting("@@VALUE@@"
					, repo.property(id, "Color").toString().compare("off") == 0 ? "0" : "255"
					, customizer.factory()->stringPropertyConverter(id, "Color"))
			<< Binding::createStaticConverting("@@COLOR@@"
					, repo.property(id, "Color").toString().compare("green") == 0 ? "\"#23C48E\"" :
						repo.property(id, "Color").toString().compare("blue") == 0 ? "\"#04C0F8\"" :
						repo.property(id, "Color").toString().compare("orange") == 0 ? "\"#ED9D00\"" :
						repo.property(id, "Color").toString().compare("red") == 0 ? "\"#D3435C\"" :
						repo.property(id, "Color").toString().compare("violet") == 0 ? "\"#5F7CD8\"" : "\"#000000\""
					, customizer.factory()->stringPropertyConverter(id, "Color"))
			, parent)
{
}
