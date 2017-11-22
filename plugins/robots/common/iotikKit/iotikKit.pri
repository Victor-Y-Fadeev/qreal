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
	$$PWD/include/iotikKit/robotModel/parts/iotikLineSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikInfraredSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikSonarSensor.h \
	$$PWD/include/iotikKit/robotModel/parts/iotikFlameSensor.h \
	$$PWD/include/iotikKit/communication/usbRobotCommunicationThread.h \
	$$PWD/src/blocks/details/iotikEnginesBackwardBlock.h \
	$$PWD/src/blocks/details/iotikEnginesForwardBlock.h \
	$$PWD/src/blocks/details/mosfetBlock.h \
	$$PWD/src/blocks/details/ledBlock.h \
	$$PWD/src/blocks/details/lineDetectorToVariable.h \
	$$PWD/src/blocks/details/waitForFlameSensorBlock.h \

SOURCES += \
	$$PWD/src/robotModel/iotikRobotModelBase.cpp \
	$$PWD/src/robotModel/parts/iotikMotor.cpp \
	$$PWD/src/robotModel/parts/iotikMosfet.cpp \
	$$PWD/src/robotModel/parts/iotikLed.cpp \
	$$PWD/src/robotModel/parts/iotikLineSensor.cpp \
	$$PWD/src/robotModel/parts/iotikInfraredSensor.cpp \
	$$PWD/src/robotModel/parts/iotikSonarSensor.cpp \
	$$PWD/src/robotModel/parts/iotikFlameSensor.cpp \
	$$PWD/src/blocks/iotikBlocksFactory.cpp \
	$$PWD/src/blocks/details/iotikEnginesBackwardBlock.cpp \
	$$PWD/src/blocks/details/iotikEnginesForwardBlock.cpp \
	$$PWD/src/blocks/details/mosfetBlock.cpp \
	$$PWD/src/blocks/details/ledBlock.cpp \
	$$PWD/src/blocks/details/lineDetectorToVariable.cpp \
	$$PWD/src/blocks/details/waitForFlameSensorBlock.cpp \
	$$PWD/src/communication/usbRobotCommunicationThread.cpp \


TRANSLATIONS = \
	$$PWD/../../../../qrtranslations/ru/plugins/robots/iotikKit_ru.ts \
	$$PWD/../../../../qrtranslations/fr/plugins/robots/iotikKit_fr.ts \
