#pragma once

#include <generatorBase/masterGeneratorBase.h>

#include "iotikGeneratorBase/iotikGeneratorBaseDeclSpec.h"

namespace iotik {

/// Master generator base implementation for every generator from IoTik kit
class ROBOTS_IOTIK_GENERATOR_BASE_EXPORT IotikMasterGeneratorBase : public generatorBase::MasterGeneratorBase
{
public:
	IotikMasterGeneratorBase(qrRepo::RepoApi const &repo
			, qReal::ErrorReporterInterface &errorReporter
			, interpreterBase::robotModel::RobotModelManagerInterface const &robotModelManager
			, qrtext::LanguageToolboxInterface &textLanguage
			, qReal::Id const &diagramId
			, QString const &generatorName);

protected:
	generatorBase::GeneratorCustomizer *createCustomizer() override;

private:
	QString const mGeneratorName;
};

}
