#pragma once

#include <generatorBase/simpleGenerators/bindingGenerator.h>

namespace iotik {
namespace simple {

/// Generator for 'EnginesForward', 'EnginesBackward' and 'AngularServo' block
class IotikEnginesGenerator : public generatorBase::simple::BindingGenerator
{
public:
	IotikEnginesGenerator(qrRepo::RepoApi const &repo
			, generatorBase::GeneratorCustomizer &customizer
			, qReal::Id const &id
			, QString const &engineType
			, QObject *parent);
};

}
}
