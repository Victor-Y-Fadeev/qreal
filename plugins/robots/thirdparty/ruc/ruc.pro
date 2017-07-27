# Copyright 2016 QReal Research Group
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

TEMPLATE = app

CONFIG(clang) {
	QMAKE_CXXFLAGS += -lm -DROBOTS
}


HEADERS += \
	$$PWD/RuC/Defs.h \
	$$PWD/RuC/global_vars.h \

SOURCES += \
	$$PWD/RuC/codegen.c \
	$$PWD/RuC/codes.c \
	$$PWD/RuC/error.c \
	$$PWD/RuC/extdecl.c \
	$$PWD/RuC/import.c \
	$$PWD/RuC/main.c \
	$$PWD/RuC/scaner.c \

RESOURCES += \
	$$PWD/keywords.txt \


copyToDestdir(keywords.txt, NOW)
