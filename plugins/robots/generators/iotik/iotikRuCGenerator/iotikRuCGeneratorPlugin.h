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

#include <iotikRuCAdditionalPreferences.h>

#include "robotModel/real/realRobotModel.h"

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

	QList<kitBase::robotModel::RobotModelInterface *> robotModels() override;

	QList<qReal::ActionInfo> customActions() override;
	QList<qReal::HotKeyActionInfo> hotKeyActions() override;
	//QList<kitBase::AdditionalPreferences *> settingsWidgets() override;
	QIcon iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const override;

protected:
	generatorBase::MasterGeneratorBase *masterGenerator() override;
	QString defaultFilePath(const QString &projectName) const override;
	qReal::text::LanguageInfo language() const override;
	QString generatorName() const override;

private slots:
	/// Generates and uploads script to a robot. Program then can be launched manually or remotely
	/// by runCommand. Program is stored on robot as a file next to scriptRunner and named
	/// as <qReal save name>.c.
	void uploadProgram();


private:
	robotModel::real::RealRobotModel mRealRobotModel;

	QWidget *producePortConfigurer();  // Transfers ownership
	/// Action that launches code generator
	QAction *mGenerateCodeAction;  // Doesn't have ownership; may be disposed by GUI.

	QAction *mUploadProgramAction;  // Doesn't have ownership; may be disposed by GUI.

	IotikAdditionalPreferences *mAdditionalPreferences = nullptr;

	/// Action that generates and uploads program on a robot

};

}
}
