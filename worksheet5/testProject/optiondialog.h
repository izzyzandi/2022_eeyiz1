#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class optionDialog;
}

class optionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit optionDialog(QWidget *parent = nullptr);
    ~optionDialog();

    QString objectNameChanged();
    bool isVisible();
    QString getRGB1Value();
    QString getRGB2Value();
    QString getRGB3Value();

    void setObjectName(QString dialogg);
    void setIsVisible(bool checkBoxx);
    void setRGB1Value(int RGB1);
    void setRGB2Value(int RGB2);
    void setRGB3Value(int RGB3);


private:
    Ui::optionDialog *ui;
};

#endif // OPTIONDIALOG_H
