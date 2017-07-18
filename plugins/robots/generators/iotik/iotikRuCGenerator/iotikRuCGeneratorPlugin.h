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

namespace utils {
class TcpRobotCommunicator;
}

namespace trik {
namespace ruc {

/// Generation of QtScript program for TRIK, uploading and execution of a program.
/// Uses setting "tcpServer" from RobotsInterpreter.
class TrikRuCGeneratorPlugin : public TrikGeneratorPluginBase
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "trik.TrikRuCGeneratorPlugin")

public:
	TrikRuCGeneratorPlugin();
	~TrikRuCGeneratorPlugin() override;

	QList<qReal::ActionInfo> actions() override;

	void init(qReal::PluginConfigurator const &configurator
			, interpreterBase::robotModel::RobotModelManagerInterface const &robotModelManager
			, qrtext::LanguageToolboxInterface &textLanguage) override;

protected:
	generatorBase::MasterGeneratorBase *masterGenerator() override;
	QString defaultFilePath(QString const &projectName) const override;
	qReal::text::LanguageInfo language() const override;
	QString generatorName() const override;

private slots:

	/// Generates and uploads script to a robot. Program then can be launched manually or remotely
	/// by runCommand. Program is stored on robot as a file next to scriptRunner and named
	/// as <qReal save name>.qts.
	/// @returns True, if successful.
	bool uploadProgram();

	/// Runs currently opened program on a robot. Uploads it first.
	void runProgram();

	/// Tries to remotely abort script execution and stop robot.
	void stopRobot();

private:
	/// Action that launches code generator
	QAction *mGenerateCodeAction;  // Doesn't have ownership; may be disposed by GUI.

	/// Action that generates and uploads program on a robot
	QAction *mUploadProgramAction;  // Doesn't have ownership; may be disposed by GUI.

	/// Action that generates and uploads program on a robot
	QAction *mRunProgramAction;  // Doesn't have ownership; may be disposed by GUI.

	/// Action that stops script execution and turns off motors.
	QAction *mStopRobotAction;  // Doesn't have ownership; may be disposed by GUI.

	utils::TcpRobotCommunicator *mCommunicator;
};

}
}
