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

#include <generatorBase/masterGeneratorBase.h>

#include "iotikGeneratorBaseDeclSpec.h"

namespace iotik {

/// Master generator base implementation for every generator from IoTik kit
class ROBOTS_IOTIK_GENERATOR_BASE_EXPORT IotikMasterGeneratorBase : public generatorBase::MasterGeneratorBase
{
public:
	IotikMasterGeneratorBase(const qrRepo::RepoApi &repo
			, qReal::ErrorReporterInterface &errorReporter
			, const utils::ParserErrorReporter &parserErrorReporter
			, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
			, qrtext::LanguageToolboxInterface &textLanguage
			, const qReal::Id &diagramId
			, const QString &generatorName);

protected:
	generatorBase::GeneratorCustomizer *createCustomizer() override;

private:
	const QString mGeneratorName;
};

}
