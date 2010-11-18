#include "preferencesDialog.h"
#include "ui_preferencesDialog.h"

#include <QSettings>

PreferencesDialog::PreferencesDialog(QAction * const showGridAction,
		QAction * const activateGridAction, QAction * const activateAlignmentAction, QWidget *parent)
	: QDialog(parent), ui(new Ui::PreferencesDialog), mShowGridAction(showGridAction)
	, mActivateGridAction(activateGridAction), mActivateAlignmentAction(activateAlignmentAction)
{
	ui->setupUi(this);
	initPreferences();

}

PreferencesDialog::~PreferencesDialog()
{
	delete ui;
}

void PreferencesDialog::initPreferences()
{
	QSettings settings("SPbSU", "QReal");
	ui->gridWidthSlider->setValue(settings.value("GridWidth", 10).toInt());

	ui->chooseDiagramsToSaveCheckBox->setChecked(
		settings.value("ChooseDiagramsToSave", true).toBool());
	ui->diagramCreateCheckBox->setChecked(settings.value("DiagramCreateSuggestion", true).toBool());
	ui->paletteTabCheckBox->setChecked(settings.value("PaletteTabSwitching", true).toBool());
	ui->chaoticEditionCheckBox->setChecked(settings.value("ChaoticEdition", false).toBool());
	ui->saveExitCheckBox->setChecked(settings.value("SaveExitSuggestion", true).toBool());
	ui->activateGridCheckBox->setChecked(settings.value("ActivateGrid", true).toBool());
	ui->activateAlignmentCheckBox->setChecked(settings.value("ActivateAlignment", true).toBool());
	ui->antialiasingCheckBox->setChecked(settings.value("Antialiasing", true).toBool());
	ui->splashScreenCheckBox->setChecked(settings.value("Splashscreen", true).toBool());
	ui->showGridCheckBox->setChecked(settings.value("ShowGrid", true).toBool());
	ui->openGLCheckBox->setChecked(settings.value("OpenGL", true).toBool());
}

void PreferencesDialog::applyChanges()
{
	QSettings settings("SPbSU", "QReal");
	settings.setValue("GridWidth", ui->gridWidthSlider->value());

	settings.setValue("ChooseDiagramsToSave", ui->chooseDiagramsToSaveCheckBox->isChecked());
	settings.setValue("DiagramCreateSuggestion", ui->diagramCreateCheckBox->isChecked());
	settings.setValue("PaletteTabSwitching", ui->paletteTabCheckBox->isChecked());
	settings.setValue("ChaoticEdition", ui->chaoticEditionCheckBox->isChecked());
	settings.setValue("SaveExitSuggestion", ui->saveExitCheckBox->isChecked());
	settings.setValue("Splashscreen", ui->splashScreenCheckBox->isChecked());
	settings.setValue("ActivateGrid", ui->activateGridCheckBox->isChecked());
	settings.setValue("ActivateAlignment", ui->activateAlignmentCheckBox->isChecked());
	settings.setValue("Antialiasing", ui->antialiasingCheckBox->isChecked());
	settings.setValue("ShowGrid", ui->showGridCheckBox->isChecked());
	settings.setValue("OpenGL", ui->openGLCheckBox->isChecked());

	mShowGridAction->setChecked(ui->showGridCheckBox->isChecked());
	mActivateGridAction->setChecked(ui->activateGridCheckBox->isChecked());
	mActivateAlignmentAction->setChecked(ui->activateAlignmentCheckBox->isChecked());
}

void PreferencesDialog::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void PreferencesDialog::on_okButton_clicked()
{
	applyChanges();
	close();
}

void PreferencesDialog::on_applyButton_clicked()
{
	applyChanges();
}

void PreferencesDialog::on_cancelButton_clicked()
{
	close();
}
