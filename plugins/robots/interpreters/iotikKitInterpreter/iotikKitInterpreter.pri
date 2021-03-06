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

links(qrkernel qrutils qrtext qrgui-preferences-dialog qrgui-tool-plugin-interface \
		robots-utils robots-kit-base robots-2d-model robots-iotik-kit qslog \
		)

includes(plugins/robots/common/kitBase \
		plugins/robots/utils \
		qrtext \
		plugins/robots/common/iotikKit \
		thirdparty/qscintilla/Qt4Qt5 \
)

HEADERS += \
	$$PWD/src/iotikKitInterpreterPlugin.h \

SOURCES += \
	$$PWD/src/iotikKitInterpreterPlugin.cpp \

RESOURCES += \
	$$PWD/iotikKitInterpreter.qrc \

TRANSLATIONS = \
	$$PWD/../../../../qrtranslations/ru/plugins/robots/iotikKitInterpreter_ru.ts \
	$$PWD/../../../../qrtranslations/fr/plugins/robots/iotikKitInterpreter_fr.ts \

OTHER_FILES += \
	$$PWD/iotikDefaultSettings.ini \
