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

#include <iotikKit/robotModel/iotikRobotModelBase.h>

namespace iotik {
namespace robotModel {

class GeneratorRobotModel : public IotikRobotModelBase
{
	Q_OBJECT

public:
	GeneratorRobotModel(const QString &kitId, const QString &robotId);

	QString name() const override;
	QString friendlyName() const override;

	bool needsConnection() const override;
	bool interpretedModel() const override;

	int priority() const override;

};

}
}
