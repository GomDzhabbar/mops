#include "mygv.h"

MYGV::MYGV(QWidget *parent)
    : QGraphicsView(parent)
{

    MyFlag = true;
    counter = 0;
    flag = false;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,640,480);
    //setSceneRect(0,0,640,480);
   // scene->setSceneRect(0, 0, this->width(), this->height());
    setScene(scene);
    //scene->setBackgroundBrush(Qt::blue);
   // scene->addLine(0, 0, 640,480);

    qDebug() << "SCENA";
    qDebug() << scene->sceneRect().width() << " " << scene->sceneRect().height();
    qDebug() << "VIEW";
    qDebug() << this->sceneRect().width() << " " << this->sceneRect().height();
}

MYGV::MYGV(int abc)
{
    MyFlag = true;
    counter = 0;
    flag = false;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,640,480);
    //setSceneRect(0,0,640,480);
   // scene->setSceneRect(0, 0, this->width(), this->height());
    setScene(scene);
    //scene->setBackgroundBrush(Qt::blue);
    QPen pen;
    pen.setWidth(5);
   // scene->addLine(0, 0, 640,480,pen);


    qDebug() << "SCENA";
    qDebug() << scene->sceneRect().width() << " " << scene->sceneRect().height();
    qDebug() << "VIEW";
    qDebug() << this->sceneRect().width() << " " << this->sceneRect().height();
}

void MYGV::mousePressEvent(QMouseEvent *event)
{
    if(MyFlag)
    {
    counter++;

    //scene->addLine(0,0,0,0);

    qDebug() << "asdfsadf";
    if(counter == 1)
    {
        Start_x = event->x();
        qDebug()<< "Start_x " << Start_x;
        Start_y = event->y();
        qDebug()<< "Start_y " << Start_y;
    }
    if(counter == 2)
    {
        End_x = event->x();
        qDebug()<< "End_x " << End_x;
        End_y = event->y();
         qDebug()<< "End_y " << End_y;
        counter = 0;
        flag = true;
        scene->addLine(this->Start_x , this->Start_y, this->End_x , this->End_y, Pen);
        this->setScene(this->scene);

    }
    if(event->button()== Qt::LeftButton)
        qDebug("LeftButton");
    if(event->button()==Qt::RightButton)
        qDebug("RightButton");
    }


}
void MYGV::mouseMoveEvent(QMouseEvent *event)
{
   // qDebug("22222222222");
}


void MYGV::SetPen(QPen TPen)
{
    Pen = TPen;
}

void MYGV::ClearScene()
{
    QList<QGraphicsItem *> list;
    list = scene->items();
    QVector <QGraphicsItem *>  Vector = list.toVector();
    int size = Vector.size();
    for(int i = 0; i < size; i++)
    {
        scene->removeItem(Vector[i]);
    }
}

void MYGV::MoveScene()
{
    QList<QGraphicsItem *> list;
    list = scene->items();
    QVector <QGraphicsItem *>  Vector = list.toVector();
    int size = Vector.size();
    for(int i = 0; i < size; i++)
    {
        Vector[i]->setFlag(QGraphicsItem::ItemIsMovable);
    }
     QGraphicsEllipseItem *ellips;

     QPen RedPen;
     RedPen.setColor(Qt::red);
     RedPen.setWidth(5);
     ellips = scene->addEllipse(150,150,100,100,RedPen);
     ellips->setFlag(QGraphicsItem::ItemIsMovable);
}

void MYGV::SetMyFlag(bool flag)
{
    MyFlag = flag;
}

MYGV::~MYGV()
{
}
