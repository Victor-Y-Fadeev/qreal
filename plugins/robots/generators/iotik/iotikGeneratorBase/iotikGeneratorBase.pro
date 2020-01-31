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

TARGET = robots-iotik-generator-base

include(../../../../../global.pri)

QT += widgets

TEMPLATE = lib

includes(plugins/robots/generators/generatorBase \
		plugins/robots/common/kitBase \
		plugins/robots/common/iotikKit \
		plugins/robots/utils \
		qrtext \
		thirdparty/qscintilla/Qt4Qt5 \
)

links(qrkernel qslog qrutils qrrepo robots-generator-base robots-iotik-kit robots-kit-base \
		qrgui-preferences-dialog robots-utils \
)

DEFINES += ROBOTS_IOTIK_GENERATOR_BASE_LIBRARY

TRANSLATIONS = \
	$$PWD/../../../../../qrtranslations/ru/plugins/robots/iotikGeneratorBase_ru.ts \
	$$PWD/../../../../../qrtranslations/fr/plugins/robots/iotikGeneratorBase_fr.ts \

HEADERS += \
	$$PWD/include/iotikGeneratorBase/iotikGeneratorBaseDeclSpec.h \
	$$PWD/include/iotikGeneratorBase/iotikGeneratorPluginBase.h \
	$$PWD/include/iotikGeneratorBase/iotikMasterGeneratorBase.h \
	$$PWD/src/iotikGeneratorCustomizer.h \
	$$PWD/src/iotikGeneratorFactory.h \
	$$PWD/src/parts/iotikVariablesNormalizer.h \
	$$PWD/src/robotModel/iotikGeneratorRobotModel.h \
	$$PWD/src/simpleGenerators/iotikEnginesGenerator.h \
	$$PWD/src/simpleGenerators/mosfetGenerator.h \
	$$PWD/src/simpleGenerators/ledGenerator.h \
	$$PWD/src/simpleGenerators/soilSensorToVariableGenerator.h \
	$$PWD/src/simpleGenerators/waterSensorToVariableGenerator.h \
	$$PWD/src/simpleGenerators/flowSensorToVariableGenerator.h \
	$$PWD/src/simpleGenerators/waitForTouchSensorGenerator.h \
	$$PWD/src/simpleGenerators/waitForInfraredSensorGenerator.h \
	$$PWD/src/simpleGenerators/waitForTemperatureSensorGenerator.h \
	$$PWD/src/simpleGenerators/waitForUltrasonicSensorGenerator.h \
	$$PWD/src/simpleGenerators/colorSensorGenerator.h \
	$$PWD/src/simpleGenerators/accelerometerGenerator.h \
	$$PWD/src/simpleGenerators/compassGenerator.h \
	$$PWD/src/simpleGenerators/gyroscopeGenerator.h \
	$$PWD/src/simpleGenerators/lineDetectorGenerator.h \
	$$PWD/src/simpleGenerators/laserSensorGenerator.h \
	$$PWD/src/simpleGenerators/flameSensorGenerator.h \
	$$PWD/src/simpleGenerators/soundSensorGenerator.h \
	$$PWD/src/simpleGenerators/heatingSensorGenerator.h \
	$$PWD/src/simpleGenerators/humiditySensorGenerator.h \
	$$PWD/src/simpleGenerators/pressureSensorGenerator.h \
	$$PWD/src/simpleGenerators/lightSensorGenerator.h \
	$$PWD/src/simpleGenerators/ultravioletGenerator.h \
	$$PWD/src/simpleGenerators/capacitiveGenerator.h \
	$$PWD/src/simpleGenerators/matrixGenerator.h \
	$$PWD/src/simpleGenerators/rgbGenerator.h \
	$$PWD/src/simpleGenerators/relayGenerator.h \
	$$PWD/src/simpleGenerators/enginesGenerator.h \
	$$PWD/src/simpleGenerators/forLoopGenerator.h \
	$$PWD/src/simpleGenerators/printStringGenerator.h \
	$$PWD/src/simpleGenerators/clearDisplayGenerator.h \
	$$PWD/src/simpleGenerators/drawPixelGenerator.h \
	$$PWD/src/simpleGenerators/drawLineGenerator.h \
	$$PWD/src/simpleGenerators/drawRectGenerator.h \
	$$PWD/src/simpleGenerators/drawEllipseGenerator.h \
	$$PWD/src/simpleGenerators/drawIconGenerator.h \
	$$PWD/src/simpleGenerators/wifiGenerator.h \
	$$PWD/src/simpleGenerators/blynkAuthorizationGenerator.h \
	$$PWD/src/simpleGenerators/blynkLedGenerator.h \
	$$PWD/src/simpleGenerators/blynkSendGenerator.h \
	$$PWD/src/simpleGenerators/blynkReceiveGenerator.h \
	$$PWD/src/simpleGenerators/blynkNotificationGenerator.h \
	$$PWD/src/simpleGenerators/blynkPropertyGenerator.h \
	$$PWD/src/simpleGenerators/blynkLCDGenerator.h \
	$$PWD/src/simpleGenerators/blynkTerminalGenerator.h \
	$$PWD/widgets/iotikAdditionalPreferences.h \

