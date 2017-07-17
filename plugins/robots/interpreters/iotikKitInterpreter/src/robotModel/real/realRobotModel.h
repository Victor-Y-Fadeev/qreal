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

#include <iotikKit/robotModel/iotikRobotModelBase.h>

namespace iotik {
namespace robotModel {
namespace real {

class RealRobotModel : public IotikRobotModelBase
{
    Q_OBJECT

public:
    /// Takes ownership on communication thread
    RealRobotModel(const QString &kitId, const QString &robotId);

    QString name() const override;
    QString friendlyName() const override;
    bool needsConnection() const override;
    int priority() const override;

signals:
    /// Emitted when communicator throws an error to be displayed with error reporter.
    void errorOccured(const QString &text);

    /// Emitted when communicator wants to display user some informational message.
    void messageArrived(const QString &text);

private:
    kitBase::robotModel::robotParts::Device *createDevice(
            const kitBase::robotModel::PortInfo &port
            , const kitBase::robotModel::DeviceInfo &deviceInfo) override;

};

}
}
}
