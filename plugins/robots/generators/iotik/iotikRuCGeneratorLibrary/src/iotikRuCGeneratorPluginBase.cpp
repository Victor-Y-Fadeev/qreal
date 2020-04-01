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

#include <qrutils/widgets/qRealMessageBox.h>
#include <qrkernel/settingsManager.h>
#include <iotikKit/communication/usbRobotCommunicationThread.h>
#include <iotikKit/communication/wifiRobotCommunicationThread.h>

#include <iotikGeneratorBase/iotikGeneratorPluginBase.h>
#include <iotikKit/robotModel/iotikRobotModelBase.h>

#include "iotikRuCMasterGenerator.h"
#include "dialogs/iotikActivator.h"

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
	, mWifiCommunicator(new WifiRobotCommunicationThread())
	, mRobotModel(*robotModel)
	, mPathsToTemplates(pathsToTemplates)
	, mRootPath(QCoreApplication::applicationDirPath())
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

	/*
	mSeparator->setSeparator(true);
	qReal::ActionInfo separatorActionInfo(mSeparator, "generators", "tools");

	mActivateAction->setObjectName("activate");
	mActivateAction->setText(tr("Аctivate IoTik 32 v2.0"));
	mActivateAction->setIcon(QIcon(":/iotik/ruc/images/activate.svg"));
	qReal::ActionInfo activateActionInfo(mActivateAction, "generators", "tools");
	connect(mActivateAction, SIGNAL(triggered()), this, SLOT(activate()), Qt::UniqueConnection);
	*/

	return {generateCodeActionInfo
				, usbUploadActionInfo
				, wifiUploadActionInfo
				/*,	separatorActionInfo
				, activateActionInfo*/
				};
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
	IotikActivator *activator = new IotikActivator(mMainWindowInterface->errorReporter());

	activator->setWindowIcon(mActivateAction->icon());
	activator->setWindowTitle(mActivateAction->text());
	activator->show();
}

void IotikRuCGeneratorPluginBase::wifiUpload()
{
	const QFileInfo fileInfo = generateCodeForProcessing();

	addDeviceVariables(fileInfo);
	if (!compileCode()) {
		return;
	}

	QFile::rename(mRootPath + "/export.txt", mRootPath + "/wifi_export.txt");

	if (!mWifiCommunicator->connect()) {
		mMainWindowInterface->errorReporter()->addError(tr("Device not connected, aborting"));
	} else {
		if (!mWifiCommunicator->sendFile("wifi_export.txt")) {
			mMainWindowInterface->errorReporter()->addError(tr("File sending failed, aborting"));
		} else {
			if (utils::QRealMessageBox::question(mMainWindowInterface->windowWidget()
					, tr("The program has been uploaded"), tr("Do you want to run it?")) == QMessageBox::Yes) {
				if (!mWifiCommunicator->sendCommand("ruc /fat/wifi_export.txt\n")) {
					mMainWindowInterface->errorReporter()->addError(tr("Program interpreting failed, aborting"));
				}
			}
		}

		mWifiCommunicator->disconnect();
	}

	QFile::remove(mRootPath + "/wifi_export.txt");
}

void IotikRuCGeneratorPluginBase::usbUpload()
{
	const QFileInfo fileInfo = generateCodeForProcessing();
	const QString mRootPath = QCoreApplication::applicationDirPath();

	addDeviceVariables(fileInfo);
	if (!compileCode()) {
		return;
	}

	if (!mUsbCommunicator->connect()) {
		mMainWindowInterface->errorReporter()->addError(tr("Device not connected, aborting"));
	} else {
		if (!mUsbCommunicator->sendFile("export.txt")) {
			mMainWindowInterface->errorReporter()->addError(tr("File sending failed, aborting"));
		} else {
			if (utils::QRealMessageBox::question(mMainWindowInterface->windowWidget()
					, tr("The program has been uploaded"), tr("Do you want to run it?")) == QMessageBox::Yes) {
				if (!mUsbCommunicator->sendCommand("ruc /fat/export.txt\n")) {
					mMainWindowInterface->errorReporter()->addError(tr("Program interpreting failed, aborting"));
				}
			}
		}

		mUsbCommunicator->disconnect();
	}

	QFile::remove(mRootPath + "/export.txt");
}

