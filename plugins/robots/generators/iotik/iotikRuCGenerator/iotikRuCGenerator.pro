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

TARGET = robots-iotik-ruc-generator

include(../../../../../global.pri)

QT += widgets network

CONFIG += c++11

TEMPLATE = lib
CONFIG += plugin

DESTDIR = $$PWD/../../../../../bin/plugins/tools/kitPlugins/

MOC_DIR = .moc
RCC_DIR = .moc
OBJECTS_DIR = .obj

LIBS += -L$$PWD/../../../../../bin -lqrkernel -lqslog -lqrutils -lqrrepo -lqscintilla2 \
                -lrobots-generator-base -lrobots-trik-generator-base -lrobots-utils \

INCLUDEPATH += \
	$$PWD/../iotikGeneratorBase/include/ \
        $$PWD/../../generatorBase/include/ \
        $$PWD/../../../interpreters/interpreterBase/include \
        $$PWD/../../../utils/include/ \
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
	$$PWD/../../../../../qrtranslations/ru/plugins/robots/iotikRuCGenerator_ru.ts \
	$$PWD/../../../../../qrtranslations/fr/plugins/robots/iotikRuCGenerator_fr.ts \

HEADERS += \
	$$PWD/iotikRuCGeneratorPlugin.h \
	$$PWD/iotikRuCMasterGenerator.h \

SOURCES += \
	$$PWD/iotikRuCGeneratorPlugin.cpp \
	$$PWD/iotikRuCMasterGenerator.cpp \

RESOURCES += \
    $$PWD/iotikRuCGenerator.qrc \
    $$PWD/templates.qrc \
