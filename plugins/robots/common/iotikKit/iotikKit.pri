# Copyright 2017 QReal Research Group
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

QT += widgets
QT += network

includes(plugins/robots/common/iotikKit \
		plugins/robots/common/kitBase \
		plugins/robots/utils \
		qrtext \
		thirdparty/qscintilla/Qt4Qt5 \
)

links(qrkernel qrutils qrtext qrgui-preferences-dialog qrgui-tool-plugin-interface \
		robots-utils robots-kit-base qextserialport qslog \
)

HEADERS += \
	$$PWD/include/iotikKit/robotModel/iotikRobotModelBase.h \
	$$PWD/include/iotikKit/blocks/iotikBlocksFactory.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikMotor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikMosfet.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikLed.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikColorSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikAccelerometer.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikCompass.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikGyroscope.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikLineSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikSoilSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikWaterSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikFlowSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikInfraredSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikTemperatureSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikSonarSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikLaserSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikFlameSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikLightSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikHumiditySensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikPressureSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikUltravioletSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikRelay.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikWifi.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikBlynkAuthorization.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikBlynkLed.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikBlynkSend.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikBlynkReceive.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikBlynkNotification.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikBlynkProperty.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikBlynkLCD.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikBlynkTerminal.h \
	$$PWD/include/iotikKit/communication/usbRobotCommunicationThread.h \
	$$PWD/include/iotikKit/communication/wifiRobotCommunicationThread.h \
	$$PWD/src/blocks/details/iotikEnginesBackwardBlock.h \
	$$PWD/src/blocks/details/iotikEnginesForwardBlock.h \
	$$PWD/src/blocks/details/mosfetBlock.h \
	$$PWD/src/blocks/details/ledBlock.h \
	$$PWD/src/blocks/details/soilSensorToVariable.h \
	$$PWD/src/blocks/details/waterSensorToVariable.h \
	$$PWD/src/blocks/details/flowSensorToVariable.h \
	$$PWD/src/blocks/details/waitForTemperatureSensorBlock.h \
	$$PWD/src/blocks/details/colorSensor.h \
	$$PWD/src/blocks/details/accelerometer.h \
	$$PWD/src/blocks/details/compass.h \
	$$PWD/src/blocks/details/gyroscope.h \
	$$PWD/src/blocks/details/lineDetector.h \
	$$PWD/src/blocks/details/flameSensorBlock.h \
	$$PWD/src/blocks/details/soundSensorBlock.h \
	$$PWD/src/blocks/details/laserDistanceBlock.h \
	$$PWD/src/blocks/details/lightSensor.h \
	$$PWD/src/blocks/details/temperature.h \
	$$PWD/src/blocks/details/humidity.h \
	$$PWD/src/blocks/details/pressure.h \
	$$PWD/src/blocks/details/ultraviolet.h \
	$$PWD/src/blocks/details/relay.h \
	$$PWD/src/blocks/details/wifi.h \
	$$PWD/src/blocks/details/blynkAuthorization.h \
	$$PWD/src/blocks/details/blynkLed.h \
	$$PWD/src/blocks/details/blynkSend.h \
	$$PWD/src/blocks/details/blynkReceive.h \
	$$PWD/src/blocks/details/blynkNotification.h \
	$$PWD/src/blocks/details/blynkProperty.h \
	$$PWD/src/blocks/details/blynkLCD.h \
	$$PWD/src/blocks/details/blynkTerminal.h \