SOURCES += \
	$$PWD/src/iotikGeneratorPluginBase.cpp \
	$$PWD/src/iotikMasterGeneratorBase.cpp \
	$$PWD/src/iotikGeneratorCustomizer.cpp \
	$$PWD/src/iotikGeneratorFactory.cpp \
	$$PWD/src/parts/iotikVariablesNormalizer.cpp \
	$$PWD/src/robotModel/iotikGeneratorRobotModel.cpp \
	$$PWD/src/simpleGenerators/iotikEnginesGenerator.cpp \
	$$PWD/src/simpleGenerators/mosfetGenerator.cpp \
	$$PWD/src/simpleGenerators/ledGenerator.cpp \
	$$PWD/src/simpleGenerators/soilSensorToVariableGenerator.cpp \
	$$PWD/src/simpleGenerators/waterSensorToVariableGenerator.cpp \
	$$PWD/src/simpleGenerators/flowSensorToVariableGenerator.cpp \
	$$PWD/src/simpleGenerators/waitForTouchSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/waitForInfraredSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/waitForTemperatureSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/waitForUltrasonicSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/colorSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/accelerometerGenerator.cpp \
	$$PWD/src/simpleGenerators/compassGenerator.cpp \
	$$PWD/src/simpleGenerators/gyroscopeGenerator.cpp \
	$$PWD/src/simpleGenerators/lineDetectorGenerator.cpp \
	$$PWD/src/simpleGenerators/laserSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/flameSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/soundSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/heatingSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/humiditySensorGenerator.cpp \
	$$PWD/src/simpleGenerators/pressureSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/lightSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/ultravioletGenerator.cpp \
	$$PWD/src/simpleGenerators/capacitiveGenerator.cpp \
	$$PWD/src/simpleGenerators/matrixGenerator.cpp \
	$$PWD/src/simpleGenerators/rgbGenerator.cpp \
	$$PWD/src/simpleGenerators/relayGenerator.cpp \
	$$PWD/src/simpleGenerators/enginesGenerator.cpp \
	$$PWD/src/simpleGenerators/forLoopGenerator.cpp \
	$$PWD/src/simpleGenerators/printStringGenerator.cpp \
	$$PWD/src/simpleGenerators/clearDisplayGenerator.cpp \
	$$PWD/src/simpleGenerators/drawPixelGenerator.cpp \
	$$PWD/src/simpleGenerators/drawLineGenerator.cpp \
	$$PWD/src/simpleGenerators/drawRectGenerator.cpp \
	$$PWD/src/simpleGenerators/drawEllipseGenerator.cpp \
	$$PWD/src/simpleGenerators/drawIconGenerator.cpp \
	$$PWD/src/simpleGenerators/wifiGenerator.cpp \
	$$PWD/src/simpleGenerators/blynkAuthorizationGenerator.cpp \
	$$PWD/src/simpleGenerators/blynkLedGenerator.cpp \
	$$PWD/src/simpleGenerators/blynkSendGenerator.cpp \
	$$PWD/src/simpleGenerators/blynkReceiveGenerator.cpp \
	$$PWD/src/simpleGenerators/blynkNotificationGenerator.cpp \
	$$PWD/src/simpleGenerators/blynkPropertyGenerator.cpp \
	$$PWD/src/simpleGenerators/blynkLCDGenerator.cpp \
	$$PWD/src/simpleGenerators/blynkTerminalGenerator.cpp \
	$$PWD/widgets/iotikAdditionalPreferences.cpp \

FORMS += \
	$$PWD/widgets/iotikAdditionalPreferences.ui \
