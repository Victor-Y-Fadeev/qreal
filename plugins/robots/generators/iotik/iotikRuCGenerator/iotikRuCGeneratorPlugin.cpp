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

#include "iotikRuCGeneratorPlugin.h"

#include <QtWidgets/QApplication>
#include <QtCore/QDir>

#include "iotikRuCMasterGenerator.h"

using namespace iotik::ruc;

IotikRuCGeneratorPlugin::IotikRuCGeneratorPlugin()
	: IotikGeneratorPluginBase("IotikRuCGeneratorRobotModel", tr("Generation (RuC)"), 7 /* Last order */)
	, mGenerateCodeAction(new QAction(nullptr))
{
	mGenerateCodeAction->setText(tr("Generate to RuC"));
	mGenerateCodeAction->setIcon(QIcon(":/iotik/ruc/images/generateRuCCode.svg"));
	mGenerateCodeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_G));
	connect(mGenerateCodeAction, SIGNAL(triggered()), this, SLOT(generateCode()));
}

QList<qReal::ActionInfo> IotikRuCGeneratorPlugin::customActions()
{
	return { qReal::ActionInfo(mGenerateCodeAction, "generators", "tools") };
}

QList<qReal::HotKeyActionInfo> IotikRuCGeneratorPlugin::hotKeyActions()
{
	return { qReal::HotKeyActionInfo("Generator.GenerateIotikRuC"
			, tr("Generate RuC Code"), mGenerateCodeAction) };
}

QIcon IotikRuCGeneratorPlugin::iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const
{
	Q_UNUSED(robotModel)
	return QIcon(":/iotik/ruc/images/switch-to-iotik-ruc.svg");
}

QString IotikRuCGeneratorPlugin::defaultFilePath(const QString &projectName) const
{
	return QString("ruc/%1/%1.c").arg(projectName);
}

qReal::text::LanguageInfo IotikRuCGeneratorPlugin::language() const
{
	return qReal::text::Languages::c();
}

QString IotikRuCGeneratorPlugin::generatorName() const
{
	return "iotikRuC";
}

generatorBase::MasterGeneratorBase *IotikRuCGeneratorPlugin::masterGenerator()
{
	return new IotikRuCMasterGenerator(*mRepo
			, *mMainWindowInterface->errorReporter()
			, *mParserErrorReporter
			, *mRobotModelManager
			, *mTextLanguage
			, mMainWindowInterface->activeDiagram()
			, generatorName());
}