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

#include <QtCore/QScopedPointer>

#include <generatorBase/robotsGeneratorPluginBase.h>

#include <widgets/iotikAdditionalPreferences.h>

#include "iotikGeneratorBaseDeclSpec.h"

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
	IotikGeneratorPluginBase(kitBase::robotModel::RobotModelInterface * const robotModel
			, kitBase::blocksBase::BlocksFactoryInterface * const blocksFactory
			);

	~IotikGeneratorPluginBase() override;

	QList<kitBase::robotModel::RobotModelInterface *> robotModels() override;

	kitBase::blocksBase::BlocksFactoryInterface *blocksFactoryFor(
			const kitBase::robotModel::RobotModelInterface *model) override;

	kitBase::robotModel::RobotModelInterface *defaultRobotModel() override;

	QList<kitBase::AdditionalPreferences *> settingsWidgets() override;
	QWidget *quickPreferencesFor(const kitBase::robotModel::RobotModelInterface &model) override;

protected:
	void regenerateExtraFiles(const QFileInfo &newFileInfo) override;

	/// Provides access to robot model to descendant classes.
	kitBase::robotModel::RobotModelInterface &robotModel() const;

private:
	/// Robot model that is used to query information about various robot devices.
	QScopedPointer<kitBase::robotModel::RobotModelInterface> mRobotModel;

	/// Does not have ownership.
	kitBase::blocksBase::BlocksFactoryInterface *mBlocksFactory;

	IotikAdditionalPreferences *mAdditionalPreferences = nullptr;
	bool mOwnsAdditionalPreferences = true;
};

}
