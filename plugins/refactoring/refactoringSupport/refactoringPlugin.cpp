#include "refactoringPlugin.h"

#include <QFileDialog>
#include <QProcess>
#include <QApplication>
#include <QProgressBar>
#include <QDesktopWidget>
#include <QtGui/QApplication>

#include "../../../qrutils/xmlUtils.h"
#include "../../../qrutils/outFile.h"
#include "../../../qrkernel/settingsManager.h"
#include "refactoringWindow.h"

using namespace qReal;
using namespace refactoring;
using namespace utils;

Q_EXPORT_PLUGIN2(refactoring, qReal::refactoring::RefactoringPlugin)

RefactoringPlugin::RefactoringPlugin()
	: mPreferencesPage(new RefactoringPreferencesPage())
	, mRefactoringWindow(NULL)
{
	mAppTranslator.load(":/refactoringSupport_" + QLocale::system().name());
	QApplication::installTranslator(&mAppTranslator);
}

RefactoringPlugin::~RefactoringPlugin()
{
}

void RefactoringPlugin::init(PluginConfigurator const &configurator)
{
	mErrorReporter = configurator.mainWindowInterpretersInterface().errorReporter();
	mLogicalModelApi = &configurator.logicalModelApi();
	mGraphicalModelApi = &configurator.graphicalModelApi();

	mMetamodelGeneratorSupport = new MetamodelGeneratorSupport(
				configurator.mainWindowInterpretersInterface().errorReporter(),
				&configurator.mainWindowInterpretersInterface());
	mRepoControlIFace = &configurator.repoControlInterface();
	mMainWindowIFace = &configurator.mainWindowInterpretersInterface();
	mQRealSourceFilesPath = SettingsManager::value("qrealSourcesLocation", "").toString();
	mPathToRefactoringExamples = mQRealSourceFilesPath + "/plugins/refactoring/refactoringExamples/";

	mRefactoringWindow = new RefactoringWindow(mMainWindowIFace->windowWidget());
	connect(mRefactoringWindow, SIGNAL(rejected()), this, SLOT(discardRefactoring()));

	mRefactoringRepoApi = new qrRepo::RepoApi(mQRealSourceFilesPath + "/plugins/refactoring/refactoringExamples");
	mRefactoringFinder = new RefactoringFinder(configurator.logicalModelApi()
			, configurator.graphicalModelApi()
			, configurator.mainWindowInterpretersInterface()
			, mRefactoringRepoApi);

	connect(mRefactoringWindow, SIGNAL(findButtonClicked(QString)), this, SLOT(findRefactoring(QString)));
	connect(mRefactoringWindow, SIGNAL(findNextButtonClicked()), this, SLOT(findNextRefactoring()));
	connect(mRefactoringWindow, SIGNAL(discardButtonClicked()), this, SLOT(discardRefactoring()));
}

QPair<QString, PreferencesPage *> RefactoringPlugin::preferencesPage()
{
	return qMakePair(tr("Refactorings"), static_cast<PreferencesPage*>(mPreferencesPage));
}

