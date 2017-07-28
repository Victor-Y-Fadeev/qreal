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

#include "iotikRuCMasterGenerator.h"
#include "iotikRuCGeneratorDefs.h"

using namespace iotik::ruc;

IotikRuCGeneratorPlugin::IotikRuCGeneratorPlugin()
	: IotikGeneratorPluginBase("IotikRuCGeneratorRobotModel", tr("Generation (RuC)"), 7 /* Last order */)
	, mGenerateCodeAction(new QAction(nullptr))
	, mUploadProgramAction(new QAction(nullptr))
{
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

void IotikRuCGeneratorPlugin::uploadProgram()
{
	const QFileInfo fileInfo = generateCodeForProcessing();
	//const QString rootPath = QDir::current().absolutePath();
	const QString dirPath = fileInfo.absolutePath();

	compileCode(fileInfo);
	configureSensors(fileInfo);

	QProcess::execute(PYTHON , {dirPath + "/file_send.py", "-d", "COM4"});
	mMainWindowInterface->errorReporter()->addError(PYTHON);
	mMainWindowInterface->errorReporter()->addError(dirPath + "/file_send.py " + "-d " + " COM4");//tr("Code uploading failed, aborting"));

	//QFile::remove(dirPath + "/file_send.py");
	//QFile::remove(dirPath + "/export");
	//QFile::remove(dirPath + "/sensors");
}

void IotikRuCGeneratorPlugin::compileCode(const QFileInfo fileInfo)
{
	const QString rootPath = QDir::current().absolutePath();
	const QString filePath = fileInfo.absoluteFilePath();
	const QString dirPath = fileInfo.absolutePath();


	if (QFile::exists(RUC_COMPILER)) {
		QProcess::execute(RUC_COMPILER, {filePath});
	} else {
		QProcess::execute(RUC_DEBUG_COMPILER, {filePath});
	}

	QFile::remove(rootPath + "/tree.txt");
	QFile::remove(rootPath + "/codes.txt");

	if (QFile::exists(rootPath + "/export.txt")) {
		QFile::rename(rootPath + "/export.txt", dirPath + "/export");
	} else {
		mMainWindowInterface->errorReporter()->addError(tr("Code compiling failed, aborting"));//tr("Code uploading failed, aborting"));
	}
}

void IotikRuCGeneratorPlugin::configureSensors(const QFileInfo fileInfo)
{
	const QString rootPath = QDir::current().absolutePath();
	const QString dirPath = fileInfo.absolutePath();


	QFile sensors(dirPath + "/sensors");
	sensors.open(QIODevice::WriteOnly);
	QTextStream out(&sensors);

	out << "servos 5 12 4 13\n";
	out << "digital 1\n";
	out << "0 1 14 15\n";
	out << "analog 1\n";
	out << "0 1\n";

	sensors.close();

	QFile::copy(rootPath + "/file_send.py", dirPath + "/file_send.py");
}