SOURCES += \
	$$PWD/src/robotModel/iotikRobotModelBase.cpp \
	$$PWD/src/robotModel/parts/iotikMotor.cpp \
	$$PWD/src/robotModel/parts/iotikMosfet.cpp \
	$$PWD/src/robotModel/parts/iotikLed.cpp \
	$$PWD/src/robotModel/parts/iotikColorSensor.cpp \
	$$PWD/src/robotModel/parts/iotikAccelerometer.cpp \
	$$PWD/src/robotModel/parts/iotikCompass.cpp \
	$$PWD/src/robotModel/parts/iotikGyroscope.cpp \
	$$PWD/src/robotModel/parts/iotikLineSensor.cpp \
	$$PWD/src/robotModel/parts/iotikSoilSensor.cpp \
	$$PWD/src/robotModel/parts/iotikWaterSensor.cpp \
	$$PWD/src/robotModel/parts/iotikFlowSensor.cpp \
	$$PWD/src/robotModel/parts/iotikInfraredSensor.cpp \
	$$PWD/src/robotModel/parts/iotikTemperatureSensor.cpp \
	$$PWD/src/robotModel/parts/iotikSonarSensor.cpp \
	$$PWD/src/robotModel/parts/iotikLaserSensor.cpp \
	$$PWD/src/robotModel/parts/iotikFlameSensor.cpp \
	$$PWD/src/robotModel/parts/iotikLightSensor.cpp \
	$$PWD/src/robotModel/parts/iotikHumiditySensor.cpp \
	$$PWD/src/robotModel/parts/iotikPressureSensor.cpp \
	$$PWD/src/robotModel/parts/iotikUltravioletSensor.cpp \
	$$PWD/src/robotModel/parts/iotikRelay.cpp \
	$$PWD/src/robotModel/parts/iotikWifi.cpp \
	$$PWD/src/robotModel/parts/iotikBlynkAuthorization.cpp \
	$$PWD/src/robotModel/parts/iotikBlynkLed.cpp \
	$$PWD/src/robotModel/parts/iotikBlynkSend.cpp \
	$$PWD/src/robotModel/parts/iotikBlynkReceive.cpp \
	$$PWD/src/robotModel/parts/iotikBlynkNotification.cpp \
	$$PWD/src/robotModel/parts/iotikBlynkProperty.cpp \
	$$PWD/src/robotModel/parts/iotikBlynkLCD.cpp \
	$$PWD/src/robotModel/parts/iotikBlynkTerminal.cpp \
	$$PWD/src/blocks/iotikBlocksFactory.cpp \
	$$PWD/src/blocks/details/iotikEnginesBackwardBlock.cpp \
	$$PWD/src/blocks/details/iotikEnginesForwardBlock.cpp \
	$$PWD/src/blocks/details/mosfetBlock.cpp \
	$$PWD/src/blocks/details/ledBlock.cpp \
	$$PWD/src/blocks/details/soilSensorToVariable.cpp \
	$$PWD/src/blocks/details/waterSensorToVariable.cpp \
	$$PWD/src/blocks/details/flowSensorToVariable.cpp \
	$$PWD/src/blocks/details/waitForTemperatureSensorBlock.cpp \
	$$PWD/src/blocks/details/colorSensor.cpp \
	$$PWD/src/blocks/details/accelerometer.cpp \
	$$PWD/src/blocks/details/compass.cpp \
	$$PWD/src/blocks/details/gyroscope.cpp \
	$$PWD/src/blocks/details/lineDetector.cpp \
	$$PWD/src/blocks/details/flameSensorBlock.cpp \
	$$PWD/src/blocks/details/soundSensorBlock.cpp \
	$$PWD/src/blocks/details/laserDistanceBlock.cpp \
	$$PWD/src/blocks/details/lightSensor.cpp \
	$$PWD/src/blocks/details/temperature.cpp \
	$$PWD/src/blocks/details/humidity.cpp \
	$$PWD/src/blocks/details/pressure.cpp \
	$$PWD/src/blocks/details/ultraviolet.cpp \
	$$PWD/src/blocks/details/relay.cpp \
	$$PWD/src/blocks/details/wifi.cpp \
	$$PWD/src/blocks/details/blynkAuthorization.cpp \
	$$PWD/src/blocks/details/blynkLed.cpp \
	$$PWD/src/blocks/details/blynkSend.cpp \
	$$PWD/src/blocks/details/blynkReceive.cpp \
	$$PWD/src/blocks/details/blynkNotification.cpp \
	$$PWD/src/blocks/details/blynkProperty.cpp \
	$$PWD/src/blocks/details/blynkLCD.cpp \
	$$PWD/src/blocks/details/blynkTerminal.cpp \
	$$PWD/src/communication/usbRobotCommunicationThread.cpp \
	$$PWD/src/communication/wifiRobotCommunicationThread.cpp \


TRANSLATIONS = \
	$$PWD/../../../../qrtranslations/ru/plugins/robots/iotikKit_ru.ts \
	$$PWD/../../../../qrtranslations/fr/plugins/robots/iotikKit_fr.ts \
