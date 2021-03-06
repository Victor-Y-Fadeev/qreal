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

#include "forLoopGenerator.h"
#include "generatorBase/generatorCustomizer.h"

using namespace iotik::simple;
using namespace generatorBase::simple;
using namespace qReal;

const QString iteratorName = "iter_";

ForLoopGenerator::ForLoopGenerator(int index
		, const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "conditional/for.t", QList<Binding *>()
			<< Binding::createStaticConverting("@@ITERATOR@@"
								, iteratorName + QString::number(index)
								, customizer.factory()->functionBlockConverter(id, "Variable"))
			<< Binding::createStatic("@@INITIAL_VALUE@@", "0")
			<< Binding::createConverting("@@BOUND@@", "Iterations"
					, customizer.factory()->intPropertyConverter(id, "Iterations"))
			, parent)
{
}
