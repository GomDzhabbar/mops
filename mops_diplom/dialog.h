#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QSize>
#include <QColorDialog>
#include <QMenuBar>
#include "ui_form_wall.h"
#include "form_wall.h"
#include "my_wall.h"
#include "my_picture.h"
#include "ui_form_picture.h"
#include "form_picture.h"
#include <QFileDialog>
#include <QRgb>
#include <QMessageBox>




namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    bool eventFilter(QObject *target, QEvent *event);
    bool sceneEventFilter( QGraphicsItem *pWatched, QEvent* pEvent);


    int Start_x;
    int Start_y;
    int End_x;
    int End_y;

    int counter;

    bool MyFlag;

    //флаги и счетчики для стен
    int counter_for_drawwall;
    bool flag_for_wall;
    bool Flag_for_drawwall;

    //флаги и счетчики для картин
    int counter_for_picture;
    bool flag_for_picture;
    bool Flag_for_picture;

    bool Flag_for_OriginPoint; //Флаг на нажатие кнопки начала обзора
    bool flag_for_OriginPoint; //Флаг нарисована точка начала обзора или нет

    QPen Pen;

    ~Dialog();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

public slots:
    void Load_MyScene();
    void Save_MyScene();
    void Edit_param_wall();
    void Delete_wall();
    void Edit_param_picture();
    void Delete_picture();
    void About_program();
    void Instructions_user();
    void Delete_Point_Origin();


private:
    Ui::Dialog *ui;
    QGraphicsLineItem *line_wall;
    QGraphicsLineItem *line_picture;
    Form_wall *form_wall;
    Form_wall *form_wall_edit;
    Form_Picture *form_picture;
    Form_Picture *form_picture_edit;
    QGraphicsEllipseItem *Point_Origin;
    QGraphicsItem *item;


    QVector <My_Wall *>  Vector_MyWall; // вектор для стен
    QVector <My_Picture *>  Vector_MyPicture; // вектор для картин

    QGraphicsScene scene;

protected:
    void mousePressEvent ( QMouseEvent * event );
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // DIALOG_H
