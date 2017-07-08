/* Copyright 2013-2016 CyberTech Labs Ltd.
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

#include "iotikKitInterpreterPlugin.h"

#include <QtWidgets/QApplication>

#include <utils/widgets/comPortPicker.h>

using namespace iotik;
using namespace qReal;

const Id robotDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "RobotsDiagramNode");
const Id subprogramDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "SubprogramDiagram");

IotikKitInterpreterPlugin::IotikKitInterpreterPlugin()
    : mRealRobotModel(kitId(), "iotikKitRobot" ) // todo: somewhere generate robotId for each robot
 //   , mBlocksFactory(new blocks::IotikBlocksFactoryBase)
{

}

IotikKitInterpreterPlugin::~IotikKitInterpreterPlugin()
{
    if (mOwnsBlocksFactory) {
        delete mBlocksFactory;
    }
}

void IotikKitInterpreterPlugin::init(const kitBase::KitPluginConfigurator &configurator)
{

    qReal::gui::MainWindowInterpretersInterface &interpretersInterface
            = configurator.qRealConfigurator().mainWindowInterpretersInterface();
    connect(&mRealRobotModel, &robotModel::real::RealRobotModel::errorOccured
            , [&interpretersInterface](const QString &message) {
                interpretersInterface.errorReporter()->addError(message);
    });
    connect(&mRealRobotModel, &robotModel::real::RealRobotModel::messageArrived
            , [&interpretersInterface](const QString &message) {
                interpretersInterface.errorReporter()->addInformation(message);
    });

}

QString IotikKitInterpreterPlugin::kitId() const
{
    return "iotikKit";
}

QString IotikKitInterpreterPlugin::friendlyKitName() const
{
    return tr("Iotik");
}

QList<kitBase::robotModel::RobotModelInterface *> IotikKitInterpreterPlugin::robotModels()
{
    return {&mRealRobotModel};
}

kitBase::blocksBase::BlocksFactoryInterface *IotikKitInterpreterPlugin::blocksFactoryFor(
        const kitBase::robotModel::RobotModelInterface *model)
{
    Q_UNUSED(model);
    mOwnsBlocksFactory = false;
    return mBlocksFactory;
}

kitBase::robotModel::RobotModelInterface *IotikKitInterpreterPlugin::defaultRobotModel()
{
    return &mRealRobotModel;
}

QWidget *IotikKitInterpreterPlugin::quickPreferencesFor(const kitBase::robotModel::RobotModelInterface &model)
{
    return nullptr;
}

QList<qReal::ActionInfo> IotikKitInterpreterPlugin::customActions()
{
    return {};
}

QList<HotKeyActionInfo> IotikKitInterpreterPlugin::hotKeyActions()
{
    return {};
}

QString IotikKitInterpreterPlugin::defaultSettingsFile() const
{
    return ":/iotikDefaultSettings.ini";
}

QIcon IotikKitInterpreterPlugin::iconForFastSelector(
        const kitBase::robotModel::RobotModelInterface &robotModel) const
{
    return QIcon();
}
