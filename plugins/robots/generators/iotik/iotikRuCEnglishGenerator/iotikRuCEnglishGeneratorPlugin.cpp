/* Copyright 2007-2015 QReal Research Group
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

#include "iotikRuCEnglishGeneratorPlugin.h"

#include <iotikKit/blocks/iotikBlocksFactory.h>
#include <src/robotModel/iotikGeneratorRobotModel.h>

using namespace iotik;
using namespace iotik::ruc;
using namespace kitBase::robotModel;

IotikRuCEnglishGeneratorPlugin::IotikRuCEnglishGeneratorPlugin()
	: IotikRuCGeneratorPluginBase(new robotModel::IotikGeneratorRobotModel(
					"iotikKit"
					, "iotikKitRobot"
					, "IotikRuCEnglishGeneratorRobotModel"
					, tr("Generation (RuC) (English)")
					, 9 /* After 2D model */)
			, new blocks::IotikBlocksFactory()
			, {":/iotikRuC/templates_english"})
	, mModel(static_cast<robotModel::IotikGeneratorRobotModel *>(robotModels().first()))
{
}

QString IotikRuCEnglishGeneratorPlugin::kitId() const
{
	return "iotikKit";
}
