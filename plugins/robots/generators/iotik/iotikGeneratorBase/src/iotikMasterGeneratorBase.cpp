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

#include <QtCore/QFile>
#include <QRegExp>

#include "iotikGeneratorBase/iotikMasterGeneratorBase.h"
#include "iotikGeneratorCustomizer.h"

using namespace iotik;

IotikMasterGeneratorBase::IotikMasterGeneratorBase(const qrRepo::RepoApi &repo
		, qReal::ErrorReporterInterface &errorReporter
		, const utils::ParserErrorReporter &parserErrorReporter
		, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
		, qrtext::LanguageToolboxInterface &textLanguage
		, const qReal::Id &diagramId
		, const QStringList &pathsToTemplates)
	: MasterGeneratorBase(repo, errorReporter, robotModelManager, textLanguage, parserErrorReporter, diagramId)
	, mPathsToTemplates(pathsToTemplates)
{
}

generatorBase::GeneratorCustomizer *IotikMasterGeneratorBase::createCustomizer()
{
	return new IotikGeneratorCustomizer(mRepo, mErrorReporter
			, mRobotModelManager, *createLuaProcessor(), mPathsToTemplates);
}

void IotikMasterGeneratorBase::afterGeneration()
{
	QFile file(targetPath());
	file.open(QIODevice::ReadOnly);
	QString resultCode = file.readAll();
	file.close();

	renameThreads(resultCode);

	file.open(QIODevice::WriteOnly);
	file.write(QByteArray::fromStdString(resultCode.toStdString()));
	file.close();
}

void IotikMasterGeneratorBase::renameThreads(QString &code)
{
	const QString threadName = "thread_";
	QRegExp definition("[\\w]{32,32},\\s[\\w]+");

	QString string;
	QStringList list;
	int index = 1;

	while (definition.indexIn(code) != -1) {
		string = definition.cap(0);
		list = string.split(", ");
		code.replace(string, threadName + QString::number(index) + ", 0");
		code.replace(list.at(0), threadName + QString::number(index));
		code.replace(list.at(1), QString::number(index));
		index++;
	}

	code.replace("(main)", "(0)");
}
