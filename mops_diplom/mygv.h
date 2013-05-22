#ifndef MYGV_H
#define MYGV_H
#include <QGraphicsView>
#include <QMouseEvent>
#include <QString>
#include <QDebug>
#include <QGraphicsItem>
#include <QVector>

class MYGV : public QGraphicsView
{
    Q_OBJECT
public:
    int Start_x;
    int Start_y;
    int End_x;
    int End_y;

    int counter;
    bool flag;
    bool MyFlag;

    QPen Pen;

   QGraphicsScene *scene;



    MYGV(QWidget *parent = 0);
    MYGV(int abc);
    void mousePressEvent(QMouseEvent *event);       //переопредиляем нужные эвенты
    void mouseMoveEvent(QMouseEvent *event);
    void SetPen(QPen TPen);
    void ClearScene ();
    void MoveScene ();
    void SetMyFlag (bool flag);



    ~MYGV();
};

#endif // MYGV_H
