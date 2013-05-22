#include "my_wall.h"

My_Wall::My_Wall(QObject *parent) :
    QObject(parent)
{
    line = new QGraphicsLineItem;

    height = 0;
}

void My_Wall::Set_Line(int x1, int y1, int x2, int y2)
{
    line->setLine(x1, y1, x2, y2);
}

void My_Wall::Set_Line (QGraphicsLineItem *line_in)
{
    line = line_in;
}

void My_Wall::Set_Color(QColor color_in)
{
    color = color_in;
}

void My_Wall::Set_Height(double height_in)
{
     height = height_in;
}

QGraphicsLineItem* My_Wall::Get_Line()
{
    return line;
}

QColor My_Wall::Get_Color()
{
    return color;
}

double My_Wall::Get_Height()
{
    return height;
}
