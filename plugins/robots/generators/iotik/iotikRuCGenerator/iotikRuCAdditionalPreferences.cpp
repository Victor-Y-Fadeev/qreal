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

#include "iotikRuCAdditionalPreferences.h"
#include "ui_iotikRuCAdditionalPreferences.h"

#include <qrkernel/settingsManager.h>
#include <../utils/include/utils/widgets/comPortPicker.h>

using namespace iotik;
using namespace qReal;

IotikAdditionalPreferences::IotikAdditionalPreferences(const QString &realRobotName, QWidget *parent)
	: AdditionalPreferences(parent)
	, mUi(new Ui::IotikAdditionalPreferences)
	, mRealRobotName(realRobotName)
{
	mUi->setupUi(this);
	mUi->robotImagePicker->configure("iotikRobot2DImage", tr("2D robot image:"));
	connect(mUi->manualComPortCheckbox, &QCheckBox::toggled
			, this, &IotikAdditionalPreferences::manualComPortCheckboxChecked);
}

IotikAdditionalPreferences::~IotikAdditionalPreferences()
{
	delete mUi;
}

void IotikAdditionalPreferences::save()
{
	SettingsManager::setValue("IotikPortName", selectedPortName());
	SettingsManager::setValue("IotikManualComPortCheckboxChecked", mUi->manualComPortCheckbox->isChecked());
	mUi->robotImagePicker->save();
	emit settingsChanged();
}

void IotikAdditionalPreferences::restoreSettings()
{
	ui::ComPortPicker::populate(*mUi->comPortComboBox, "IotikPortName");
	mUi->robotImagePicker->restore();

	if (mUi->comPortComboBox->count() == 0) {
		mUi->comPortComboBox->hide();
		mUi->comPortLabel->hide();
		mUi->manualComPortCheckbox->hide();
		mUi->noComPortsFoundLabel->show();
		mUi->directInputComPortLabel->show();
		mUi->directInputComPortLineEdit->show();
		mUi->directInputComPortLineEdit->setText(SettingsManager::value("IotikPortName").toString());
	} else {
		mUi->comPortComboBox->show();
		mUi->comPortLabel->show();
		mUi->manualComPortCheckbox->show();
		mUi->directInputComPortLabel->hide();
		mUi->directInputComPortLineEdit->hide();
		mUi->noComPortsFoundLabel->hide();
		mUi->manualComPortCheckbox->setChecked(false);
		mUi->manualComPortCheckbox->setChecked(SettingsManager::value("IotikManualComPortCheckboxChecked").toBool());
	}
}

void IotikAdditionalPreferences::onRobotModelChanged(kitBase::robotModel::RobotModelInterface * const robotModel)
{
	mUi->usbSettingsGroupBox->setVisible(robotModel->name() == mRealRobotName);
}

void IotikAdditionalPreferences::manualComPortCheckboxChecked(bool state)
{
	const QString defaultPortName = SettingsManager::value("IotikPortName").toString();

	if (state) {
		mUi->comPortComboBox->hide();
		mUi->comPortLabel->hide();
		mUi->directInputComPortLabel->show();
		mUi->directInputComPortLineEdit->show();
		mUi->directInputComPortLineEdit->setText(defaultPortName);
	} else {
		mUi->comPortComboBox->show();
		mUi->comPortLabel->show();
		mUi->directInputComPortLabel->hide();
		mUi->directInputComPortLineEdit->hide();
		mUi->noComPortsFoundLabel->hide();
	}
}

QString IotikAdditionalPreferences::selectedPortName() const
{
	return mUi->comPortComboBox->isVisible()
			? mUi->comPortComboBox->currentText()
			: mUi->directInputComPortLineEdit->text();
}
