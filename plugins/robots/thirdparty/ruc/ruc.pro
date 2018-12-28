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

CONFIG(clang) {
	QMAKE_CXXFLAGS += -c -Wall -DROBOTS -lm -lpthread
}

HEADERS += \
	$$PWD/ruc/RuC/Defs.h \
	$$PWD/ruc/RuC/global_vars.h \
	$$PWD/ruc/RuC/th_static.h \

SOURCES += \
	$$PWD/ruc/RuC/codegen.c \
	$$PWD/ruc/RuC/codes.c \
	$$PWD/ruc/RuC/error.c \
	$$PWD/ruc/RuC/extdecl.c \
	$$PWD/ruc/RuC/import.c \
	$$PWD/ruc/RuC/main.c \
	$$PWD/ruc/RuC/mipsgen.c \
	$$PWD/ruc/RuC/mipsopt.c \
	$$PWD/ruc/RuC/preprocess.c \
	$$PWD/ruc/RuC/scaner.c \
	$$PWD/ruc/RuC/threads.c \

RESOURCES += \
	$$PWD/ruc.qrc \
