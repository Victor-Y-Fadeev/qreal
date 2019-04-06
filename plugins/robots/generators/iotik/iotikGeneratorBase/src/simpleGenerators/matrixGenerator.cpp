/* Copyright 2019 QReal Research Group
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

#include "matrixGenerator.h"

#include <generatorBase/generatorCustomizer.h>

using namespace iotik::simple;
using namespace generatorBase::simple;
using namespace qReal;

MatrixGenerator::MatrixGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "sensors/signalForFourParameters.t", QList<Binding *>()
			<< Binding::createStatic("@@DRIVER@@", "MATRIX")
			<< Binding::createConverting("@@PORT@@", "SCL", customizer.factory()->portNameConverter())
			<< Binding::createConverting("@@PORT_2@@", "SDA", customizer.factory()->portNameConverter())

			<< Binding::createStatic("@@PARAM@@"
					, repo.property(id, "Print").toString().compare("false") == 0 ? "'\\0'"
						: "'" + (repo.property(id, "Symbol").toString()[0] == '\'' ||
							repo.property(id, "Symbol").toString()[0] == '"' ? repo.property(id, "Symbol").toString()[1]
							: repo.property(id, "Symbol").toString()[0]) + "'")

			<< Binding::createStaticConverting("@@PARAM_2@@"
					, ColorConverter(repo.property(id, "Color").toString(), repo.property(id, "Intensity").toInt(), 'r')
					, customizer.factory()->stringPropertyConverter(id, "Color"))

			<< Binding::createStaticConverting("@@PARAM_3@@"
					, ColorConverter(repo.property(id, "Color").toString(), repo.property(id, "Intensity").toInt(), 'g')
					, customizer.factory()->stringPropertyConverter(id, "Color"))

			<< Binding::createStaticConverting("@@PARAM_4@@"
					, ColorConverter(repo.property(id, "Color").toString(), repo.property(id, "Intensity").toInt(), 'b')
					, customizer.factory()->stringPropertyConverter(id, "Color"))
			, parent)
{
}

QString MatrixGenerator::ColorConverter(QString color, int intensity, char rgb)
{
	if (color.compare("off") == 0) {
		return "0";
	}

	int value = 0;

	switch (rgb) {
		case 'r':
			if (color.compare("violet") == 0) {
				value = 127;
			} else if (color.compare("green") == 0 || color.compare("turquoise") == 0 || color.compare("blue") == 0) {
				value = 0;
			} else {
				value = 255;
			}
			break;
		case 'g':
			if (color.compare("orange") == 0) {
				value = 127;
			} else if (color.compare("red") == 0 || color.compare("blue") == 0 || color.compare("violet") == 0) {
				value = 0;
			} else {
				value = 255;
			}
			break;
		case 'b':
				if (color.compare("red") == 0 || color.compare("orange") == 0 || color.compare("yellow") == 0
						|| color.compare("green") == 0) {
					value = 0;
				} else {
					value = 255;
				}
			break;
	}

	value *= intensity;
	value /= 100;

	return QString::number(value);
}
