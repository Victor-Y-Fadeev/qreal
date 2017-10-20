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

#include <widgets/iotikAdditionalPreferences.h>

#include "iotikGeneratorBaseDeclSpec.h"

#include "src/robotModel/iotikGeneratorRobotModel.h"

namespace iotik {

namespace robotModel {
class IotikGeneratorRobotModel;
}

namespace blocks {
class IotikBlocksFactory;
}

/// A base class for every generator from the IoTik kit.
class ROBOTS_IOTIK_GENERATOR_BASE_EXPORT IotikGeneratorPluginBase : public generatorBase::RobotsGeneratorPluginBase
{
	Q_OBJECT

public:
	IotikGeneratorPluginBase(const QString &robotName, const QString &robotFriendlyName, int priority);
	~IotikGeneratorPluginBase() override;

	QString kitId() const override;

	QList<kitBase::robotModel::RobotModelInterface *> robotModels() override;
	kitBase::blocksBase::BlocksFactoryInterface *blocksFactoryFor(
			const kitBase::robotModel::RobotModelInterface *model) override;

	kitBase::robotModel::RobotModelInterface *defaultRobotModel() override;

	QList<kitBase::AdditionalPreferences *> settingsWidgets() override;
	QWidget *quickPreferencesFor(const kitBase::robotModel::RobotModelInterface &model) override;

protected:
	void regenerateExtraFiles(const QFileInfo &newFileInfo) override;

private:
	/// Robot model that is used to query information about various robot devices.
	robotModel::IotikGeneratorRobotModel mRobotModel;

	QWidget *producePortConfigurer();  // Transfers ownership

	IotikAdditionalPreferences *mAdditionalPreferences = nullptr;
	bool mOwnsAdditionalPreferences = true;

	/// Does not have ownership.
	kitBase::blocksBase::BlocksFactoryInterface *mBlocksFactory;
};

}
