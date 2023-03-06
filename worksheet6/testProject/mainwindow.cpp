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
    ui->treeView->addAction(ui->actionItem_Options);
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
    // link a render window with qt widget
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    ui->vtkWidget->setRenderWindow(renderWindow);
    // add a renderer
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    /* Create an object and add to renderer
    it will copy and paste cylinder example*/
    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);

    // mapper pushes geometry into graphics library and can do colour mapping
    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    // actor is a grouping mechanism. besides geometry mapper, it also has a property, transformation matrix 
    // and texture map
    // set colour and rotate is around the XY axes
    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1, 0, 0.35);
    cylinderActor->RotateX(30);
    cylinderActor->RotateY(-45);

    renderer->AddActor(cylinderActor);

    // reset camera
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();
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
        int RGB1 = dialog.getRGB1Value();
        int RGB2 = dialog.getRGB1Value();
        int RGB3 = dialog.getRGB1Value();
        bool Visible = dialog.isVisible();
        

        emit statusUpdateMessage(QString(name)+" " + QString::number(RGB1) +" " + QString::number(RGB2) + " " + QString::number(RGB3) +" "+ (Visible ? "True" : "False"), 0);


        
        
        
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
    /* Get the index of the selected item*/
    QModelIndex index = ui->treeView->currentIndex();

    /* Get a pointer to the item from the index*/

    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    selectedPart->set(0, fileName);
    emit statusUpdateMessage(QString(fileName), 0);
}

void MainWindow::on_actionItem_Options_triggered()
{
    optionDialog dialog(this);
    optionDialog visible(this);
    optionDialog RGB1(this);
    optionDialog RGB2(this);
    optionDialog RGB3(this);

    /* Get the index of the selected item*/
    QModelIndex index = ui->treeView->currentIndex();
    /* Get a pointer to the item from the index*/
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    dialog.setObjectName(selectedPart->data(0).toString());
    dialog.setRGB1Value(selectedPart->getColourR());
    dialog.setRGB2Value(selectedPart->getColourG());
    dialog.setRGB3Value(selectedPart->getColourB());
    dialog.setIsVisible(selectedPart->get_visible());
    

    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.objectNameChanged();
        int RGB1 = dialog.getRGB1Value();
        int RGB2 = dialog.getRGB2Value();
        int RGB3 = dialog.getRGB3Value();
        bool Visible = dialog.isVisible();

  
        
        

        selectedPart->set(0, name);
        selectedPart->setColour(RGB1, RGB2,RGB3);
        selectedPart->setVisible(Visible);
        if (Visible)
        {
            selectedPart->set(1, "true");
        }
        else
        {
            selectedPart->set(1, "false");
        }


    
        emit statusUpdateMessage(QString(name) + " " + QString::number(RGB1) + " " + QString::number(RGB2) + " " + QString::number(RGB3) + " " + (Visible ? "True" : "False"), 0);





    }
    else {
        emit statusUpdateMessage(QString("Dialog rejected"), 0);
    }
}