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

#include <QtCore/QMetaClassInfo>

namespace iotik {
namespace parts {

class IotikVariablesNormalizer
{
public:
	IotikVariablesNormalizer(QString &code);

	void normalizeArrays();

private:
	const QStringList findExpression(const QString text, const QRegExp expression);
	int countDimension(const QString definition);
	const QString getElement(const QVector<int> concrete, const int current, const QString simple);

	void normalizeArray(const QString definition);

	void updateConcrete(QVector<int> &concrete, QString use);
	void updateUse(const QVector<int> concrete, const QString use);

	QString &mCode;
};

}
}
