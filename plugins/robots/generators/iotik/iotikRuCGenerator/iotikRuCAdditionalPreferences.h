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

#include <kitBase/additionalPreferences.h>

namespace Ui {
class IotikAdditionalPreferences;
}

namespace iotik {

class IotikAdditionalPreferences : public kitBase::AdditionalPreferences
{
	Q_OBJECT

public:
	explicit IotikAdditionalPreferences(const QString &realRobotName, QWidget *parent = 0);
	~IotikAdditionalPreferences();

	void save() override;
	void restoreSettings() override;
	void onRobotModelChanged(kitBase::robotModel::RobotModelInterface * const robotModel) override;

signals:
	void settingsChanged();

private slots:
	void manualComPortCheckboxChecked(bool state);

private:
	QString selectedPortName() const;

	Ui::IotikAdditionalPreferences *mUi;
	const QString mRobotName;
};

}
