#include "optiondialog.h"
#include "ui_optiondialog.h"

optionDialog::optionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::optionDialog)
{
    ui->setupUi(this);
}

optionDialog::~optionDialog()
{
    delete ui;
}

QString optionDialog::objectNameChanged() {
    return ui->name->text();
}

bool optionDialog::isVisible() {
    return ui->visible->checkState();

}

QString optionDialog::getRGB1Value() {
    return ui->RGB1->text();
}

QString optionDialog::getRGB2Value() {
    return ui->RGB2->text();
}

QString optionDialog::getRGB3Value() {
    return ui->RGB3->text();
}

void optionDialog::setObjectName(QString dialogg) {
    ui->name->setText(dialogg);
}

void optionDialog::setIsVisible(bool checkBoxx) {
    ui->visible->setChecked(checkBoxx);
}

void optionDialog::setRGB1Value(int RGB1_) {
    ui->RGB1->setValue(RGB1_);
}

void optionDialog::setRGB2Value(int RGB2_) {
    ui->RGB2->setValue(RGB2_);
}

void optionDialog::setRGB3Value(int RGB3_) {
    ui->RGB3->setValue(RGB3_);
}