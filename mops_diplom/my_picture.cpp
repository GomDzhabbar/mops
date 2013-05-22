#include "my_picture.h"

My_Picture::My_Picture(QObject *parent) :
    QObject(parent)
{
    line = new QGraphicsLineItem;
}

void My_Picture::Set_Line(int x1, int y1, int x2, int y2)
{
    line->setLine(x1, y1, x2, y2);
}

void My_Picture::Set_Line (QGraphicsLineItem *line_in)
{
    line = line_in;
}

void My_Picture::Set_WayFile(QString str)
{
    WayFile = str;
}

void My_Picture::Set_Specification_Picture(QString Specification)
{
    Specification_Picture = Specification;
}


QGraphicsLineItem* My_Picture::Get_Line()
{
    return line;
}

QString My_Picture::Get_WayFile()
{
    return WayFile;
}

QString My_Picture::Get_Specification_Picture()
{
    return Specification_Picture;
}
