#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source $INSTALLER_ROOT/utils/mac_utils.sh

mkdir -p "$BUNDLE_CONTENTS/Lib/"

cp    $BIN_DIR/librobots-iotik-kit*.dylib						"$BUNDLE_CONTENTS/Lib/"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-iotik-kit.dylib"
cp    $BIN_DIR/librobots-iotik-generator-base*.dylib					"$BUNDLE_CONTENTS/Lib/"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-iotik-generator-base.dylib"
cp    $BIN_DIR/librobots-iotik-ruc-generator-library*.dylib				"$BUNDLE_CONTENTS/Lib/"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-iotik-ruc-generator-library.dylib"


mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins"
cp     $BIN_DIR/plugins/tools/kitPlugins/librobots-iotik-interpreter.dylib		"$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/librobots-iotik-interpreter.dylib"
cp     $BIN_DIR/plugins/tools/kitPlugins/librobots-iotik-ruc-english-generator.dylib	"$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/" 
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/librobots-iotik-ruc-english-generator.dylib"
cp     $BIN_DIR/plugins/tools/kitPlugins/librobots-iotik-ruc-russian-generator.dylib	"$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/" 
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/librobots-iotik-ruc-russian-generator.dylib"


mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/editors"
cp $BIN_DIR/plugins/editors/libiotikMetamodel.dylib					"$BUNDLE_CONTENTS/Lib/plugins/editors/" 
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/editors/libiotikMetamodel.dylib"
