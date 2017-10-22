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

#include "iotikGeneratorBase/iotikGeneratorPluginBase.h"

#include <qrutils/inFile.h>

using namespace iotik;
using namespace qReal;

IotikGeneratorPluginBase::IotikGeneratorPluginBase(kitBase::robotModel::RobotModelInterface * const robotModel
		, kitBase::blocksBase::BlocksFactoryInterface * const blocksFactory)
	: mRobotModel(robotModel)
	, mBlocksFactory(blocksFactory)
{
	mAdditionalPreferences = new IotikAdditionalPreferences(mRobotModel.data()->name());
}

IotikGeneratorPluginBase::~IotikGeneratorPluginBase()
{
	if (mOwnsAdditionalPreferences) {
		delete mAdditionalPreferences;
	}
}

QList<kitBase::robotModel::RobotModelInterface *> IotikGeneratorPluginBase::robotModels()
{
	return { mRobotModel.data() };
}

kitBase::robotModel::RobotModelInterface *IotikGeneratorPluginBase::defaultRobotModel()
{
	return mRobotModel.data();
}

kitBase::blocksBase::BlocksFactoryInterface *IotikGeneratorPluginBase::blocksFactoryFor(
		const kitBase::robotModel::RobotModelInterface *model)
{
	Q_UNUSED(model)
	return mBlocksFactory;
}

QList<kitBase::AdditionalPreferences *> IotikGeneratorPluginBase::settingsWidgets()
{
	mOwnsAdditionalPreferences = false;
	return {mAdditionalPreferences};
}

QWidget *IotikGeneratorPluginBase::quickPreferencesFor(const kitBase::robotModel::RobotModelInterface &model)
{
	return nullptr;
}

void IotikGeneratorPluginBase::regenerateExtraFiles(const QFileInfo &newFileInfo)
{
	Q_UNUSED(newFileInfo);
}

kitBase::robotModel::RobotModelInterface &IotikGeneratorPluginBase::robotModel() const
{
	return *mRobotModel.data();
}