bool IotikRuCGeneratorPluginBase::compileCode()
{
	QDir::setCurrent(mRootPath);

	if (QFile::exists(RUC_COMPILER)) {
		QProcess::execute(RUC_COMPILER, {mRootPath + "/import.c"});
	} else {
		QProcess::execute(RUC_DEBUG_COMPILER, {mRootPath + "/import.c"});
	}

	QFile::remove(mRootPath + "/import.c");
	QFile::remove(mRootPath + "/macro.txt");
	QFile::remove(mRootPath + "/tree.txt");
	QFile::remove(mRootPath + "/codes.txt");

	if (!QFile::exists(mRootPath + "/export.txt")) {
		mMainWindowInterface->errorReporter()->addError(tr("Code compiling failed, aborting"));
		return false;
	}

	return true;
}

void IotikRuCGeneratorPluginBase::addDeviceVariables(const QFileInfo fileInfo)
{
	QString variables =
			"#define RED_COLOR 0\n"
			"#define GREEN_COLOR 1\n"
			"#define BLUE_COLOR 2\n"

			"#define LINE 3\n"
			"#define FLAME 4\n"
			"#define INFARED 5\n"
			"#define SOUND 6\n"
			"#define TOUCH 7\n"
			"#define ULTRASONIC 8\n"
			"#define TEMPERATURE 9\n"
			"#define WATER 10\n"
			"#define SOIL 11\n"
			"#define FLOW 12\n"
			"#define LASER 13\n"

			"#define X_ACCELEROMETER 14\n"
			"#define Y_ACCELEROMETER 15\n"
			"#define Z_ACCELEROMETER 16\n"
			"#define X_GYROSCOPE 17\n"
			"#define Y_GYROSCOPE 18\n"
			"#define Z_GYROSCOPE 19\n"
			"#define X_COMPASS 20\n"
			"#define Y_COMPASS 21\n"
			"#define Z_COMPASS 22\n"

			"#define HEATING 23\n"
			"#define HUMIDITY 24\n"
			"#define PRESSURE 25\n"
			"#define LIGHT 26\n"
			"#define CAPACITIVE 27\n"
			"#define UVA_ULTRAVIOLET 28\n"
			"#define UVB_ULTRAVIOLET 29\n"

			"#define RELAY 0\n"
			"#define RGB 1\n"
			"#define MATRIX 2\n"
			"#define ENGINES 3\n"


			"#define MA -1\n"
			"#define MB -2\n"

			"#define A4 32\n"
			"#define A5 33\n"
			"#define A6 34\n"
			"#define A7 35\n"
			"#define A18 25\n"
			"#define A19 26\n"

			"#define TXD 1\n"
			"#define RXD 3\n"
			"#define D4 4\n"
			"#define D5 5\n"
			"#define D13 13\n"
			"#define D14 14\n"
			"#define D15 15\n"
			"#define D16 16\n"
			"#define D17 17\n"
			"#define D18 18\n"
			"#define D19 19\n"
			"#define D21 21\n"
			"#define D22 22\n"
			"#define D23 23\n"

			"#define SUN 0\n"
			"#define LAMP 1\n"
			"#define CLOCK 2\n"
			"#define BATTERY 3\n"
			"#define WIFI 4\n"
			"#define LEFT 5\n"
			"#define RIGHT 6\n"
			"#define UP 7\n"
			"#define DOWN 8\n";

	for (int i = 0; i < 256; i++)
	{
		variables += "#define V" + QString::number(i) + " " + QString::number(i) + "\n";
	}

	const QString filePath = fileInfo.absoluteFilePath();

	QFile file(filePath);
	file.open(QIODevice::ReadOnly);
	QString code = file.readAll();
	file.close();

	file.setFileName(mRootPath + "/import.c");
	file.open(QIODevice::WriteOnly);
	file.write(QByteArray::fromStdString((variables + code).toStdString()));
	file.close();
}