QList<qReal::ActionInfo> RefactoringPlugin::actions()
{
	mRefactoringMenu = new QMenu(tr("Refactoring"));
	ActionInfo refactoringMenuInfo(mRefactoringMenu, "tools");

	mGenerateAndLoadRefactoringEditorAction = new QAction(tr("Generate and load refactoring editor"), NULL);
	connect(mGenerateAndLoadRefactoringEditorAction, SIGNAL(triggered()), this, SLOT(generateRefactoringMetamodel()));
	mRefactoringMenu->addAction(mGenerateAndLoadRefactoringEditorAction);

	mOpenRefactoringWindowAction = new QAction(tr("Open Refactoring Window"), NULL);
	connect(mOpenRefactoringWindowAction, SIGNAL(triggered()), this, SLOT(openRefactoringWindow()));
	mRefactoringMenu->addAction(mOpenRefactoringWindowAction);

	mSaveRefactoringAction = new QAction(tr("Save Refactoring"), NULL);
	connect(mSaveRefactoringAction, SIGNAL(triggered()), this, SLOT(saveRefactoring()));
	mRefactoringMenu->addAction(mSaveRefactoringAction);

	mPlaceMenu = new QMenu(tr("Automatically arrange elements"));

	mPlaceTBAction = new QAction(tr("Top-Bottom"), NULL);
	connect(mPlaceTBAction, SIGNAL(triggered()), this, SLOT(arrangeElementsTB()));
	mPlaceMenu->addAction(mPlaceTBAction);

	mPlaceLRAction = new QAction(tr("Left-Right"), NULL);
	connect(mPlaceLRAction, SIGNAL(triggered()), this, SLOT(arrangeElementsLR()));
	mPlaceMenu->addAction(mPlaceLRAction);

	mPlaceBTAction = new QAction(tr("Bottom-Top"), NULL);
	connect(mPlaceBTAction, SIGNAL(triggered()), this, SLOT(arrangeElementsBT()));
	mPlaceMenu->addAction(mPlaceBTAction);

	mPlaceRLAction = new QAction(tr("Right-Left"), NULL);
	connect(mPlaceRLAction, SIGNAL(triggered()), this, SLOT(arrangeElementsRL()));
	mPlaceMenu->addAction(mPlaceRLAction);

	mRefactoringMenu->addMenu(mPlaceMenu);

	mActionInfos << refactoringMenuInfo;

	return mActionInfos;
}

void RefactoringPlugin::generateRefactoringMetamodel()
{
	QDir currentDir(".");

	QString editorMetamodelFilePath =
			QFileDialog::getOpenFileName(
				NULL
				, tr("Select xml file to load refactoring metamodel")
				, currentDir.absolutePath()
				, "XML files (*.xml)"
				);
		if (editorMetamodelFilePath == "" || mQRealSourceFilesPath == "") {
		return;
	}

	QDomDocument metamodel = mMetamodelGeneratorSupport->loadMetamodelFromFile(editorMetamodelFilePath);

	QDomElement diagram = mMetamodelGeneratorSupport->getDiagramElement(metamodel);
	QDomElement graphics = metamodel.elementsByTagName("graphicTypes").at(0).toElement();
	QString diagramName = diagram.attribute("name").replace(" ", "_");
	QString displayedName = diagram.attribute("displayedName");
	if (displayedName == "") {
		displayedName = diagramName;
	}

	diagram.setAttribute("displayedName", displayedName + " Refactorings");
	insertRefactoringID(metamodel, metamodel.elementsByTagName("node"), true);
	insertRefactoringID(metamodel, metamodel.elementsByTagName("edge"), false);
	addPalette(metamodel, diagram, metamodelPaletteGroup(metamodel, metamodel.elementsByTagName("node"), metamodel.elementsByTagName("edge")));

	addRefactoringLanguageElements(diagramName, metamodel, graphics, mQRealSourceFilesPath + "/plugins/refactoring/editor/refactoringEditor.xml");
		mEditorElementNames.clear();

	QString metamodelName = diagramName + "RefactoringsMetamodel";
	QString relativeEditorPath = diagramName + "RefactoringsEditor";
	QString editorPath = mQRealSourceFilesPath + "/plugins/" + relativeEditorPath;

	mMetamodelGeneratorSupport->generateProFile(metamodel,
												editorMetamodelFilePath, mQRealSourceFilesPath, metamodelName,
												editorPath, relativeEditorPath
												);

	mMetamodelGeneratorSupport->saveMetamodelInFile(metamodel, editorPath + "/" + metamodelName + ".xml");

	mMetamodelGeneratorSupport->loadPlugin(editorPath, metamodelName
										   , SettingsManager::value("pathToQmake", "").toString()
										   , SettingsManager::value("pathToMake", "").toString()
										   , SettingsManager::value("pluginExtension", "").toString()
										   , SettingsManager::value("prefix", "").toString());

}

