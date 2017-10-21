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
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QProcess>
#include <QtCore/QThread>

#include <qrkernel/settingsManager.h>
#include <plugins/robots/thirdparty/qextserialport/src/qextserialport.h>

#include "iotikRuCMasterGenerator.h"
#include "iotikRuCGeneratorDefs.h"

using namespace iotik::ruc;
using namespace qReal;

const Id robotDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "RobotsDiagramNode");
const Id subprogramDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "SubprogramDiagram");

IotikRuCGeneratorPlugin::IotikRuCGeneratorPlugin()
	: IotikGeneratorPluginBase("IotikRuCGeneratorRobotModel", tr("Generation (RuC)"), 7 /* Last order */)
	, mGenerateCodeAction(new QAction(nullptr))
	, mUsbUploadAction(new QAction(nullptr))
	, mWifiUploadAction(new QAction(nullptr))
{
}

IotikRuCGeneratorPlugin::~IotikRuCGeneratorPlugin()
{
}

QList<qReal::ActionInfo> IotikRuCGeneratorPlugin::customActions()
{
	mGenerateCodeAction->setObjectName("generateRuCCode");
	mGenerateCodeAction->setText(tr("Generate RuC code"));
	mGenerateCodeAction->setIcon(QIcon(":/iotik/ruc/images/generateRuCCode.svg"));
	qReal::ActionInfo generateCodeActionInfo(mGenerateCodeAction, "generators", "tools");
	connect(mGenerateCodeAction, SIGNAL(triggered()), this, SLOT(generateCode()), Qt::UniqueConnection);

	mUsbUploadAction->setObjectName("usbUpload");
	mUsbUploadAction->setText(tr("Upload program by USB"));
	mUsbUploadAction->setIcon(QIcon(":/images/usbUpload.svg"));
	qReal::ActionInfo usbUploadActionInfo(mUsbUploadAction, "generators", "tools");
	connect(mUsbUploadAction, SIGNAL(triggered()), this, SLOT(usbUpload()), Qt::UniqueConnection);

	mWifiUploadAction->setObjectName("wifiUpload");
	mWifiUploadAction->setText(tr("Upload program by Wi-Fi"));
	mWifiUploadAction->setIcon(QIcon(":/images/wifiUpload.svg"));
	qReal::ActionInfo wifiUploadActionInfo(mWifiUploadAction, "generators", "tools");
	connect(mWifiUploadAction, SIGNAL(triggered()), this, SLOT(wifiUpload()), Qt::UniqueConnection);

	QList<qReal::ActionInfo> result = {generateCodeActionInfo, usbUploadActionInfo, wifiUploadActionInfo};
	result.append(activateActions());

	return result;
}

QList<qReal::HotKeyActionInfo> IotikRuCGeneratorPlugin::hotKeyActions()
{
	mGenerateCodeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
	mUsbUploadAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
	mWifiUploadAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));

	qReal::HotKeyActionInfo generateCodeInfo("Generator.GenerateRuC", tr("Generate RuC Code"), mGenerateCodeAction);
	qReal::HotKeyActionInfo usbUploadInfo("Generator.UsbUploadRuC", tr("Upload RuC Program by USB"), mUsbUploadAction);
	qReal::HotKeyActionInfo wifiUploadInfo("Generator.WifiUploadRuC", tr("Upload RuC Program by Wi-Fi"), mWifiUploadAction);

	return {generateCodeInfo, usbUploadInfo, wifiUploadInfo};
}

QIcon IotikRuCGeneratorPlugin::iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const
{
	Q_UNUSED(robotModel)

	return QIcon(":/iotik/ruc/images/switch-to-iotik-ruc.svg");
}

generatorBase::MasterGeneratorBase *IotikRuCGeneratorPlugin::masterGenerator()
{
	return new IotikRuCMasterGenerator(*mRepo
			, *mMainWindowInterface->errorReporter()
			, *mParserErrorReporter
			, *mRobotModelManager
			, *mTextLanguage
			, mMainWindowInterface->activeDiagram()
			, generatorName());
}

QString IotikRuCGeneratorPlugin::defaultFilePath(const QString &projectName) const
{
	return QString("ruc/%1/%1.c").arg(projectName);
}

qReal::text::LanguageInfo IotikRuCGeneratorPlugin::language() const
{
	return qReal::text::Languages::c();
}

QString IotikRuCGeneratorPlugin::generatorName() const
{
	return "iotikRuC";
}

void IotikRuCGeneratorPlugin::wifiUpload()
{
	mMainWindowInterface->errorReporter()->addError(tr("Wi-Fi is not released yet"));
}

void IotikRuCGeneratorPlugin::usbUpload()
{
	const QString comPort = SettingsManager::value("IotikPortName").toString();
	const QFileInfo fileInfo = generateCodeForProcessing();
	const QString rootPath = QDir::current().absolutePath();

	configureSensors();
	compileCode(fileInfo);

	QextSerialPort *tty = new QextSerialPort(comPort);
	tty->setBaudRate(BAUD115200);
	tty->setFlowControl(FLOW_OFF);
	tty->setParity(PAR_NONE);
	tty->setDataBits(DATA_8);
	tty->setStopBits(STOP_1);
	tty->setTimeout(0);

	tty->open(QIODevice::WriteOnly | QIODevice::Unbuffered);
	tty->write("cd /flash\n");
	sendFile("sensors", tty);
	sendFile("export", tty);
	tty->write("ruc export sensors\n");
	tty->close();

	QFile::remove(rootPath + "/sensors");
	QFile::remove(rootPath + "/export");
}

void IotikRuCGeneratorPlugin::compileCode(const QFileInfo fileInfo)
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
	}
}

void IotikRuCGeneratorPlugin::configureSensors()
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

void IotikRuCGeneratorPlugin::sendFile(const QString filename, QextSerialPort *tty)
{
	QFile sfile(filename);
	sfile.open(QIODevice::ReadOnly);

	const int block = 32;
	int size = sfile.size();

	QString command = "file_receive " +  QString::number(size) + " " + filename + "\n";
	tty->write(QByteArray::fromStdString(command.toStdString()));
	QThread::msleep(1000);

	while (size > 0) {
		QByteArray data = sfile.read(size > block ? block : size);
		tty->write(data);
		QThread::msleep(25);
		size -= block;
	}

	sfile.close();
}
