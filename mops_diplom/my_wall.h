#ifndef MY_WALL_H
#define MY_WALL_H

#include <QObject>
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

class My_Wall : public QObject
{
    Q_OBJECT
public:
    explicit My_Wall(QObject *parent = 0);
    void Set_Line (int x1, int y1, int x2, int y2);
    void Set_Line (QGraphicsLineItem *line_in);
    void Set_Color (QColor color_in);
    void Set_Height (double height_in);

    QGraphicsLineItem* Get_Line ();
    QColor Get_Color ();
    double Get_Height ();
    
signals:
    
public slots:

private:
     QGraphicsLineItem *line;
     QColor color;
     double height;
    
};

#endif // MY_WALL_H
