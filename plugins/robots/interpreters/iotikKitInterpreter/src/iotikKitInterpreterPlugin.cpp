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

#include "iotikKitInterpreterPlugin.h"

#include <QtWidgets/QApplication>

using namespace iotik;

IotikKitInterpreterPlugin::IotikKitInterpreterPlugin()
{
}

QString IotikKitInterpreterPlugin::kitId() const
{
	return "iotikKit";
}

QString IotikKitInterpreterPlugin::friendlyKitName() const
{
	return tr("IoTik v1.0");
}

QList<kitBase::robotModel::RobotModelInterface *> IotikKitInterpreterPlugin::robotModels()
{
	return {};
}

kitBase::blocksBase::BlocksFactoryInterface *IotikKitInterpreterPlugin::blocksFactoryFor(
		const kitBase::robotModel::RobotModelInterface *model)
{
	Q_UNUSED(model);
	return mBlocksFactory;
}

QList<kitBase::AdditionalPreferences *> IotikKitInterpreterPlugin::settingsWidgets()
{
	return {};
}

QList<qReal::ActionInfo> IotikKitInterpreterPlugin::customActions()
{
	return {};
}

QList<qReal::HotKeyActionInfo> IotikKitInterpreterPlugin::hotKeyActions()
{
	return {};
}

QIcon IotikKitInterpreterPlugin::iconForFastSelector(
		const kitBase::robotModel::RobotModelInterface &robotModel) const
{
	Q_UNUSED(robotModel);
	return QIcon();
}
