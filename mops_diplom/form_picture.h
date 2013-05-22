#ifndef FORM_PICTURE_H
#define FORM_PICTURE_H

#include <QWidget>
#include <QFileDialog>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>

namespace Ui {
class Form_Picture;
}

class Form_Picture : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form_Picture(QWidget *parent = 0);
    Ui::Form_Picture *ui;
    QString Get_WayFile ();
    bool flag_ok;
    ~Form_Picture();
    
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    QString WayFile;
};

#endif // FORM_PICTURE_H
