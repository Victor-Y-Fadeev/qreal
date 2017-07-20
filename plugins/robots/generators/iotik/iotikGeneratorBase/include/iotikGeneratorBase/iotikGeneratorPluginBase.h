#pragma once

#include <generatorBase/robotsGeneratorPluginBase.h>

#include "iotikGeneratorBase/iotikGeneratorBaseDeclSpec.h"

namespace iotik {

/// A base class for every generator from the TRIK kit.
class ROBOTS_IOTIK_GENERATOR_BASE_EXPORT IotikGeneratorPluginBase : public generatorBase::RobotsGeneratorPluginBase
{
	Q_OBJECT

public:
	IotikGeneratorPluginBase();

	QString kitId() const override;

protected:
	void regenerateExtraFiles(QFileInfo const &newFileInfo) override;
};

}
