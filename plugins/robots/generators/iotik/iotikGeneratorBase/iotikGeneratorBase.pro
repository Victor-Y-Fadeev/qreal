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

DEFINES += ROBOTS_TRIK_GENERATOR_BASE_LIBRARY

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
	$$PWD/include/iotikGeneratorBase/trikGeneratorBaseDeclSpec.h \
	$$PWD/include/iotikGeneratorBase/trikGeneratorPluginBase.h \
	$$PWD/include/iotikGeneratorBase/trikMasterGeneratorBase.h \
	$$PWD/src/iotikGeneratorFactory.h \
	$$PWD/src/simpleGenerators/iotikEnginesGenerator.h \
	$$PWD/src/simpleGenerators/waitForInfraredSensorGenerator.h \


SOURCES += \
	$$PWD/src/iotikGeneratorPluginBase.cpp \
	$$PWD/src/iotikMasterGeneratorBase.cpp \
	$$PWD/src/iotikGeneratorCustomizer.cpp \
	$$PWD/src/iotikGeneratorFactory.cpp \
	$$PWD/src/simpleGenerators/iotikEnginesGenerator.cpp \
	$$PWD/src/simpleGenerators/waitForInfraredSensorGenerator.cpp \
