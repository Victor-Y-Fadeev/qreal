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

#include <kitBase/blocksBase/common/engineCommandBlock.h>

namespace iotik {
namespace blocks {
namespace details {

class IotikEnginesBackwardBlock : public kitBase::blocksBase::common::EngineCommandBlock
{
	Q_OBJECT

public:
	explicit IotikEnginesBackwardBlock(kitBase::robotModel::RobotModelInterface &robotModel);

	void run() override;
};

}
}
}