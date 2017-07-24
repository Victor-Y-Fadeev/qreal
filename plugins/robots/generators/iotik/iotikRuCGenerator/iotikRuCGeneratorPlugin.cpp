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

#include "iotikRuCGeneratorPlugin.h"

#include <QtWidgets/QApplication>
#include <QtCore/QFileInfo>
#include <QtCore/QStateMachine>
#include <QtCore/QState>
#include <QtCore/QFinalState>

#include <qrkernel/logging.h>
#include <iotikGeneratorBase/iotikGeneratorPluginBase.h>
#include <iotikGeneratorBase/robotModel/iotikGeneratorRobotModel.h>
#include <iotikKit/robotModel/iotikRobotModelBase.h>
//#include <utils/tcpRobotCommunicator.h>

#include "iotikRuCMasterGenerator.h"

using namespace iotik::ruc;
using namespace kitBase::robotModel;
using namespace qReal;

IotikRuCGeneratorPlugin::IotikRuCGeneratorPlugin(
		 iotik::robotModel::IotikRobotModelBase * const robotModel
		, kitBase::blocksBase::BlocksFactoryInterface * const blocksFactory
		, const QStringList &pathsToTemplates)
	: IotikGeneratorPluginBase(robotModel, blocksFactory)
	, mGenerateCodeAction(new QAction(nullptr))
	, mUploadProgramAction(new QAction(nullptr))
	, mRunProgramAction(new QAction(nullptr))
	, mStopRobotAction(new QAction(nullptr))
	, mRobotModel(*robotModel)
	, mPathsToTemplates(pathsToTemplates)
{
}

IotikRuCGeneratorPlugin::~IotikRuCGeneratorPlugin()
{
	//delete mCommunicator;
}

void IotikRuCGeneratorPlugin::init(const kitBase::KitPluginConfigurator &configurer)
{
	RobotsGeneratorPluginBase::init(configurer);
	//mCommunicator = new utils::TcpRobotCommunicator("IotikTcpServer");
	//mCommunicator->setErrorReporter(configurator.mainWindowInterpretersInterface().errorReporter());
}

QList<ActionInfo> IotikRuCGeneratorPlugin::customActions()
{
	mGenerateCodeAction->setObjectName("generateRuCCode");
	mGenerateCodeAction->setText(tr("Generate RuC code"));
	mGenerateCodeAction->setIcon(QIcon(":/images/generateQtsCode.svg"));
	ActionInfo generateCodeActionInfo(mGenerateCodeAction, "generators", "tools");
	connect(mGenerateCodeAction, SIGNAL(triggered()), this, SLOT(generateCode()), Qt::UniqueConnection);

	mUploadProgramAction->setObjectName("uploadProgram");
	mUploadProgramAction->setText(tr("Upload program"));
	mUploadProgramAction->setIcon(QIcon(":/images/uploadProgram.svg"));
	ActionInfo uploadProgramActionInfo(mUploadProgramAction, "generators", "tools");
	connect(mUploadProgramAction, SIGNAL(triggered()), this, SLOT(uploadProgram()), Qt::UniqueConnection);

	mRunProgramAction->setObjectName("runProgram");
	mRunProgramAction->setText(tr("Run program"));
	mRunProgramAction->setIcon(QIcon(":/images/uploadAndExecuteProgram.svg"));
	ActionInfo runProgramActionInfo(mRunProgramAction, "generators", "tools");
	connect(mRunProgramAction, SIGNAL(triggered()), this, SLOT(runProgram()), Qt::UniqueConnection);

	mStopRobotAction->setObjectName("stopRobot");
	mStopRobotAction->setText(tr("Stop robot"));
	mStopRobotAction->setIcon(QIcon(":/images/stopRobot.svg"));
	ActionInfo stopRobotActionInfo(mStopRobotAction, "generators", "tools");
	connect(mStopRobotAction, SIGNAL(triggered()), this, SLOT(stopRobot()), Qt::UniqueConnection);


	return {generateCodeActionInfo, uploadProgramActionInfo, runProgramActionInfo, stopRobotActionInfo};
}

QList<HotKeyActionInfo> IotikRuCGeneratorPlugin::hotKeyActions()
{
	mGenerateCodeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
	mUploadProgramAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
	mRunProgramAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F5));
	mStopRobotAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_F5));

	HotKeyActionInfo generateCodeInfo("Generator.GenerateRuc", tr("Generate RuC Code"), mGenerateCodeAction);
	HotKeyActionInfo uploadProgramInfo("Generator.UploadRuc", tr("Upload Program"), mUploadProgramAction);
	HotKeyActionInfo runProgramInfo("Generator.RunRuc", tr("Run Program"), mRunProgramAction);
	HotKeyActionInfo stopRobotInfo("Generator.StopRuc", tr("Stop Robot"), mStopRobotAction);

	return {generateCodeInfo, uploadProgramInfo, runProgramInfo, stopRobotInfo};
}

QIcon IotikRuCGeneratorPlugin::iconForFastSelector(const RobotModelInterface &robotModel) const
{
	Q_UNUSED(robotModel)

	return QIcon(":/iotik/rus/images/switch-to-iotik-ruc.svg");
}

generatorBase::MasterGeneratorBase *IotikRuCGeneratorPlugin::masterGenerator()
{
	return new IotikRuCMasterGenerator(*mRepo
			, *mMainWindowInterface->errorReporter()
			, *mParserErrorReporter
			, *mRobotModelManager
			, *mTextLanguage
			, mMainWindowInterface->activeDiagram()
			, mPathsToTemplates);
}

QString IotikRuCGeneratorPlugin::defaultFilePath(const QString &projectName) const
{
	return QString("trik/%1/%1.c").arg(projectName);
}

text::LanguageInfo IotikRuCGeneratorPlugin::language() const
{
	return qReal::text::Languages::c();
}

QString IotikRuCGeneratorPlugin::generatorName() const
{
   return "iotikRuC";
}

void IotikRuCGeneratorPlugin::uploadProgram()
{
	const QFileInfo fileInfo = generateCodeForProcessing();

	if (fileInfo != QFileInfo() && !fileInfo.absoluteFilePath().isEmpty()) {
		disableButtons();
		//mUploadProgramProtocol->run(fileInfo);
	} else {
		QLOG_ERROR() << "Code generation failed, aborting";
	}
}

void IotikRuCGeneratorPlugin::runProgram()
{
	const QFileInfo fileInfo = generateCodeForProcessing();

	if (fileInfo != QFileInfo() && !fileInfo.absoluteFilePath().isEmpty()) {
		/*if (mRunProgramProtocol) {
			disableButtons();
			mRunProgramProtocol->run(fileInfo);
		} else {
			QLOG_ERROR() << "Run program protocol is not initialized";
		}*/
	} else {
		QLOG_ERROR() << "Code generation failed, aborting";
	}
}

void IotikRuCGeneratorPlugin::stopRobot()
{
	/*if (mStopRobotProtocol) {
		disableButtons();
		mStopRobotProtocol->run(
				"script.system(\"killall aplay\"); \n"
				"script.system(\"killall vlc\");"
				);
	} else {*/
		QLOG_ERROR() << "Stop robot protocol is not initialized";
	//}
}

void IotikRuCGeneratorPlugin::disableButtons()
{
	mUploadProgramAction->setEnabled(false);
	mRunProgramAction->setEnabled(false);
	mStopRobotAction->setEnabled(false);
}
