#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p $PWD/../data/lib/plugins/editors/
mkdir -p $PWD/../data/lib/plugins/tools/kitPlugins/

cp $BIN_DIR/librobots-iotik-kit.so*						$PWD/../data/lib/
cp $BIN_DIR/librobots-iotik-generator-base.so*					$PWD/../data/lib/
cp $BIN_DIR/librobots-iotik-ruc-generator-library.so*				$PWD/../data/lib/
cp $BIN_DIR/plugins/editors/libiotikMetamodel.so				$PWD/../data/lib/plugins/editors/
cp $BIN_DIR/plugins/tools/kitPlugins/librobots-iotik-interpreter.so		$PWD/../data/lib/plugins/tools/kitPlugins/
cp $BIN_DIR/plugins/tools/kitPlugins/librobots-iotik-ruc-english-generator.so	$PWD/../data/lib/plugins/tools/kitPlugins/
cp $BIN_DIR/plugins/tools/kitPlugins/librobots-iotik-ruc-russian-generator.so	$PWD/../data/lib/plugins/tools/kitPlugins/

cp $BIN_DIR/keywords.txt	$PWD/../data/
cp $BIN_DIR/ruc			$PWD/../data/
