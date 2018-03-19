#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

cp $BIN_DIR/robots-iotik-kit.dll						$PWD/../data/
cp $BIN_DIR/robots-iotik-generator-base.dll					$PWD/../data/
cp $BIN_DIR/robots-iotik-ruc-generator-library.dll				$PWD/../data/
cp $BIN_DIR/plugins/editors/iotikMetamodel.dll					$PWD/../data/plugins/editors/
cp $BIN_DIR/plugins/tools/kitPlugins/robots-iotik-interpreter.dll		$PWD/../data/plugins/tools/kitPlugins/
cp $BIN_DIR/plugins/tools/kitPlugins/robots-iotik-ruc-english-generator.dll	$PWD/../data/plugins/tools/kitPlugins/
cp $BIN_DIR/plugins/tools/kitPlugins/robots-iotik-ruc-russian-generator.dll	$PWD/../data/plugins/tools/kitPlugins/

cp $BIN_DIR/keywords.txt		$PWD/../data/
cp $BIN_DIR/ruc.exe			$PWD/../data/
