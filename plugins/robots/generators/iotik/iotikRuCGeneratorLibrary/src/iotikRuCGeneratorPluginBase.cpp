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

#include "include/iotikRuCGeneratorLibrary/iotikRuCGeneratorPluginBase.h"
#include "include/iotikRuCGeneratorLibrary/iotikRuCGeneratorDefs.h"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QProcess>

#include <qrkernel/settingsManager.h>
#include <iotikKit/communication/usbRobotCommunicationThread.h>

#include <iotikGeneratorBase/iotikGeneratorPluginBase.h>
//#include <iotikGeneratorBase/robotModel/generatorModelExtensionInterface.h>
#include <iotikKit/robotModel/iotikRobotModelBase.h>

#include "iotikRuCMasterGenerator.h"

using namespace iotik::communication;
using namespace iotik::ruc;
using namespace kitBase::robotModel;
using namespace qReal;

//const Id robotDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "RobotsDiagramNode");
//const Id subprogramDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "SubprogramDiagram");

IotikRuCGeneratorPluginBase::IotikRuCGeneratorPluginBase(
		iotik::robotModel::IotikRobotModelBase * const robotModel
		, kitBase::blocksBase::BlocksFactoryInterface * const blocksFactory
		, const QStringList &pathsToTemplates)
	: IotikGeneratorPluginBase(robotModel, blocksFactory)
	, mGenerateCodeAction(new QAction(nullptr))
	, mUsbUploadAction(new QAction(nullptr))
	, mWifiUploadAction(new QAction(nullptr))
	, mSeparator(new QAction(nullptr))
	, mActivateAction(new QAction(nullptr))
	, mUsbCommunicator(new UsbRobotCommunicationThread())
	, mRobotModel(*robotModel)
	, mPathsToTemplates(pathsToTemplates)
{
}

IotikRuCGeneratorPluginBase::~IotikRuCGeneratorPluginBase()
{
}

QList<qReal::ActionInfo> IotikRuCGeneratorPluginBase::customActions()
{
	mGenerateCodeAction->setObjectName("generateRuCCode");
	mGenerateCodeAction->setText(tr("Generate RuC code"));
	mGenerateCodeAction->setIcon(QIcon(":/iotik/ruc/images/generateRuCCode.svg"));
	qReal::ActionInfo generateCodeActionInfo(mGenerateCodeAction, "generators", "tools");
	connect(mGenerateCodeAction, SIGNAL(triggered()), this, SLOT(generateCode()), Qt::UniqueConnection);

	mUsbUploadAction->setObjectName("usbUpload");
	mUsbUploadAction->setText(tr("Upload program by USB"));
	mUsbUploadAction->setIcon(QIcon(":/iotik/ruc/images/usbUpload.svg"));
	qReal::ActionInfo usbUploadActionInfo(mUsbUploadAction, "generators", "tools");
	connect(mUsbUploadAction, SIGNAL(triggered()), this, SLOT(usbUpload()), Qt::UniqueConnection);

	mWifiUploadAction->setObjectName("wifiUpload");
	mWifiUploadAction->setText(tr("Upload program by Wi-Fi"));
	mWifiUploadAction->setIcon(QIcon(":/iotik/ruc/images/wifiUpload.svg"));
	qReal::ActionInfo wifiUploadActionInfo(mWifiUploadAction, "generators", "tools");
	connect(mWifiUploadAction, SIGNAL(triggered()), this, SLOT(wifiUpload()), Qt::UniqueConnection);

	mSeparator->setSeparator(true);
	qReal::ActionInfo separatorActionInfo(mSeparator, "generators", "tools");

	mActivateAction->setObjectName("activate");
	mActivateAction->setText(tr("Аctivate IoTik v1.0"));
	mActivateAction->setIcon(QIcon(":/iotik/ruc/images/activate.svg"));
	qReal::ActionInfo activateActionInfo(mActivateAction, "generators", "tools");
	connect(mActivateAction, SIGNAL(triggered()), this, SLOT(activate()), Qt::UniqueConnection);

	return {generateCodeActionInfo, usbUploadActionInfo, wifiUploadActionInfo,
				separatorActionInfo, activateActionInfo};
}

