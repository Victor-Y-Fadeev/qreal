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
	const QString pathToOutput = targetPath();
	QString resultCode = inputCode(pathToOutput);

	renameThreads(resultCode);
	normalizeArrays(resultCode);

	outputCode(pathToOutput, resultCode);
}

const QString IotikMasterGeneratorBase::inputCode(const QString &path)
{
	QFile file(path);
	file.open(QIODevice::ReadOnly);

	const QString code = file.readAll();

	file.close();
	return code;
}

const QStringList IotikMasterGeneratorBase::findExpression(const QString text, const QRegExp expression)
{
	QStringList list;
	int lastPos = 0;

	while ((lastPos = expression.indexIn(text, lastPos)) != -1){
		lastPos += expression.matchedLength();
		list.append(expression.cap(0));
	}

	return list;
}

void IotikMasterGeneratorBase::renameThreads(QString &code)
{
	const QString threadName = "thread_";
	const QRegExp definition("[\\w]{32,32},\\s[\\w]+");

	QStringList parts;
	int index = 1;

	for (const QString name : findExpression(code, definition)) {
		parts = name.split(", ");
		code.replace(name, threadName + QString::number(index) + ", 0");
		code.replace(parts.at(0), threadName + QString::number(index));
		code.replace(parts.at(1), QString::number(index));
		index++;
	}

	code.replace("(main)", "(0)");
}

void IotikMasterGeneratorBase::normalizeArrays(QString &code)
{
	const QRegExp definition("[\\w]+(\\s\\*)+\\s[\\w]+;");

	for (const QString name : findExpression(code, definition)) {
		normalizeArray(code, name);
	}
}

const int IotikMasterGeneratorBase::countDimension(const QString definition)
{
	int number = 0;
	int lastPos = 0;

	while ((lastPos = definition.indexOf(" *", lastPos)) != -1){
		lastPos += 2;
		number++;
	}

	return number;
}

void IotikMasterGeneratorBase::normalizeArray(QString &code, const QString definition)
{
	const int dimension = countDimension(definition);

	const QRegExp findType("[\\w]+");
	findType.indexIn(definition);
	QString type = findType.cap(0);

	QString name = definition;
	name.replace(QRegExp("[\\w]+(\\s\\*)+\\s"), "");
	name.replace(";", "");

	QString newDefinition = type + " " + name;

	if (dimension == 1) {
		code.replace(definition, newDefinition + "[];");
		return;
	}

	const QRegExp content(name + "\\s=\\s\\{[^\n]+\\};");
	const QStringList applying = findExpression(code, content);

	QVector<int> concrete(dimension - 1);
	for (int i = 0; i < concrete.size(); i++) {
		concrete[i] = 1;
	}

	for (const QString use : applying) {
		updateConcrete(concrete, use);
	}

	for (const QString use : applying) {
		updateUse(code, concrete, use);
	}


	for (int i = 0; i < concrete.size(); i++) {
		newDefinition += "[" + QString::number(concrete[i]) + "]";
	}
	code.replace(definition, newDefinition + "[];");
}

void IotikMasterGeneratorBase::updateConcrete(QVector<int> &concrete, QString use)
{
	use.replace(QRegExp("\\{\\s[\\d\\.]+(,\\s[\\d\\.]+)*\\s\\}"), "");
	use.replace(QRegExp("\"[^\"]*\""), "");

	QVector<int> temp(concrete.size());
	int current = -1;
	for (int i = 0; i < use.length(); i++) {
		if (use[i] == '{') {
			current++;
			temp[current] = 1;
		} else if (use[i] == ',') {
			temp[current]++;
		} else if (use[i] == '}') {
			if (temp[current] > concrete[current]) {
				concrete[current] = temp[current];
			}
			current--;
		}
	}
}

void IotikMasterGeneratorBase::updateUse(QString &code, const QVector<int> concrete, const QString use)
{
	const QString simple = use.contains("\"") ? "\"\"" : "{ 0 }";
	QString result = "";

	QVector<int> temp(concrete.size());
	int current = -1;
	for (int i = 0; i < use.length(); i++) {
		if (use[i] == '"') {
			result += use[i];
			i++;

			while (use[i] != '"') {
				result += use[i];
				i++;
			}
		} else if (use[i] == '{') {
			if (current == concrete.size() - 1) {
				while (use[i] != '}') {
					result += use[i];
					i++;
				}
			} else {
				current++;
				temp[current] = concrete[current];
			}
		} else if (use[i] == ',') {
			temp[current]--;
		} else if ((i < use.length() - 1) && (use[i + 1] == '}')) {
			if (temp[current] != 1) {
				const QString element = getElement(concrete, current, simple);
				for (int j = temp[current]; j > 1; j--) {
					result += ", " + element;
				}
			}
			current--;
		}

		result += use[i];
	}

	code.replace(use, result);
}

const QString IotikMasterGeneratorBase::getElement(const QVector<int> concrete, const int current, const QString simple)
{
	if (current == concrete.size() - 1) {
		return simple;
	}

	const QString element = getElement(concrete, current + 1, simple);
	QString result = "{ ";

	result += element;
	for (int i = 1; i < concrete[current + 1]; i++) {
		result += ", " + element;
	}

	return result + " }";
}
