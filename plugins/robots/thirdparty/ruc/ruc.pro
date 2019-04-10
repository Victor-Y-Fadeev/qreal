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

TARGET = ruc

include(../../../../global.pri)

copyToDestdir(ruc/keywords.txt, NOW)

TEMPLATE = app

includes(plugins/robots/thirdparty/ruc/ruc/util)

CONFIG(clang) {
	QMAKE_CXXFLAGS += -c -Wall -DROBOTS -lm -lpthread -Iutil
}

HEADERS += \
	$$PWD/ruc/RuC/global_vars.h \
	$$PWD/ruc/util/Defs.h \
	$$PWD/ruc/util/util.h \
	#$$PWD/ruc/RuCVM/th_static.h \

SOURCES += \
	$$PWD/ruc/RuC/codegen.c \
	$$PWD/ruc/RuC/codes.c \
	$$PWD/ruc/RuC/error.c \
	$$PWD/ruc/RuC/extdecl.c \
	$$PWD/ruc/RuC/main.c \
	$$PWD/ruc/RuC/preprocess.c \
	$$PWD/ruc/RuC/scaner.c \
	$$PWD/ruc/util/util.c \
	#$$PWD/ruc/RuCVM/import.c \
	#$$PWD/ruc/RuCVM/threads.c \

RESOURCES += \
	$$PWD/ruc.qrc \
