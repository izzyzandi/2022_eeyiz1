#include "mainwindow.h"
#include <QMessageBox>
#include <QApplication>

void MainWindow::handleButton() {
    QMessageBox msgBox;
    msgBox.setText("Button was clicked");
    msgBox.exec();
    emit statusUpdateMessage(QString("button was clicked!"), 0);
}

void MainWindow::handleButton2() {
    QMessageBox msgBox2;
    msgBox2.setText("Button 2 was clicked");
    msgBox2.exec();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
