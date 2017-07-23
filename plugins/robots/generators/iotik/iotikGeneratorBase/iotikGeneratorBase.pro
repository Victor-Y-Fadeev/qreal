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

CONFIG += c++11

TEMPLATE = lib
CONFIG += plugin

DESTDIR = $$PWD/../../../../../bin/

MOC_DIR = .moc
RCC_DIR = .moc
OBJECTS_DIR = .obj

LIBS += -L$$PWD/../../../../../bin -lqrkernel -lqslog -lqrutils -lqrrepo \
		-lrobots-generator-base -lrobots-interpreter-base \

DEFINES += ROBOTS_IOTIK_GENERATOR_BASE_LIBRARY

INCLUDEPATH += \
	$$PWD/include \
	$$PWD/../../generatorBase/include/ \
	$$PWD/../../../interpreters/interpreterBase/include \
	$$PWD/../../../../../ \
	$$PWD/../../../../../qrgui \
	$$PWD/../../../../../qrtext/include \

# workaround for http://bugreports.qt.nokia.com/browse/QTBUG-8110
# when fixed it would become possible to use QMAKE_LFLAGS_RPATH
!macx {
	QMAKE_LFLAGS += -Wl,-O1,-rpath,$$PWD/../../../../../bin/
	QMAKE_LFLAGS += -Wl,-rpath,$$PWD/../../../../../bin/plugins/
}

TRANSLATIONS = \
	$$PWD/../../../../../qrtranslations/ru/plugins/robots/iotikGeneratorBase_ru.ts \
	$$PWD/../../../../../qrtranslations/fr/plugins/robots/iotikGeneratorBase_fr.ts \

HEADERS += \
	$$PWD/include/iotikGeneratorBase/iotikGeneratorBaseDeclSpec.h \
	$$PWD/include/iotikGeneratorBase/iotikGeneratorPluginBase.h \
	$$PWD/include/iotikGeneratorBase/iotikMasterGeneratorBase.h \
	$$PWD/src/iotikGeneratorCustomizer.h \
	$$PWD/src/iotikGeneratorFactory.h \
	$$PWD/src/parts/iotikDeviceVariables.h \
	$$PWD/src/simpleGenerators/detectorToVariableGenerator.h \
	$$PWD/src/simpleGenerators/systemGenerator.h \
	$$PWD/src/simpleGenerators/iotikEnginesGenerator.h \
	$$PWD/src/simpleGenerators/waitForInfraredSensorGenerator.h \
	$$PWD/src/simpleGenerators/waitForMotionGenerator.h \
	#$$PWD/src/simpleGenerators/sendMessageGenerator.h \
	#$$PWD/src/simpleGenerators/waitForMessageGenerator.h \

SOURCES += \
	$$PWD/src/iotikGeneratorPluginBase.cpp \
	$$PWD/src/iotikMasterGeneratorBase.cpp \
	$$PWD/src/iotikGeneratorCustomizer.cpp \
	$$PWD/src/iotikGeneratorFactory.cpp \
	$$PWD/src/parts/iotikDeviceVariables.cpp \
	$$PWD/src/simpleGenerators/detectorToVariableGenerator.cpp \
	$$PWD/src/simpleGenerators/systemGenerator.cpp \
	$$PWD/src/simpleGenerators/iotikEnginesGenerator.cpp \
	$$PWD/src/simpleGenerators/waitForInfraredSensorGenerator.cpp \
	$$PWD/src/simpleGenerators/waitForMotionGenerator.cpp \
	#$$PWD/src/simpleGenerators/sendMessageGenerator.cpp \
	#$$PWD/src/simpleGenerators/waitForMessageGenerator.cpp \
