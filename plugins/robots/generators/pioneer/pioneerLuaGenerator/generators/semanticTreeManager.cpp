/* Copyright 2017 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "semanticTreeManager.h"

#include <generatorBase/semanticTree/semanticTree.h>

using namespace pioneer::lua;
using namespace generatorBase::semantics;

SemanticTreeManager::SemanticTreeManager(
		SemanticTree &semanticTree
		, qReal::ErrorReporterInterface &errorReporter
		, bool &errorsOccured)
	: mSemanticTree(semanticTree)
	, mErrorReporter(errorReporter)
	, mErrorsOccured(errorsOccured)
{
}

bool SemanticTreeManager::isLabel(const SemanticNode * const node)
{
	return node->id().editor().startsWith("label_");
}

SemanticNode *SemanticTreeManager::rightSibling(SemanticNode * const node)
{
	NonZoneNode * const nonZoneNode = dynamic_cast<NonZoneNode * const>(node);
	if (!nonZoneNode) {
		return nullptr;
	}

	const auto zone = nonZoneNode->parentZone();
	SemanticNode * currentChild = nonZoneNode;
	if (zone && zone->nextChild(currentChild)) {
		currentChild = zone->nextChild(currentChild);
		while (currentChild && isLabel(currentChild)) {
			currentChild = zone->nextChild(currentChild);
			continue;
		}

		return currentChild;
	} else {
		return nullptr;
	}
}

NonZoneNode *SemanticTreeManager::parent(SemanticNode * const node)
{
	NonZoneNode * const nonZoneNode = dynamic_cast<NonZoneNode * const>(node);
	if (!nonZoneNode) {
		return nullptr;
	}

	return static_cast<NonZoneNode *>(nonZoneNode->parentZone()->parentNode());
}

void SemanticTreeManager::addAfter(SemanticNode * const thisNode, SemanticNode * const nextNode)
{
	static_cast<NonZoneNode * const>(thisNode)->insertSiblingAfterThis(nextNode);
}

bool SemanticTreeManager::isTopLevelNode(const generatorBase::semantics::SemanticNode * const node)
{
	if (!static_cast<const NonZoneNode * const>(node)->parentZone()) {
		return true;
	}

	const SemanticNode * const parent = static_cast<const NonZoneNode * const>(node)->parentZone()->parentNode();
	return dynamic_cast<const RootNode * const>(parent) != nullptr;
}

void SemanticTreeManager::addToZone(generatorBase::semantics::ZoneNode * const zone, const qReal::Id &id)
{
	if (!mSemanticTree.findNodeFor(id)) {
		SemanticNode * const node = mSemanticTree.produceNodeFor(id);
		zone->appendChild(node);
	} else {
		mErrorReporter.addError(QObject::tr("Too complex algorithmic construction, can not generate."));
		mErrorsOccured = true;
	}
}

NonZoneNode *SemanticTreeManager::produceLabeledNode(const qReal::Id &block)
{
	auto existingNode = mSemanticTree.findNodeFor(block);
	NonZoneNode *node = dynamic_cast<NonZoneNode *>(mSemanticTree.produceNodeFor(block));

	if (!node) {
		mErrorReporter.addError(QString(QObject::tr("Generation internal error, please send bug report to developers."
				"Additional info: zone node %1 can not be used as labeled node.").arg(block.id())));
		mErrorsOccured = true;
		return nullptr;
	}

	if (existingNode) {
		if (!mClones.contains(existingNode->id(), dynamic_cast<NonZoneNode *>(existingNode))) {
			mClones.insert(existingNode->id(), dynamic_cast<NonZoneNode *>(existingNode));
		}

		mClones.insert(node->id(), node);
	}

	node->addLabel();
	return node;
}

SemanticNode *SemanticTreeManager::findSibling(SemanticNode *node, std::function<bool(SemanticNode *)> predicate)
{
	NonZoneNode *nonZoneNode = dynamic_cast<NonZoneNode *>(node);
	if (!nonZoneNode) {
		return nullptr;
	}

	const auto zone = nonZoneNode->parentZone();
	if (!zone) {
		return nullptr;
	}

	SemanticNode * currentChild = nonZoneNode;
	while (zone->nextChild(currentChild)) {
		currentChild = zone->nextChild(currentChild);
		if (predicate(currentChild)) {
			return currentChild;
		}
	}

	return nullptr;
}

QLinkedList<SemanticNode *> SemanticTreeManager::copyRightSiblingsUntil(SemanticNode *node
		, std::function<bool(SemanticNode *)> predicate)
{
	NonZoneNode *nonZoneNode = dynamic_cast<NonZoneNode *>(node);
	if (!nonZoneNode) {
		mErrorReporter.addError(QObject::tr("Generation internal error, synchronous zone parent is a zone node."));
		mErrorsOccured = true;
		return {};
	}

	const auto zone = nonZoneNode->parentZone();
	if (!zone) {
		mErrorReporter.addError(QObject::tr("Generation internal error, synchronous fragment zone is absent."));
		mErrorsOccured = true;
		return {};
	}

	SemanticNode * currentChild = nonZoneNode;
	QLinkedList<SemanticNode *> result;
	while (zone->nextChild(currentChild)) {
		currentChild = zone->nextChild(currentChild);

		if (isLabel(currentChild)) {
			// Label node, we want to simply skip it, as it is not actually a part of a fragment.
			continue;
		}

		result << mSemanticTree.produceNodeFor(currentChild->id());
		if (!mClones.contains(currentChild->id(), dynamic_cast<NonZoneNode *>(currentChild))) {
			mClones.insert(currentChild->id(), dynamic_cast<NonZoneNode *>(currentChild));
		}

		mClones.insert(currentChild->id(), dynamic_cast<NonZoneNode *>(result.last()));

		// "If" needs special handling.
		auto ifNode = dynamic_cast<IfNode *>(currentChild);
		if (ifNode) {
			auto newIfNode = dynamic_cast<IfNode *>(result.last());
			QLinkedList<SemanticNode *> newThenNodes;
			for (auto node : ifNode->thenZone()->children()) {
				if (isLabel(node)) {
					SimpleNode * const gotoNode = mSemanticTree.produceSimple(node->id());
					gotoNode->bindToSyntheticConstruction(SimpleNode::gotoNode);
					newThenNodes << gotoNode;
					continue;
				}

				newThenNodes << mSemanticTree.produceNodeFor(node->id());
				if (!mClones.contains(node->id(), dynamic_cast<NonZoneNode *>(node))) {
					mClones.insert(node->id(), dynamic_cast<NonZoneNode *>(node));
				}

				mClones.insert(node->id(), dynamic_cast<NonZoneNode *>(newThenNodes.last()));
			}

			QLinkedList<SemanticNode *> newElseNodes;
			for (auto node : ifNode->elseZone()->children()) {
				if (isLabel(node)) {
					SimpleNode * const gotoNode = mSemanticTree.produceSimple(node->id());
					gotoNode->bindToSyntheticConstruction(SimpleNode::gotoNode);
					newElseNodes << gotoNode;
					continue;
				}

				newElseNodes << mSemanticTree.produceNodeFor(node->id());
				if (!mClones.contains(node->id(), dynamic_cast<NonZoneNode *>(node))) {
					mClones.insert(node->id(), dynamic_cast<NonZoneNode *>(node));
				}

				mClones.insert(node->id(), dynamic_cast<NonZoneNode *>(newElseNodes.last()));
			}

			newIfNode->thenZone()->appendChildren(newThenNodes);
			newIfNode->elseZone()->appendChildren(newElseNodes);
		}

		if (predicate(currentChild)) {
			break;
		}
	}

	return result;
}

QList<NonZoneNode *> SemanticTreeManager::nodes(const qReal::Id &id) const
{
	if (mClones.contains(id)) {
		return mClones.values(id);
	} else {
		return {mSemanticTree.findNodeFor(id)};
	}
}