void RefactoringPlugin::insertRefactoringID(QDomDocument metamodel, QDomNodeList list, bool isNode)
{
	for (int i = 0; i < list.size(); ++i) {
		QDomElement element = list.at(i).toElement();
		mEditorElementNames.append(element.attribute("name", ""));

		QDomElement graphics = element.elementsByTagName("graphics").at(0).toElement();
		QDomNodeList labels = graphics.elementsByTagName("labels");
		QString x = graphics.elementsByTagName("picture").at(0).toElement().attribute("sizex");

		QDomElement label = metamodel.createElement("label");
		if (isNode) {
			label.setAttribute("x", x);
			label.setAttribute("y", "0");
		}
		label.setAttribute("textBinded", "ID");
		if (labels.length() > 0) {
			labels.at(0).insertBefore(label, labels.at(0).firstChild());
		} else {
			QDomElement labelsElem = metamodel.createElement("labels");
			labelsElem.appendChild(label);
			graphics.appendChild(labelsElem);
		}

		QDomElement logic = element.elementsByTagName("logic").at(0).toElement();
		QDomNodeList properties = logic.elementsByTagName("properties");

		QDomElement property = metamodel.createElement("property");
		property.setAttribute("type", "ID");
		property.setAttribute("name", "ID");
		if (properties.length() > 0) {
			properties.at(0).appendChild(property);
		} else {
			QDomElement propertiesElem = metamodel.createElement("properties");
			propertiesElem.appendChild(property);
			logic.appendChild(propertiesElem);
		}
	}
}
void RefactoringPlugin::addRefactoringLanguageElements(QString diagramName, QDomDocument metamodel, QDomElement &graphics, const QString &pathToRefactoringMetamodel)
{
	QDomDocument refactoringMetamodel = mMetamodelGeneratorSupport->loadMetamodelFromFile(pathToRefactoringMetamodel);
	QDomNodeList nodes = refactoringMetamodel.elementsByTagName("node");
	while (!nodes.isEmpty()) {
		QDomNode node = nodes.at(0);
		QDomElement nodeElement = node.toElement();
		QString const name = nodeElement.attribute("name", "");
		if (name == "beforeBlock" || name == "afterBlock") {
			QDomElement logic = nodeElement.elementsByTagName("logic").at(0).toElement();
			QDomElement container = logic.elementsByTagName("container").at(0).toElement();
			foreach (QString elementName, mEditorElementNames) {
				QDomElement contains = metamodel.createElement("contains");
				contains.setAttribute("type", diagramName + "::" + elementName);
				container.appendChild(contains);
			}
		}
		graphics.appendChild(node);
	}
	QDomNodeList edges = refactoringMetamodel.elementsByTagName("edge");
	while (!edges.isEmpty()) {
		QDomNode edge = edges.at(0);
		graphics.appendChild(edge);
	}
}

void RefactoringPlugin::openRefactoringWindow()
{
	mRefactoringWindow->updateRefactorings(mPathToRefactoringExamples);
	mRefactoringWindow->show();
}

void RefactoringPlugin::saveRefactoring()
{
	IdList const childrenIDs = mLogicalModelApi->children(Id::rootId());
	QHash<Id, QString> diagramIds;
	foreach (Id const &childId, childrenIDs) {
		if (childId.element() == "RefactoringDiagramNode" && childId == mMainWindowIFace->activeDiagram()) {
			QString elementName = mGraphicalModelApi->name(childId).replace(" ", "")
					.replace("(", "").replace(")", "");
			if (elementName != "") {
				QString fileName = mPathToRefactoringExamples + elementName;
				diagramIds.insert(childId, fileName + ".qrs");
				mMainWindowIFace->saveDiagramAsAPictureToFile(fileName + ".png");
			}
		}
	}
	mRepoControlIFace->saveDiagramsById(diagramIds);
}

QDomElement RefactoringPlugin::createPaletteElement(QString const &elementType, QDomDocument metamodel, QString const &displayedName)
{
	QDomElement element = metamodel.createElement(elementType);
	element.setAttribute("name", displayedName);
	return element;
}

QDomElement RefactoringPlugin::metamodelPaletteGroup(QDomDocument metamodel, QDomNodeList nodeList, QDomNodeList edgeList)
{
	QDomElement metamodelGroup = createPaletteElement("group", metamodel, "Source Metamodel Elements");
	addElementsToMetamodelGroup(metamodel, nodeList, metamodelGroup);
	addElementsToMetamodelGroup(metamodel, edgeList, metamodelGroup);
	return metamodelGroup;
}

