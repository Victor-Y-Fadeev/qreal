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

#include "iotikVariablesNormalizer.h"

#include <QRegExp>
#include <QVector>

using namespace iotik::parts;

IotikVariablesNormalizer::IotikVariablesNormalizer(QString &code):
	mCode(code)
{
}

void IotikVariablesNormalizer::normalizeArrays()
{
	const QRegExp definition("[\\w]+(\\s\\*)+\\s[\\w]+;");

	for (const QString name : findExpression(mCode, definition)) {
		normalizeArray(name);
	}
}

const QStringList IotikVariablesNormalizer::findExpression(const QString text, const QRegExp expression)
{
	QStringList list;
	int lastPos = 0;

	while ((lastPos = expression.indexIn(text, lastPos)) != -1){
		lastPos += expression.matchedLength();
		list.append(expression.cap(0));
	}

	return list;
}

const int IotikVariablesNormalizer::countDimension(const QString definition)
{
	int number = 0;
	int lastPos = 0;

	while ((lastPos = definition.indexOf(" *", lastPos)) != -1){
		lastPos += 2;
		number++;
	}

	return number;
}

void IotikVariablesNormalizer::normalizeArray(const QString definition)
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
		mCode.replace(definition, newDefinition + "[];");
		return;
	}

	const QRegExp content(name + "\\s=\\s\\{[^\n]+\\};");
	const QStringList applying = findExpression(mCode, content);

	QVector<int> concrete(dimension - 1);
	for (int i = 0; i < concrete.size(); i++) {
		concrete[i] = 1;
	}

	for (const QString use : applying) {
		updateConcrete(concrete, use);
	}

	for (const QString use : applying) {
		updateUse(concrete, use);
	}


	for (int i = 0; i < concrete.size(); i++) {
		newDefinition += "[" + QString::number(concrete[i]) + "]";
	}

	mCode.replace(definition, newDefinition + "[];");
}

void IotikVariablesNormalizer::updateConcrete(QVector<int> &concrete, QString use)
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

void IotikVariablesNormalizer::updateUse(const QVector<int> concrete, const QString use)
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

	mCode.replace(use, result);
}

const QString IotikVariablesNormalizer::getElement(const QVector<int> concrete, const int current, const QString simple)
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