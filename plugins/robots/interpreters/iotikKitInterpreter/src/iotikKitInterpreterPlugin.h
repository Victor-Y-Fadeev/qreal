/* Copyright 2017 QReal Research group
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

#include <kitBase/kitPluginInterface.h>
#include <iotikKit/blocks/iotikBlocksFactory.h>

#include "robotModel/real/RealRobotModel.h"

namespace iotik {

class IotikKitInterpreterPlugin : public QObject, public kitBase::KitPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(kitBase::KitPluginInterface)
    Q_PLUGIN_METADATA(IID "iotik.IotikKitInterpreterPlugin")

public:
    IotikKitInterpreterPlugin();
    ~IotikKitInterpreterPlugin() override;

    void init(const kitBase::KitPluginConfigurator &configurator) override;

    QString kitId() const override;
    QString friendlyKitName() const override;

    QList<kitBase::robotModel::RobotModelInterface *> robotModels() override;
    kitBase::robotModel::RobotModelInterface *defaultRobotModel() override;

    kitBase::blocksBase::BlocksFactoryInterface *blocksFactoryFor(
            const kitBase::robotModel::RobotModelInterface *model) override;

    QList<qReal::ActionInfo> customActions() override;  // Transfers ownership of embedded QActions
    QList<qReal::HotKeyActionInfo> hotKeyActions() override;
    QString defaultSettingsFile() const override;

    QWidget *quickPreferencesFor(const kitBase::robotModel::RobotModelInterface &model) override;
    QIcon iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const override;

private:
    robotModel::real::RealRobotModel mRealRobotModel;

    /// @todo Use shared pointers instead of this sh~.
    blocks::IotikBlocksFactoryBase *mBlocksFactory = nullptr;  // Transfers ownership
    bool mOwnsBlocksFactory = true;

};

}
