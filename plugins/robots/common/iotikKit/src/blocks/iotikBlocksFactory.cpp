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

#include "iotikKit/blocks/iotikBlocksFactory.h"
#include "iotikKit/robotModel/parts/iotikInfraredSensor.h"
#include "iotikKit/robotModel/parts/iotikSonarSensor.h"

#include <kitBase/robotModel/robotParts/rangeSensor.h>
#include <kitBase/blocksBase/common/enginesStopBlock.h>
#include <kitBase/blocksBase/common/waitForSonarDistanceBlock.h>



#include <qrutils/interpreter/blocks/emptyBlock.h>

#include "details/iotikEnginesBackwardBlock.h"
#include "details/iotikEnginesForwardBlock.h"


using namespace iotik::blocks;
using namespace iotik::blocks::details;
using namespace kitBase::blocksBase::common;

qReal::interpretation::Block *IotikBlocksFactory::produceBlock(const qReal::Id &element)
{
	if (elementMetatypeIs(element, "IotikEnginesForward")) {
		return new details::IotikEnginesForwardBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikEnginesBackward")) {
		return new details::IotikEnginesBackwardBlock(mRobotModelManager->model());
	} else if (elementMetatypeIs(element, "IotikEnginesStop")) {
		return new EnginesStopBlock(mRobotModelManager->model());

	} else if (elementMetatypeIs(element, "IotikWaitForIRDistance")) {
		return new WaitForSonarDistanceBlock(mRobotModelManager->model()
				, kitBase::robotModel::DeviceInfo::create<robotModel::parts::IotikInfraredSensor>());
	} else if (elementMetatypeIs(element, "IotikWaitForSonarDistance")) {
		return new WaitForSonarDistanceBlock(mRobotModelManager->model()
				, kitBase::robotModel::DeviceInfo::create<robotModel::parts::IotikSonarSensor>());
	}

	return nullptr;
}

qReal::IdList IotikBlocksFactory::providedBlocks() const
{
	return {
				id("IotikEnginesBackward")
				, id("IotikEnginesForward")
				, id("IotikEnginesStop")

				, id("IotikWaitForIRDistance")
				, id("TrikWaitForSonarDistance")
	};
}

qReal::IdList IotikBlocksFactory::blocksToDisable() const
{
	return {};
}

qReal::IdList IotikBlocksFactory::blocksToHide() const
{
	return {
				id("Function")
				, id("IfBlock")
				, id("FiBlock")
				, id("SwitchBlock")
				, id("Loop")
				, id("Subprogram")
				, id("Fork")
				, id("Join")
				, id("KillThread")
				, id("VariableInit")
				, id("Randomizer")

				, id("SendMessageThreads")

				, id("ReceiveMessageThreads")

				, id("PrintText")
				, id("ClearScreen")
				, id("MarkerDown")
				, id("MarkerUp")
	};
}