QList<qReal::HotKeyActionInfo> IotikRuCGeneratorPluginBase::hotKeyActions()
{
	mGenerateCodeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
	mUsbUploadAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
	mWifiUploadAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));

	qReal::HotKeyActionInfo generateCodeInfo("Generator.GenerateRuC", tr("Generate RuC Code"),
											 mGenerateCodeAction);

	qReal::HotKeyActionInfo usbUploadInfo("Generator.UsbUploadRuC", tr("Upload RuC Program by USB"),
										  mUsbUploadAction);

	qReal::HotKeyActionInfo wifiUploadInfo("Generator.WifiUploadRuC", tr("Upload RuC Program by Wi-Fi"),
										   mWifiUploadAction);

	return {generateCodeInfo, usbUploadInfo, wifiUploadInfo};
}

QIcon IotikRuCGeneratorPluginBase::iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const
{
	Q_UNUSED(robotModel)

	return QIcon(":/iotik/ruc/images/switch-to-iotik-ruc.svg");
}

generatorBase::MasterGeneratorBase *IotikRuCGeneratorPluginBase::masterGenerator()
{
	return new IotikRuCMasterGenerator(*mRepo
			, *mMainWindowInterface->errorReporter()
			, *mParserErrorReporter
			, *mRobotModelManager
			, *mTextLanguage
			, mMainWindowInterface->activeDiagram()
			, mPathsToTemplates);
}

QString IotikRuCGeneratorPluginBase::defaultFilePath(const QString &projectName) const
{
	return QString("ruc/%1/%1.c").arg(projectName);
}

qReal::text::LanguageInfo IotikRuCGeneratorPluginBase::language() const
{
	return qReal::text::Languages::c();
}

QString IotikRuCGeneratorPluginBase::generatorName() const
{
	return "iotikRuC";
}

void IotikRuCGeneratorPluginBase::activate()
{
	mMainWindowInterface->errorReporter()->addError(tr("Activator is not released yet"));
}

void IotikRuCGeneratorPluginBase::wifiUpload()
{
	mMainWindowInterface->errorReporter()->addError(tr("Wi-Fi is not released yet"));
}

void IotikRuCGeneratorPluginBase::usbUpload()
{
	const QFileInfo fileInfo = generateCodeForProcessing();
	const QString rootPath = QDir::current().absolutePath();

	if (!compileCode(fileInfo)) {
		return;
	}
	configureSensors();

	mUsbCommunicator->connect();
	mUsbCommunicator->sendCommand("cd flash\n");
	mUsbCommunicator->sendFile("sensors");
	mUsbCommunicator->sendFile("export");
	mUsbCommunicator->sendCommand("ruc export sensors\n");
	mUsbCommunicator->disconnect();

	QFile::remove(rootPath + "/sensors");
	QFile::remove(rootPath + "/export");
}

bool IotikRuCGeneratorPluginBase::compileCode(const QFileInfo fileInfo)
{
	const QString rootPath = QDir::current().absolutePath();
	const QString filePath = fileInfo.absoluteFilePath();


	if (QFile::exists(RUC_COMPILER)) {
		QProcess::execute(RUC_COMPILER, {filePath});
	} else {
		QProcess::execute(RUC_DEBUG_COMPILER, {filePath});
	}

	QFile::remove(rootPath + "/tree.txt");
	QFile::remove(rootPath + "/codes.txt");

	if (QFile::exists(rootPath + "/export.txt")) {
		QFile::rename(rootPath + "/export.txt", rootPath + "/export");
	} else {
		mMainWindowInterface->errorReporter()->addError(tr("Code compiling failed, aborting"));
		return false;
	}

	return true;
}

void IotikRuCGeneratorPluginBase::configureSensors()
{
	const QString rootPath = QDir::current().absolutePath();


	QFile sensors(rootPath + "/sensors");
	sensors.open(QIODevice::WriteOnly);
	QTextStream out(&sensors);

	out << "servos 5 12 4 13\n";
	out << "digital 1\n";
	out << "0 1 14 15\n";
	out << "analog 1\n";
	out << "0 1\n";

	sensors.close();
}
