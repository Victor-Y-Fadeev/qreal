#!/bin/bash
# Usage: build-iotik-studio.sh <path-to-qt> <path-to-qt-installer-framework> [tag]. See build-installer.sh for more info.

QT="/C/Qt/5.9.9/mingw53_32/bin/"
QT_INSTALLER_FRAMEWORK="/C/Qt/Tools/QtInstallerFramework/3.1/bin"

if ! [[ -z $1 ]] ; then
	QT=$1

	if ! [[ -z $2 ]] ; then
		QT_INSTALLER_FRAMEWORK=$2
	fi
fi


set -o nounset
set -o errexit

cd "$(dirname "$0")"

export QREAL_BUILD_TAG=${3:-}

[ $OSTYPE == "linux-gnu" ] && EXCLUDE="-e ru.qreal.root.nxt.tools,ru.qreal.root.associations" || EXCLUDE=
grep -q "darwin" <<< $OSTYPE && EXCLUDE="-e ru.qreal.root.nxt.tools,ru.qreal.root.associations" || :
grep -q "darwin" <<< $OSTYPE && export PRODUCT_DISPLAYED_NAME="IoTik Studio" || :
chmod +x $PWD/build-installer.sh && $PWD/build-installer.sh $QT $QT_INSTALLER_FRAMEWORK iotik-studio $EXCLUDE
