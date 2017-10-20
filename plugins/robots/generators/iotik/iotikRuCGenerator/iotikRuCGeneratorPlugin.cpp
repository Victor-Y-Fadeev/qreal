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
#include <utils/widgets/comPortPicker.h>

#include <plugins/robots/thirdparty/qextserialport/src/qextserialport.h>

#include "iotikRuCMasterGenerator.h"
#include "iotikRuCGeneratorDefs.h"

using namespace iotik::ruc;
using namespace qReal;

const Id robotDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "RobotsDiagramNode");
const Id subprogramDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "SubprogramDiagram");

IotikRuCGeneratorPlugin::IotikRuCGeneratorPlugin()
	: IotikGeneratorPluginBase("IotikRuCGeneratorRobotModel", tr("Generation (RuC)"), 7 /* Last order */)
	, mRobotModel(kitId(), "iotikGeneratorRobot", "iotikGeneratorRobot", tr("Generation (RuC)"), 0)
	, mGenerateCodeAction(new QAction(nullptr))
	, mUploadProgramAction(new QAction(nullptr))
{
	mAdditionalPreferences = new IotikAdditionalPreferences(mRobotModel.name());

	connect(mAdditionalPreferences, &IotikAdditionalPreferences::settingsChanged
			, &mRobotModel, &iotik::robotModel::IotikGeneratorRobotModel::rereadSettings);
}

IotikRuCGeneratorPlugin::~IotikRuCGeneratorPlugin()
{
	if (mOwnsAdditionalPreferences) {
		delete mAdditionalPreferences;
	}
}

QList<qReal::ActionInfo> IotikRuCGeneratorPlugin::customActions()
{
	mGenerateCodeAction->setObjectName("generateRuCCode");
	mGenerateCodeAction->setText(tr("Generate RuC code"));
	mGenerateCodeAction->setIcon(QIcon(":/iotik/ruc/images/generateRuCCode.svg"));
	qReal::ActionInfo generateCodeActionInfo(mGenerateCodeAction, "generators", "tools");
	connect(mGenerateCodeAction, SIGNAL(triggered()), this, SLOT(generateCode()), Qt::UniqueConnection);

	mUploadProgramAction->setObjectName("uploadProgram");
	mUploadProgramAction->setText(tr("Upload program"));
	mUploadProgramAction->setIcon(QIcon(":/iotik/ruc/images/uploadProgram.svg"));
	qReal::ActionInfo uploadProgramActionInfo(mUploadProgramAction, "generators", "tools");
	connect(mUploadProgramAction, SIGNAL(triggered()), this, SLOT(uploadProgram()), Qt::UniqueConnection);

	return {generateCodeActionInfo, uploadProgramActionInfo};
}

QList<qReal::HotKeyActionInfo> IotikRuCGeneratorPlugin::hotKeyActions()
{
	mGenerateCodeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
	mUploadProgramAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));

	qReal::HotKeyActionInfo generateCodeInfo("Generator.GenerateRuC", tr("Generate RuC Code"), mGenerateCodeAction);
	qReal::HotKeyActionInfo uploadProgramInfo("Generator.UploadRuC", tr("Upload RuC Program"), mUploadProgramAction);

	return {generateCodeInfo, uploadProgramInfo};
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

QList<kitBase::robotModel::RobotModelInterface *> IotikRuCGeneratorPlugin::robotModels()
{
	return {&mRobotModel};
}

kitBase::robotModel::RobotModelInterface *IotikRuCGeneratorPlugin::defaultRobotModel()
{
	return &mRobotModel;
}

QList<kitBase::AdditionalPreferences *> IotikRuCGeneratorPlugin::settingsWidgets()
{
	mOwnsAdditionalPreferences = false;
	return {mAdditionalPreferences};
}

QWidget *IotikRuCGeneratorPlugin::quickPreferencesFor(const kitBase::robotModel::RobotModelInterface &model)
{
	return producePortConfigurer();
}

QWidget *IotikRuCGeneratorPlugin::producePortConfigurer()
{
	QWidget * const result = new ui::ComPortPicker("IotikPortName", this);
	connect(this, &QObject::destroyed, [result]() { delete result; });
	return result;
}

void IotikRuCGeneratorPlugin::uploadProgram()
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
