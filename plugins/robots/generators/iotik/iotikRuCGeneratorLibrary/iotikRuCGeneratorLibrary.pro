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

TARGET = robots-iotik-ruc-generator-library

include(../../../../../global.pri)

QT += widgets

TEMPLATE = lib

includes(plugins/robots/generators/iotik/iotikGeneratorBase \
		plugins/robots/generators/generatorBase \
		plugins/robots/common/kitBase \
		plugins/robots/common/iotikKit \
		plugins/robots/utils \
		qrtext \
                thirdparty/qscintilla/Qt4Qt5 \
)

links(qrkernel qslog qrutils qrrepo qscintilla2 robots-generator-base robots-iotik-generator-base \
		robots-kit-base robots-iotik-kit robots-utils \
)

TRANSLATIONS = \
	$$PWD/../../../../../qrtranslations/ru/plugins/robots/iotikRuCGeneratorLibrary_ru.ts \
	$$PWD/../../../../../qrtranslations/fr/plugins/robots/iotikRuCGeneratorLibrary_fr.ts \

HEADERS += \
	$$PWD/include/iotikRuCGeneratorLibrary/iotikRuCGeneratorPluginBase.h \
	$$PWD/include/iotikRuCGeneratorLibrary/iotikRuCGeneratorDefs.h \
	$$PWD/src/iotikRuCMasterGenerator.h \
	$$PWD/dialogs/iotikActivator.h \

SOURCES += \
	$$PWD/src/iotikRuCGeneratorPluginBase.cpp \
	$$PWD/src/iotikRuCMasterGenerator.cpp \
	$$PWD/dialogs/iotikActivator.cpp \

FORMS += \
	$$PWD/dialogs/iotikActivator.ui \

RESOURCES += \
	$$PWD/iotikRuCGeneratorLibrary.qrc \
	$$PWD/templates_russian.qrc \
	$$PWD/templates_english.qrc \