void RefactoringPlugin::addElementsToMetamodelGroup(QDomDocument metamodel, QDomNodeList list, QDomElement metamodelGroup)
{
	for (int i = 0; i < list.size(); ++i) {
		QDomElement element = list.at(i).toElement();
		QString const displayedName = element.attribute("displayedName", "");
		QDomElement paletteElement = createPaletteElement("element", metamodel, displayedName);
		metamodelGroup.appendChild(paletteElement);
	}
}

void RefactoringPlugin::addPalette(QDomDocument metamodel, QDomElement diagram, QDomElement metamodelPaletteGroup)
{
	QStringList patternGroupNamesList;
	patternGroupNamesList << "Refactoring Diagram"
			<< "From Before To After"
			<< "After Block"
			<< "After Block";
	QStringList basicGroupNamesList;
	basicGroupNamesList << "Element"
			<< "Link"
			<< "Selected segment";
	QDomElement palette = metamodel.createElement("palette");
	addPaletteGroup(metamodel, palette, "Refactoring Rule Elements", patternGroupNamesList);
	addPaletteGroup(metamodel, palette, "Basic Elements", basicGroupNamesList);
	palette.appendChild(metamodelPaletteGroup);
	diagram.appendChild(palette);
}

void RefactoringPlugin::addPaletteGroup(QDomDocument metamodel, QDomElement palette, const QString &groupName, const QStringList &elementNameList)
{
	QDomElement group = createPaletteElement("group", metamodel, groupName);
	foreach (QString const &elementName, elementNameList) {
		QDomElement element = createPaletteElement("element", metamodel, elementName);
		group.appendChild(element);
	}
	palette.appendChild(group);
}

void RefactoringPlugin::arrangeElements(const QString &algorithm)
{
	mMainWindowIFace->arrangeElementsByDotRunner(algorithm, mQRealSourceFilesPath + "/qrgui/dotFiles");
}

void RefactoringPlugin::arrangeElementsBT()
{
	arrangeElements("TB"); // направление оси y противоположное
}

void RefactoringPlugin::arrangeElementsLR()
{
	arrangeElements("LR");
}
void RefactoringPlugin::arrangeElementsTB()
{
	arrangeElements("BT"); // направление оси y противоположное
}

void RefactoringPlugin::arrangeElementsRL()
{
	arrangeElements("RL");
}

void RefactoringPlugin::findRefactoring(const QString &refactoringName)
{
	QString refactoringPath = mPathToRefactoringExamples + refactoringName + ".qrs";
	mRefactoringRepoApi->importFromDisk(refactoringPath);
	if (mRefactoringFinder->findMatch()) {
		mMatches = mRefactoringFinder->getMatches();
		if (mMatches.isEmpty()) {
			return;
		}
		QHash <Id, Id> currentMatch = mMatches.takeFirst();
		foreach (Id const &id, currentMatch.keys()) {
			QColor const color = QColor(SettingsManager::value("refactoringColor"
					, "green").toString());
			mMainWindowIFace->highlight(currentMatch.value(id), false, color);
		}
	}
	mRefactoringWindow->activateRestButtons();
}

void qReal::refactoring::RefactoringPlugin::findNextRefactoring()
{
	mMainWindowIFace->dehighlight();
	if (mMatches.isEmpty()) {
		mMainWindowIFace->errorReporter()->addInformation("No next match");
		mRefactoringWindow->discard();
	}
	else {
		QHash <Id, Id> currentMatch = mMatches.takeFirst();
		foreach (Id const &id, currentMatch.keys()) {
			QColor const color = QColor(SettingsManager::value("refactoringColor"
					, "green").toString());
			mMainWindowIFace->highlight(currentMatch.value(id), false, color);
		}
	}
}

void RefactoringPlugin::discardRefactoring()
{
	mMainWindowIFace->dehighlight();
	mMatches.clear();
	mRefactoringWindow->discard();
	mMainWindowIFace->errorReporter()->clearErrors();
}

