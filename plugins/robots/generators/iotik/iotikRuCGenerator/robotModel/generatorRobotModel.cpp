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

#include "generatorRobotModel.h"

using namespace iotik::robotModel;

GeneratorRobotModel::GeneratorRobotModel(const QString &kitId
		, const QString &robotId)
	: IotikRobotModelBase(kitId, robotId)
{
}

QString GeneratorRobotModel::name() const
{
	return "generatorRobotModel";
}

QString GeneratorRobotModel::friendlyName() const
{
	return tr("Generation (RuC)");
}

bool GeneratorRobotModel::needsConnection() const
{
	return false;
}

bool GeneratorRobotModel::interpretedModel() const
{
	return false;
}

int GeneratorRobotModel::priority() const
{
	return 0;
}
