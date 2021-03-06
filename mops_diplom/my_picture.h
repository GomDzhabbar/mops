#ifndef MY_PICTURE_H
#define MY_PICTURE_H

#include <QObject>
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

class My_Picture : public QObject
{
    Q_OBJECT
public:
    explicit My_Picture(QObject *parent = 0);
    void Set_Line (int x1, int y1, int x2, int y2);
    void Set_Line (QGraphicsLineItem *line_in);
    void Set_WayFile (QString str);
    void Set_Specification_Picture(QString Specification);

    QGraphicsLineItem* Get_Line ();
    QString Get_WayFile ();
    QString Get_Specification_Picture();
    
signals:
    
public slots:

private:
     QGraphicsLineItem *line;
     QString WayFile;
     QString Specification_Picture;
    
};

#endif // MY_PICTURE_H
