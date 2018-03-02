/* Copyright 2007-2015 QReal Research Group
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

#include <iotikRuCGeneratorLibrary/iotikRuCGeneratorPluginBase.h>

namespace iotik {

namespace robotModel {
class IotikGeneratorRobotModel;
}

namespace ruc {

/// RuC generator specialization for IoTik v2.0 ("new case", with encoders marked as E1 - E4).
class IotikRuCEnglishGeneratorPlugin : public IotikRuCGeneratorPluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "iotik.IotikRuCEnglishGeneratorPlugin")

public:
	IotikRuCEnglishGeneratorPlugin();

	QString kitId() const override;

private:
	/// Temporary storage for robot model to be able to correctly initialize it.
	/// Does not have ownership.
	robotModel::IotikGeneratorRobotModel *mModel;
};

}
}
