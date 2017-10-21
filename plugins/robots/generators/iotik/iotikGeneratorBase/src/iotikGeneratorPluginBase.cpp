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

#include <iotikKit/blocks/iotikBlocksFactory.h>

#include <utils/widgets/comPortPicker.h>

#include "src/robotModel/iotikGeneratorRobotModel.h"

using namespace iotik;
using namespace qReal;

IotikGeneratorPluginBase::IotikGeneratorPluginBase(const QString &robotName, const QString &robotFriendlyName
	   , int priority)
	: mRobotModel(kitId(), "iotikGeneratorRobot", robotName, robotFriendlyName, priority)
	, mBlocksFactory(new blocks::IotikBlocksFactory)
	, mActivateAction(new QAction(nullptr))
	, mSeparator(nullptr)
{
	mAdditionalPreferences = new IotikAdditionalPreferences(mRobotModel.name());

	connect(mAdditionalPreferences, &IotikAdditionalPreferences::settingsChanged
			, &mRobotModel, &iotik::robotModel::IotikGeneratorRobotModel::rereadSettings);

	mSeparator.setSeparator(true);
}

IotikGeneratorPluginBase::~IotikGeneratorPluginBase()
{
	if (mOwnsAdditionalPreferences) {
		delete mAdditionalPreferences;
	}
}

QList<qReal::ActionInfo> IotikGeneratorPluginBase::activateActions()
{
	mActivateAction->setObjectName("activate");
	mActivateAction->setText(tr("Аctivate IoTik v1.0"));
	mActivateAction->setIcon(QIcon(":/images/activate.svg"));
	qReal::ActionInfo activateActionInfo(mActivateAction, "generators", "tools");
	connect(mActivateAction, SIGNAL(triggered()), this, SLOT(activate()), Qt::UniqueConnection);

	return {qReal::ActionInfo(&mSeparator, "generators", "tools"), activateActionInfo};
}

void IotikGeneratorPluginBase::activate()
{
	mMainWindowInterface->errorReporter()->addError(tr("Activator is not released yet"));
}

QString IotikGeneratorPluginBase::kitId() const
{
	return "iotikKit";
}

QList<kitBase::robotModel::RobotModelInterface *> IotikGeneratorPluginBase::robotModels()
{
	return {&mRobotModel};
}

kitBase::robotModel::RobotModelInterface *IotikGeneratorPluginBase::defaultRobotModel()
{
	return &mRobotModel;
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
	return producePortConfigurer();
}

QWidget *IotikGeneratorPluginBase::producePortConfigurer()
{
	QWidget * const result = new ui::ComPortPicker("IotikPortName", this);
	connect(this, &QObject::destroyed, [result]() { delete result; });
	return result;
}

void IotikGeneratorPluginBase::regenerateExtraFiles(const QFileInfo &newFileInfo)
{
	Q_UNUSED(newFileInfo);
}
