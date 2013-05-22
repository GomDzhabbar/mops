#ifndef FORM_WALL_H
#define FORM_WALL_H

#include <QWidget>
#include <QColorDialog>
#include <QMessageBox>

namespace Ui {
class Form_wall;
}

class Form_wall : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form_wall(QWidget *parent = 0);
    QColor Get_color ();
    bool flag_ok;
    Ui::Form_wall *ui;
    ~Form_wall();
    
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    QColor color;
    QColorDialog *Color_dialog;
};

#endif // FORM_WALL_H
