#pragma once

#include <functional>
#include <QtCore/QHash>

#include "qrtext/core/error.h"
#include "qrtext/core/ast/node.h"

#include "qrtext/core/semantics/semanticAnalyzer.h"

#include "qrtext/lua/types/function.h"

namespace qrtext {
namespace lua {
namespace details {

class LuaInterpreter {
public:
	explicit LuaInterpreter(QList<core::Error> &errors);

	void addIntrinsicFunction(QString const &name
			, std::function<QVariant(QList<QVariant> const &)> const &semantic);

	QVariant interpret(QSharedPointer<core::ast::Node> const &root, core::SemanticAnalyzer const &semanticAnalyzer);

	QStringList identifiers() const;

	QVariant value(QString const &identifier) const;

	void setVariableValue(QString const &name, QVariant const &value);

private:
	QVariant interpretUnaryOperator(QSharedPointer<core::ast::Node> const &root
			, core::SemanticAnalyzer const &semanticAnalyzer);

	QVariant interpretBinaryOperator(QSharedPointer<core::ast::Node> const &root
			, core::SemanticAnalyzer const &semanticAnalyzer);

	QVariant operateOnIndexingExpression(QSharedPointer<core::ast::Node> const &indexingExpression
			, core::SemanticAnalyzer const &semanticAnalyzer
			, std::function<QVariant(QString const &, QStringList &, int)> const &action);

	QHash<QString, QVariant> mIdentifierValues;
	QHash<QString, std::function<QVariant(QList<QVariant> const &)>> mIntrinsicFunctions;

	QList<core::Error> &mErrors;
};

}
}
}
