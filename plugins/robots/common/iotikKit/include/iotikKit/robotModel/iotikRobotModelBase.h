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

#include <qrgui/plugins/toolPluginInterface/usedInterfaces/errorReporterInterface.h>
#include <kitBase/robotModel/commonRobotModel.h>

namespace iotik {
namespace robotModel {

class IotikRobotModelBase : public kitBase::robotModel::CommonRobotModel
{
    Q_OBJECT

public:
    IotikRobotModelBase(const QString &kitId, const QString &robotId);

    QList<kitBase::robotModel::PortInfo> configurablePorts() const override;
    QList<kitBase::robotModel::DeviceInfo> convertibleBases() const override;

    QHash<QString, int> buttonCodes() const override;

    /// Registers error reporter in a model.
    virtual void setErrorReporter(qReal::ErrorReporterInterface &errorReporter) = 0;

    /// Returns config file version that shall be on a robot to be able to use this model.
    virtual QString robotConfigFileVersion() const = 0;

protected:

};

}
}
