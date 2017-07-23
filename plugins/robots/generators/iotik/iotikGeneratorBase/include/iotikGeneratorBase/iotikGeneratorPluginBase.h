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
