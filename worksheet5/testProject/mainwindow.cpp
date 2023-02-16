#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./ui_optiondialog.h"
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClick);
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);

    /* create/allocate the ModelList */
    this->partList = new ModelPartList("PartsList");

    /* Link it to the treeview in the GUI */
    ui->treeView->setModel(this->partList);

    /*Manually create a model tree - they're better and flexible
    eg nested functions*/
    ModelPart* rootItem = this->partList->getRootItem();

    /* Add 3 top level items*/
    for (int i = 0; i < 3; i++) {
        /* Create strings for both data columns*/
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        /* Creat child item */
        ModelPart* childItem = new ModelPart({ name,visible });

        /*Append to tree top-level*/
        rootItem->appendChild(childItem);

        /* Add 5 sub-items*/
        for (int j = 0; j < 5; j++) {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");

            ModelPart* childChildItem = new ModelPart({ name,visible });

            /* Append to parent*/
            childItem->appendChild(childChildItem);
        }
    }
}

void MainWindow::handleButton() {
    QMessageBox msgBox;
    msgBox.setText("Button was clicked");
    msgBox.exec();
    emit statusUpdateMessage(QString("button was clicked!"), 0);
}

void MainWindow::handleButton2() {
    optionDialog dialog(this);
    optionDialog visible(this);
    optionDialog RGB1(this);
    optionDialog RGB2(this);
    optionDialog RGB3(this);



    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.objectNameChanged();
        QString RGB1 = dialog.getRGB1Value();
        QString RGB2 = dialog.getRGB1Value();
        QString RGB3 = dialog.getRGB1Value();
        bool Visible = dialog.isVisible();
        

        emit statusUpdateMessage(QString(name)+" " + RGB1+" " + RGB2+ " " + RGB3+" "+ (Visible ? "True" : "False"), 0);


        
        
        
    }
    else {
        emit statusUpdateMessage(QString("Dialog rejected"), 0);
    }

    
}

void MainWindow::handleTreeClick() {
    /* Get the index of the selected item*/
    QModelIndex index = ui->treeView->currentIndex();

    /* Get a pointer to the item from the index*/

    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    /* we will retrieve the name string from the internal QVariant data array*/
    QString text = selectedPart->data(0).toString();

    emit statusUpdateMessage(QString("The selected item is: ") + text, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C:\\",
        tr("STL Files(*.stl);;Text Files(*.txt)"));

    emit statusUpdateMessage(QString(fileName), 0);
}

