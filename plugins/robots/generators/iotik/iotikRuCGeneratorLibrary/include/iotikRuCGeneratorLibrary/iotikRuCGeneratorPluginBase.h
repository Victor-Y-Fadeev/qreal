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

#include <iotikKit/communication/usbRobotCommunicationThread.h>

namespace iotik {

namespace robotModel {
class IotikRobotModelBase;
}

namespace ruc {

/// Generation of QtScript program for IoTik, uploading and execution of a program.
/// Uses setting "tcpServer" from RobotsInterpreter.
class IotikRuCGeneratorPluginBase : public IotikGeneratorPluginBase
{
	Q_OBJECT

public:
	IotikRuCGeneratorPluginBase(iotik::robotModel::IotikRobotModelBase * const robotModel
			, kitBase::blocksBase::BlocksFactoryInterface * const blocksFactory
			, const QStringList &pathsToTemplates);

	~IotikRuCGeneratorPluginBase() override;

	QList<qReal::ActionInfo> customActions() override;
	QList<qReal::HotKeyActionInfo> hotKeyActions() override;
	QIcon iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const override;

protected:
	generatorBase::MasterGeneratorBase *masterGenerator() override;
	QString defaultFilePath(const QString &projectName) const override;
	qReal::text::LanguageInfo language() const override;
	QString generatorName() const override;

protected slots:
	/// Generates and uploads script to a robot. Program then can be launched manually or remotely
	/// by runCommand. Program is stored on robot as a file next to scriptRunner and named
	/// as <qReal save name>.c.
	void activate();
	void usbUpload();
	void wifiUpload();

protected:
	/// Action that launches code generator
	QAction *mGenerateCodeAction;  // Doesn't have ownership; may be disposed by GUI.

	/// Action that generates and uploads program on a robot
	QAction *mUsbUploadAction;  // Doesn't have ownership; may be disposed by GUI.
	QAction *mWifiUploadAction;

	QAction *mSeparator;
	QAction *mActivateAction;

	/// Communicator object used to send commands to robot.
	communication::UsbRobotCommunicationThread *mUsbCommunicator;

	/// Robot model that is used by generator to check config file version on a robot.
	iotik::robotModel::IotikRobotModelBase &mRobotModel;

	QStringList mPathsToTemplates;

	void addDeviceVariables(const QFileInfo fileInfo);
	bool compileCode();
};

}
}
