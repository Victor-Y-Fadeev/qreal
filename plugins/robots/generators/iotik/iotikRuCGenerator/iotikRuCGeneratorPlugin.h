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

#include <iotikGeneratorBase/iotikGeneratorPluginBase.h>

#include "../iotikGeneratorBase/src/robotModel/iotikGeneratorRobotModel.h"

#include <iotikRuCAdditionalPreferences.h>

namespace iotik {
namespace ruc {

/// Generation of QtScript program for IoTik, uploading and execution of a program.
/// Uses setting "tcpServer" from RobotsInterpreter.
class IotikRuCGeneratorPlugin : public IotikGeneratorPluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "iotik.IotikRuCGeneratorPlugin")

public:
	IotikRuCGeneratorPlugin();

	QList<qReal::ActionInfo> customActions() override;
	QList<qReal::HotKeyActionInfo> hotKeyActions() override;
	QIcon iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const override;

protected:
	generatorBase::MasterGeneratorBase *masterGenerator() override;
	QString defaultFilePath(const QString &projectName) const override;
	qReal::text::LanguageInfo language() const override;
	QString generatorName() const override;

private:
	/// Action that launches code generator
	QAction *mGenerateCodeAction;  // Doesn't have ownership; may be disposed by GUI.
	robotModel::real::RealRobotModel mRealRobotModel;
	IotikAdditionalPreferences *mAdditionalPreferences = nullptr;
};

}
}
