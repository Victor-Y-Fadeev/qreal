#pragma once

#include "waitForSensorBlock.h"

namespace interpreterBase {
namespace blocksBase {
namespace common {

class ROBOTS_INTERPRETER_BASE_EXPORT WaitForGyroscopeSensorBlock : public WaitForSensorBlock
{
	Q_OBJECT

public:
	explicit WaitForGyroscopeSensorBlock(interpreterBase::robotModel::RobotModelInterface &robotModel);
	~WaitForGyroscopeSensorBlock() override;

protected slots:
	void responseSlot(int reading) override;

protected:
	interpreterBase::robotModel::DeviceInfo device() const override;
};
}
}
}