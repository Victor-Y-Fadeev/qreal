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

#pragma once

#include <generatorBase/generatorFactoryBase.h>

namespace iotik {

/// Generator factory implemtation for IoTik platform
class IotikGeneratorFactory : public generatorBase::GeneratorFactoryBase
{
public:
	IotikGeneratorFactory(const qrRepo::RepoApi &repo
			, qReal::ErrorReporterInterface &errorReporter
			, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
			, generatorBase::lua::LuaProcessor &luaProcessor
			, const QStringList &pathsToTemplates);

	~IotikGeneratorFactory() override;

	/// Returns a pointer to a code generator for loops in 'for' form
	virtual generatorBase::simple::AbstractSimpleGenerator *forLoopGenerator(const qReal::Id &id
			, generatorBase::GeneratorCustomizer &customizer);

	generatorBase::simple::AbstractSimpleGenerator *simpleGenerator(const qReal::Id &id
			, generatorBase::GeneratorCustomizer &customizer) override;

	QStringList pathsToTemplates() const override;

private:
	const QStringList mPathsToTemplates;
	int mRgbIndex = 0;
	int mMatrixIndex = 0;
};

}
