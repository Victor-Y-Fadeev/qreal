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
	$$PWD/src/simpleGenerators/colorSensorToVariableGenerator.h \
	$$PWD/src/simpleGenerators/compassToVariableGenerator.h \
	$$PWD/src/simpleGenerators/lineDetectorToVariableGenerator.h \
	$$PWD/src/simpleGenerators/waitForTouchSensorGenerator.h \
	$$PWD/src/simpleGenerators/waitForInfraredSensorGenerator.h \
	$$PWD/src/simpleGenerators/waitForUltrasonicSensorGenerator.h \
	$$PWD/src/simpleGenerators/waitForFlameSensorGenerator.h \
	$$PWD/src/simpleGenerators/waitForSoundSensorGenerator.h \
	$$PWD/src/simpleGenerators/receiveMessageThreadsGenerator.h \
	$$PWD/src/simpleGenerators/forLoopGenerator.h \
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
	$$PWD/src/simpleGenerators/colorSensorToVariableGenerator.cpp \
	$$PWD/src/simpleGenerators/compassToVariableGenerator.cpp \
	$$PWD/src/simpleGenerators/lineDetectorToVariableGenerator.cpp \
	$$PWD/src/simpleGenerators/waitForTouchSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/waitForInfraredSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/waitForUltrasonicSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/waitForFlameSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/waitForSoundSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/receiveMessageThreadsGenerator.cpp \
	$$PWD/src/simpleGenerators/forLoopGenerator.cpp \
	$$PWD/widgets/iotikAdditionalPreferences.cpp \

FORMS += \
	$$PWD/widgets/iotikAdditionalPreferences.ui \
