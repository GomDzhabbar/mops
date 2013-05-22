#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
//    setMouseTracking(true);
//    ui->graphicsView->setMouseTracking(true);
//    ui->graphicsView->viewport()->setMouseTracking(true);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    form_wall = new Form_wall;
    form_wall_edit = new Form_wall;
    form_picture = new Form_Picture;
    form_picture_edit = new Form_Picture;

    Point_Origin = new  QGraphicsEllipseItem;

    ui->pushButton->setCheckable(true); // делаем кнопку стены триггерной
    ui->pushButton_2->setCheckable(true);
    ui->pushButton_5->setCheckable(true);
    scene.setSceneRect(0,0,640,480);
    ui->graphicsView->setSceneRect(0,0,640,480);
    ui->graphicsView->setScene(&scene);
//    ellipse = scene.addEllipse(-50,-50,100,100);
//    ellipse->setFlag(QGraphicsItem::ItemIsMovable);
//    ellipse->installSceneEventFilter(ellipse);

  //  ellipse = scene.addEllipse(QRectF(50, 50, 200, 200));
 //line = scene.addLine(QLineF(50, 50, 200, 200));
// line->setFlag(QGraphicsItem::ItemIsMovable,true);
// line->installSceneEventFilter(line);


 //   ellipse->setFlag(QGraphicsItem::ItemIsMovable);


   // line->installSceneEventFilter(ellipse);
    // line's events are filtered by ellipse's sceneEventFilter() function.

  //  ellipse->installSceneEventFilter(line);
    // ellipse's events are filtered by line's sceneEventFilter() function.



    ui->graphicsView->installEventFilter(this);
    ui->graphicsView->viewport()->installEventFilter(this);
    form_wall->ui->pushButton_2->installEventFilter(this);    
    form_wall->ui->pushButton_3->installEventFilter(this);
    form_wall_edit->ui->pushButton_2->installEventFilter(this);
    form_picture->ui->pushButton->installEventFilter(this);
    form_picture->ui->pushButton_2->installEventFilter(this);
    form_picture_edit->ui->pushButton->installEventFilter(this);

    //установка флагов в положение "неактивен", обнуление счетчиков
    // для стен
    flag_for_wall = false;
    Flag_for_drawwall = false;
    counter_for_drawwall = 0;

    //для картины
    flag_for_picture = false;
    Flag_for_picture = false;
    counter_for_picture = 0;

    //для точки начала осмотра
    Flag_for_OriginPoint = false;
    flag_for_OriginPoint = false;

    QMenuBar *menuBar = new QMenuBar();
    QMenu *fileMenu = new QMenu(tr("&Файл"), this);
    fileMenu->addAction("&Открыть", this, SLOT(Load_MyScene()), Qt::CTRL + Qt::Key_O);
    fileMenu->addAction("&Сохранить", this, SLOT(Save_MyScene()), Qt::CTRL + Qt::Key_S);
    menuBar->addMenu(fileMenu);

    QMenu *helpMenu = new QMenu(tr("&Справка"), this);
    helpMenu->addAction("&О программе", this, SLOT(About_program()), Qt::Key_F1);
    helpMenu->addAction("&Инструкция пользователя", this, SLOT(Instructions_user()), Qt::Key_F2);
    menuBar->addMenu(helpMenu);
    helpMenu->setPalette(*(new QPalette(Qt::red)));



    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    setLayout(mainLayout);

    QString str;
    str = "Макет Иванова\nМакет Петрова\nДомашний музей v1.0\nКартинная галерея\nНовая галерея\nВыставочный комплекс\nМузей чайника";
    ui->textEdit->setText(str);



}

void Dialog::About_program()
{
    QMessageBox::information(this, "Информация о программе", "Конструктор для создания виртуальной галереи современного искусства.\nВерсия 1.0\nШеманаев Дмитрий.");
}

void Dialog::Instructions_user()
{
    QMessageBox::information(this, "Инструкция пользователя", "Инструкция для пользователя");
}

void Dialog::Save_MyScene()
{
    //Для стен
    //для перемещенных объектов на сцене меняем координаты в хранилище
    QList<QGraphicsItem *> list;
    list = scene.items();
    QVector <QGraphicsItem *>  Vector_Graphics = list.toVector();
    int size_VG = Vector_Graphics.size();
    int size_VW = Vector_MyWall.size();

    for(int i = 0; i < size_VG; i++)
    {
        for(int j = 0; j < size_VW; j++)
        {
            if(Vector_MyWall[j] != NULL)
            {
                if(Vector_Graphics[i] == Vector_MyWall[j]->Get_Line())
                {
                    QPointF point = Vector_Graphics[i]->pos();
                    QLineF line = Vector_MyWall[j]->Get_Line()->line();
                    QPen pen = Vector_MyWall[j]->Get_Line()->pen();
                    Vector_MyWall[j]->Set_Line(line.x1() + point.x(), line.y1() + point.y(), line.x2() + point.x(), line.y2() + point.y());
                    Vector_MyWall[j]->Get_Line()->setPen(pen);
                }
            }
        }
    }

    //Для картин
    //для перемещенных объектов на сцене меняем координаты в хранилище
    int size_VP = Vector_MyPicture.size();

    for(int i = 0; i < size_VG; i++)
    {
        for(int j = 0; j < size_VP; j++)
        {
            if(Vector_MyPicture[j] != NULL)
            {
                if(Vector_Graphics[i] == Vector_MyPicture[j]->Get_Line())
                {
                    QPointF point = Vector_Graphics[i]->pos();
                    QLineF line = Vector_MyPicture[j]->Get_Line()->line();
                    QPen pen = Vector_MyPicture[j]->Get_Line()->pen();
                    Vector_MyPicture[j]->Set_Line(line.x1() + point.x(), line.y1() + point.y(), line.x2() + point.x(), line.y2() + point.y());
                    Vector_MyPicture[j]->Get_Line()->setPen(pen);
                }
            }
        }
    }

    //меняем координаты для точки начала осмотра
    QPointF point = Point_Origin->pos();
    QPen pen(Qt::black);
    QBrush brush(Qt::black);
    Point_Origin = scene.addEllipse(Point_Origin->rect().x() + point.x(), Point_Origin->rect().y() + point.y(), 20, 20, pen, brush);

    QString str_save_file = QFileDialog::getSaveFileName(0,"Сохранить проект","","*.txt");
    str_save_file+=".txt";
    qDebug() << str_save_file;
    QFile file(str_save_file);
    file.open(QIODevice::Append | QIODevice::WriteOnly);
    QTextStream out(&file);
    //Выводим стены
    out << "Line" << "\r\n";
    int size_wall = Vector_MyWall.size();
    for(int i = 0; i < size_wall; i++)
    {
        if(Vector_MyWall[i] != NULL)
        {
            // Выводим координаты стены (начало и конец линии)
            QLineF line_wall = Vector_MyWall[i]->Get_Line()->line();
            out << line_wall.x1()<< "\t";
            out << line_wall.y1()<< "\t";
            out << line_wall.x2()<< "\t";
            out << line_wall.y2()<< "\t";

            // Выводим цвет стены
            // В первый параметр передается значение красного цвета, во второй - зеленого, в третий - синего,
            //а в четвертый - уровень прозрачности. Например:  Color colorBlue(0, 0, 255, 128);
            QColor color = Vector_MyWall[i]->Get_Color();
            out << color.red() << "\t";
            out << color.green() << "\t";
            out << color.blue() << "\t";
            out << color.alpha() << "\t";

            // Выводим высоту стены
            out << Vector_MyWall[i]->Get_Height() << "\t";
            out << "\r\n";
        }
    }

    //Вывод картины
    out << "Picture" << "\r\n";
    int size_picture = Vector_MyPicture.size();
    for (int i = 0; i < size_picture; i++)
    {
        if(Vector_MyPicture[i] != NULL)
        {
            // Выводим координаты картины (начало и конец линии)
            QLineF line_picture = Vector_MyPicture[i]->Get_Line()->line();
            out << line_picture.x1()<< "\t";
            out << line_picture.y1()<< "\t";
            out << line_picture.x2()<< "\t";
            out << line_picture.y2()<< "\t";

            //Выводим местораположения файла для картины
            out << Vector_MyPicture[i]->Get_WayFile() << "\t";

            //Выводим описание для картины
            out << Vector_MyPicture[i]->Get_Specification_Picture() << "\t";
            out << "\r\n";
        }
    }

    //Выводим точку начала осмотра
    out << "Point origin" << "\r\n" ;
    out << Point_Origin->rect().x() << "\t" << Point_Origin->rect().y() << "\t";
    out << "\r\n";

    out << "The End";
    file.close();
    return;
}

void Dialog::Load_MyScene()
{
    // полная очистка области рисования
    QList<QGraphicsItem *> list;
    list = scene.items();
    QVector <QGraphicsItem *>  Vector_Graphics = list.toVector();
    int size = Vector_Graphics.size();
    for(int i = 0; i < size; i++)
    {
        scene.removeItem(Vector_Graphics[i]);
    }
    //очитка вектора для стен
    Vector_MyWall.clear();
    //Сброс флагов и счетчиков для стен
    flag_for_wall = false;
    Flag_for_drawwall = false;
    counter_for_drawwall = 0;

    //очитка вектора для картин
    Vector_MyPicture.clear();
    //Сброс флагов и счетчиков для картин
    flag_for_picture = false;
    Flag_for_picture = false;
    counter_for_picture = 0;

    //Сброс флага, что точка начала обзора нарисована
    flag_for_OriginPoint = false;



    QString str_load_file = QFileDialog::getOpenFileName(0,"Откртыть проект","","*.txt");
    QFile file(str_load_file);
    file.open(QIODevice::ReadOnly);
    QTextStream out(&file);
    QString str;
    int X1, Y1, X2, Y2, Red, Green, Blue, Alfa, Height;
    int Point_Origin_X, Point_Origin_Y;
    QString WayFile, Specification_Picture, temp;
    str = out.readLine();
    int counter = 0;
    if(str == "Line")
    {
        while(1)
        {
            str = out.readLine();
            counter = 0;
            temp.clear();
            if(str == "Picture")
                break;
            int size = str.size();
            qDebug() << X1 << Y1 << X2 << Y2 << Red << Green << Blue << Alfa << Height;
            for(int i = 0; i <= size; i++)
            {
                if(str[i] == '\t' || str[i] == '\n')
                {
                    counter++;
                    if(counter == 9)
                        qDebug() << "sdf" << temp;
                    switch(counter)
                    {
                        case 1: X1 = temp.toInt(); temp.clear(); break;
                        case 2: Y1 = temp.toInt(); temp.clear(); break;
                        case 3: X2 = temp.toInt(); temp.clear(); break;
                        case 4: Y2 = temp.toInt(); temp.clear(); break;
                        case 5: Red = temp.toInt(); temp.clear(); break;
                        case 6: Green = temp.toInt(); temp.clear(); break;
                        case 7: Blue = temp.toInt(); temp.clear(); break;
                        case 8: Alfa = temp.toInt(); temp.clear(); break;
                        case 9: Height = temp.toInt(); temp.clear(); break;
                    }
                    if(counter == 9)
                    {
                        My_Wall *my_wall = new My_Wall;
                        my_wall->Set_Line(X1, Y1, X2, Y2);
                        QColor color;
                        color.setRgb(Red, Green, Blue, Alfa);
                        my_wall->Set_Color(color);
                        my_wall->Set_Height(Height);
                        Vector_MyWall.push_back(my_wall);
                    }
                }
                else
                    temp += str[i];
            }
        }
        while(1)
        {
            str = out.readLine();
            counter = 0;
            temp.clear();
            if(str == "Point origin")
                break;
            int size = str.size();
            qDebug() << X1 << Y1 << X2 << Y2 << WayFile;
            for(int i = 0; i <= size; i++)
            {
                if(str[i] == '\t' || str[i] == '\n')
                {
                    counter++;
                    if(counter == 6)
                        qDebug() << "sdf" << temp;
                    switch(counter)
                    {
                        case 1: X1 = temp.toInt(); temp.clear(); break;
                        case 2: Y1 = temp.toInt(); temp.clear(); break;
                        case 3: X2 = temp.toInt(); temp.clear(); break;
                        case 4: Y2 = temp.toInt(); temp.clear(); break;
                        case 5: WayFile = temp; temp.clear(); break;
                        case 6: Specification_Picture = temp; temp.clear(); break;
                    }
                    if(counter == 6)
                    {
                        My_Picture * my_picture = new My_Picture;
                        my_picture->Set_Line(X1, Y1, X2, Y2);
                        my_picture ->Set_WayFile(WayFile);
                        my_picture->Set_Specification_Picture(Specification_Picture);
                        Vector_MyPicture.push_back(my_picture);
                    }
                }
                else
                    temp += str[i];
            }
        }
        str = out.readLine();
        temp.clear();
        int size = str.size();
        counter = 0;
        for(int i = 0; i <= size; i++)
        {
            if(str[i] == '\t' || str[i] == '\n')
            {
                counter++;
                switch(counter)
                {
                    case 1: Point_Origin_X = temp.toInt(); temp.clear(); break;
                    case 2: Point_Origin_Y = temp.toInt(); temp.clear(); break;
                }
                if(counter == 2)
                {
                    QPen pen(Qt::black);
                    QBrush brush(Qt::black);
                    Point_Origin = scene.addEllipse(Point_Origin_X, Point_Origin_Y, 20, 20, pen, brush);
                    Point_Origin->setFlag(QGraphicsItem::ItemIsMovable);
                    flag_for_OriginPoint = true;
                }
            }
            else
                temp += str[i];
        }


    }
    file.close();

    int size_VP = Vector_MyPicture.size();
    int size_VW = Vector_MyWall.size();
    //полностью перерисовываем стены в связи с возможными изменения данных в хранилище
    for(int j = 0; j < size_VW; j++)
    {
        if(Vector_MyWall[j] != NULL)
        {
            QLineF line = Vector_MyWall[j]->Get_Line()->line();
            QPen pen = Vector_MyWall[j]->Get_Line()->pen();
            pen.setColor(Vector_MyWall[j]->Get_Color());
            pen.setWidth(4);
            QGraphicsLineItem *line_item = scene.addLine(line, pen);
            Vector_MyWall[j]->Set_Line(line_item);
            line_item->setFlag(QGraphicsItem::ItemIsMovable);
        }
    }
     //полностью перерисовываем картины в связи с возможными изменения данных в хранилище
    for(int j = 0; j < size_VP; j++)
    {
        if(Vector_MyPicture[j] != NULL)
        {
            QLineF line = Vector_MyPicture[j]->Get_Line()->line();
            QPen pen = Vector_MyPicture[j]->Get_Line()->pen();
            pen.setColor(Qt::red);
            pen.setWidth(6);
            QGraphicsLineItem *line_item = scene.addLine(line, pen);
            Vector_MyPicture[j]->Set_Line(line_item);
            line_item->setFlag(QGraphicsItem::ItemIsMovable);
        }
    }
}


// стена
void Dialog::on_pushButton_clicked()
{
    if(ui->pushButton->isChecked())
    {
        Pen.setWidth(4);
        Pen.setColor(Qt::black);
        Flag_for_drawwall = true;
        ui->pushButton_2->setChecked(false);
        ui->pushButton_5->setChecked(false);
        Flag_for_picture = false;
    }
    else
    {
        Pen.setWidth(1);
        Pen.setColor(Qt::black);
        Flag_for_drawwall = false;
    }

}

//картина
void Dialog::on_pushButton_2_clicked()
{
    if(ui->pushButton_2->isChecked())
    {
        Pen.setWidth(6);
        Pen.setColor(Qt::red);
        Flag_for_picture = true;
        ui->pushButton->setChecked(false);
        ui->pushButton_5->setChecked(false);
        Flag_for_drawwall = false;
    }
    else
    {
        Pen.setWidth(1);
        Pen.setColor(Qt::black);
        Flag_for_picture = false;
    }



}

void Dialog::on_pushButton_3_clicked()
{
    //uuu->ClearScene();
    ui->graphicsView->viewport()->removeEventFilter(this);
}

void Dialog::on_pushButton_4_clicked() // очистка окна
{
    ui->pushButton->setChecked(false);
    ui->pushButton_2->setChecked(false);
    ui->pushButton_5->setChecked(false);

    // полная очистка области рисования
    QList<QGraphicsItem *> list;
    list = scene.items();
    QVector <QGraphicsItem *>  Vector_Graphics = list.toVector();
    int size = Vector_Graphics.size();
    for(int i = 0; i < size; i++)
    {
        scene.removeItem(Vector_Graphics[i]);
    }
    //очитка вектора для стен
    Vector_MyWall.clear();
    //Сброс флагов и счетчиков для стен
    flag_for_wall = false;
    Flag_for_drawwall = false;
    counter_for_drawwall = 0;

    //очитка вектора для картин
    Vector_MyPicture.clear();
    //Сброс флагов и счетчиков для картин
    flag_for_picture = false;
    Flag_for_picture = false;
    counter_for_picture = 0;

    delete Point_Origin;
    //Сброс флагов для точки начала осмотра
    Flag_for_OriginPoint = false;
    flag_for_OriginPoint = false;

}

void Dialog::on_pushButton_5_clicked()
{
    if(ui->pushButton_5->isChecked())
    {
        Flag_for_OriginPoint = true;
        ui->pushButton->setChecked(false);
        ui->pushButton_2->setChecked(false);
    }
    else
    {
        Flag_for_OriginPoint = false;
    }

//    //Для стен
//    //для перемещенных объектов на сцене меняем координаты в хранилище
//    QList<QGraphicsItem *> list;
//    list = scene.items();
//    QVector <QGraphicsItem *>  Vector_Graphics = list.toVector();
//    int size_VG = Vector_Graphics.size();
//    int size_VW = Vector_MyWall.size();

//    for(int i = 0; i < size_VG; i++)
//    {
//        for(int j = 0; j < size_VW; j++)
//        {
//            if(Vector_MyWall[j] != NULL)
//            {
//                if(Vector_Graphics[i] == Vector_MyWall[j]->Get_Line())
//                {
//                    QPointF point = Vector_Graphics[i]->pos();
//                    QLineF line = Vector_MyWall[j]->Get_Line()->line();
//                    QPen pen = Vector_MyWall[j]->Get_Line()->pen();
//                    Vector_MyWall[j]->Set_Line(line.x1() + point.x(), line.y1() + point.y(), line.x2() + point.x(), line.y2() + point.y());
//                    Vector_MyWall[j]->Get_Line()->setPen(pen);
//                }
//            }
//        }
//    }


//    //полностью перерисовываем стены в связи с возможными изменения данных в хранилище
//    list = scene.items();
//    QVector <QGraphicsItem *>  Vector = list.toVector();
//    int size = Vector.size();
//    for(int i = 0; i < size; i++)
//    {
//        scene.removeItem(Vector[i]);
//    }

//    for(int j = 0; j < size_VW; j++)
//    {
//        if(Vector_MyWall[j] != NULL)
//        {
//            QLineF line = Vector_MyWall[j]->Get_Line()->line();
//            QPen pen = Vector_MyWall[j]->Get_Line()->pen();
//            QGraphicsLineItem *line_item = scene.addLine(line, pen);
//            Vector_MyWall[j]->Set_Line(line_item);
//            line_item->setFlag(QGraphicsItem::ItemIsMovable);
//        }
//    }


//    //Для картин
//    //для перемещенных объектов на сцене меняем координаты в хранилище
//    int size_VP = Vector_MyPicture.size();

//    for(int i = 0; i < size_VG; i++)
//    {
//        for(int j = 0; j < size_VP; j++)
//        {
//            if(Vector_MyPicture[j] != NULL)
//            {
//                if(Vector_Graphics[i] == Vector_MyPicture[j]->Get_Line())
//                {
//                    QPointF point = Vector_Graphics[i]->pos();
//                    QLineF line = Vector_MyPicture[j]->Get_Line()->line();
//                    QPen pen = Vector_MyPicture[j]->Get_Line()->pen();
//                    Vector_MyPicture[j]->Set_Line(line.x1() + point.x(), line.y1() + point.y(), line.x2() + point.x(), line.y2() + point.y());
//                    Vector_MyPicture[j]->Get_Line()->setPen(pen);
//                }
//            }
//        }
//    }


//    //полностью перерисовываем картины в связи с возможными изменения данных в хранилище
//    for(int j = 0; j < size_VP; j++)
//    {
//        if(Vector_MyPicture[j] != NULL)
//        {
//            QLineF line = Vector_MyPicture[j]->Get_Line()->line();
//            QPen pen = Vector_MyPicture[j]->Get_Line()->pen();
//            QGraphicsLineItem *line_item = scene.addLine(line, pen);
//            Vector_MyPicture[j]->Set_Line(line_item);
//            line_item->setFlag(QGraphicsItem::ItemIsMovable);
//        }
//    }
}

void Dialog::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "Начальные "<< event->x() << "  " << event->y();
    QPoint globalPos = this->mapToGlobal( event->pos() );
    qDebug() << "Переведенные в глобальные координаты экрана"<< globalPos.x() << "  " << globalPos.y();
    QPoint scenePos = ui->graphicsView->mapFromGlobal( globalPos );
    qDebug() << "Переведенные в координаты виджета"<< scenePos.x() << "  " << scenePos.y();
    counter++;

    //scene->addLine(0,0,0,0);

    qDebug() << "asdfsadf";
    if(counter == 1)
    {
        Start_x = scenePos.x();
        qDebug()<< "Start_x " << Start_x;
        Start_y = scenePos.y();
        qDebug()<< "Start_y " << Start_y;
    }
//    if(counter == 2)
//    {
//        End_x = scenePos.x();
//        qDebug()<< "End_x " << End_x;
//        End_y = scenePos.y();
//         qDebug()<< "End_y " << End_y;
//        counter = 0;
//        flag = true;
//        QGraphicsLineItem *line;
//        Pen.setWidth(8);
//        line = scene.addLine(Start_x , Start_y, End_x , End_y, Pen);
//      // ui->graphicsView->setScene(&scene);
//        line->setFlag(QGraphicsItem::ItemIsMovable);

//    }
    if(event->button()== Qt::LeftButton)
        qDebug("LeftButton");
    if(event->button()==Qt::RightButton)
        qDebug("RightButton");
}



void Dialog::mouseMoveEvent(QMouseEvent* event)
{

    QPointF pos = ui->graphicsView->mapToScene(ui->graphicsView->viewport()->mapFromGlobal( QCursor::pos() ) );

    qDebug() << "YUYUYUYU" << pos.x() << "   " << pos.y();

    qDebug() << "Начальные "<< event->x() << "  " << event->y();
    QPoint globalPos = this->mapToGlobal( event->pos() );
    qDebug() << "Переведенные в глобальные координаты экрана"<< globalPos.x() << "  " << globalPos.y();
    QPoint scenePos = ui->graphicsView->mapFromGlobal( globalPos );
    qDebug() << "Переведенные в координаты виджета"<< scenePos.x() << "  " << scenePos.y();
//    qDebug() << event->x() << "  " << event->y();
//    qDebug() << "Начальные "<< event->x() << "  " << event->y();
//    QPoint globalPos = this->mapToGlobal( event->pos() );
//    qDebug() << "Переведенные в глобальные координаты экрана"<< globalPos.x() << "  " << globalPos.y();
//    QPoint scenePos = ui->graphicsView->mapFromGlobal( globalPos );
//    qDebug() << "Переведенные в координаты виджета"<< scenePos.x() << "  " << scenePos.y();
//    ui->label->setText(QString::number(scenePos.x())+"  "+QString::number(scenePos.y()));
}



bool Dialog::eventFilter(QObject *target, QEvent *event)
{
//  if (target==ui->graphicsView)
//  {
//      if(event->type() == QEvent::MouseMove)
//      {
//          qDebug() << "Вошел в фильтр событий - Движение";
//          QMouseEvent *MouseEvent = (QMouseEvent *)event;
//          qDebug() << MouseEvent->x() << "   " << MouseEvent->y();
//          return true;
//      }
//      if (event->type() == QEvent::MouseButtonPress)
//      {
//            QMouseEvent *MouseEvent = (QMouseEvent *)event;
//            qDebug() << MouseEvent->x() << "   " << MouseEvent->y();
//            //mouseMoveEvent (MouseEvent);

//            qDebug() << "Вошел в фильтр событий - Клик";

//            QTransform transform;
//            QGraphicsItem *item = scene.itemAt(MouseEvent->x()+10, MouseEvent->y(), transform);
//            QGraphicsLineItem *line_item = (QGraphicsLineItem*)item;
//            if(!line_item)
//                qDebug() << "YPA";

//            int size = Vector_MyWall.size();
//            for(int i = 0; i < size; i++)
//            {

//                if(Vector_MyWall[i]->Get_Line() == line_item)
//                    qDebug() << "YPAAAAAAAAAAAAAAAAA";
//            }


//              return true;
//       }
//      if(event->type() == QEvent::MouseButtonDblClick)
//      {
//          qDebug() << "Вошел в фильтр событий - Двойной клик";
//          return true;
//      }


// }
   //обращение непосредственно к области рисования

  if(target == ui->graphicsView->viewport() && Flag_for_OriginPoint)
  {
      QMouseEvent *MouseEvent = (QMouseEvent *)event;
      if (event->type() == QEvent::MouseButtonPress && MouseEvent->button() == Qt::LeftButton)
      {
          if(!flag_for_OriginPoint)
          {
              qDebug() <<MouseEvent->x() << "  "  << MouseEvent->y();
              QPen pen(Qt::black);
              QBrush brush(Qt::black);
              Point_Origin = scene.addEllipse(MouseEvent->x()-10, MouseEvent->y()-10, 20, 20, pen , brush);
              Point_Origin->setFlag(QGraphicsItem::ItemIsMovable);
              flag_for_OriginPoint = true;
          }
      }

  }


  if(target == ui->graphicsView->viewport() && !Flag_for_drawwall && !Flag_for_picture)
  {
      QMouseEvent *m_event = (QMouseEvent*)event;
      if (event->type() == QEvent::MouseButtonPress && m_event->button() == Qt::RightButton)
      {
            QMouseEvent *MouseEvent = (QMouseEvent *)event;
            qDebug() << MouseEvent->x() << "   " << MouseEvent->y();
            //mouseMoveEvent (MouseEvent);

            qDebug() << "Вошел в фильтр событий - Клик в области видимости";
            QTransform transform;
            QGraphicsItem *item = scene.itemAt(MouseEvent->x(), MouseEvent->y(), transform);
            QGraphicsLineItem *line_item = (QGraphicsLineItem*)item;
            QGraphicsEllipseItem *ellipse_item = (QGraphicsEllipseItem*)item;

            if(!line_item)
                qDebug() << "YPA";
            int size_VW = Vector_MyWall.size();
            for(int i = 0; i < size_VW; i++)
            {
                if(Vector_MyWall[i] != NULL)
                {
                    if(Vector_MyWall[i]->Get_Line() == line_item)
                    {
                        line_wall = line_item;
                        QMenu menu(this);
                        menu.addAction("Изменить параметры стены", this, SLOT(Edit_param_wall()));
                        menu.addAction("Удалить стену", this, SLOT(Delete_wall()));
                        menu.exec(MouseEvent->globalPos());
                    }
                }
            }

            int size_VP = Vector_MyPicture.size();
            for(int i = 0; i < size_VP; i++)
            {
                if(Vector_MyPicture[i] != NULL)
                {
                    if(Vector_MyPicture[i]->Get_Line() == line_item)
                    {
                        line_picture = line_item;
                        QMenu menu(this);
                        menu.addAction("Изменить параметры картины", this, SLOT(Edit_param_picture()));
                        menu.addAction("Удалить картину", this, SLOT(Delete_picture()));
                        menu.exec(MouseEvent->globalPos());
                    }
                }
            }
            if(Point_Origin == ellipse_item)
            {
                QMenu menu(this);
                menu.addAction("Удалить точку начала обзора", this, SLOT(Delete_Point_Origin()));
                menu.exec(MouseEvent->globalPos());
            }
      }
  }

  //рисуем стены
  if (target==ui->graphicsView->viewport() && Flag_for_drawwall)
  {
     // qDebug() << "ViewPort";
      if(event->type() == QEvent::MouseMove)
      {
          if(counter_for_drawwall == 1)
          {
            QMouseEvent *MouseEvent = (QMouseEvent *)event;
            qDebug() << "Зашел_3";
            if(flag_for_wall)
            {
                //поиск и удаление ненужной линии стены на области рисования
                QList<QGraphicsItem *> list;
                list = scene.items();
                QVector <QGraphicsItem *>  Vector = list.toVector();
                int size = Vector.size();
                for(int i = 0; i < size; i++)
                {

                    if(Vector[i] == line_wall)
                    {
                        scene.removeItem(Vector[i]);
                        qDebug() << "007";
                        break;
                    }
                }
                //поиск и удаление ненужной линии стены в векторе линий стены
                size = Vector_MyWall.size();
                for(int i = 0; i < size; i++)
                {
                    if(Vector_MyWall[i] != NULL)
                    {
                        if(Vector_MyWall[i]->Get_Line() == line_wall)
                        {
                            Vector_MyWall.remove(i);
                            qDebug() << "007";
                            break;
                        }
                    }
                }
            }
            End_x = MouseEvent->x();
            End_y = MouseEvent->y();
            line_wall = scene.addLine(Start_x, Start_y, End_x, End_y, Pen);
            My_Wall *my_wall = new My_Wall;
            my_wall->Set_Line(line_wall);
            my_wall->Set_Color(Pen.color());
            Vector_MyWall.push_back(my_wall);
            line_wall->setFlag(QGraphicsItem::ItemIsMovable); // возможность двигать
            flag_for_wall = true;
          }
          return true;
      }

      if (event->type() == QEvent::MouseButtonPress)
      {
            QMouseEvent *MouseEvent = (QMouseEvent *)event;
            if(MouseEvent->button() == Qt::LeftButton && counter_for_drawwall == 0)
            {
                Start_x = MouseEvent->x();
                Start_y = MouseEvent->y();
                counter_for_drawwall = 1;
                qDebug() << "Зашел_1";
            }

            qDebug() << "Клик мышки";
            qDebug() << MouseEvent->x() << "   " << MouseEvent->y();
            //mouseMoveEvent (MouseEvent);

            qDebug() << "Вошел в фильтр событий - Клик";
              return true;
       }

      if (event->type() == QEvent::MouseButtonRelease)
      {
          if(counter_for_drawwall == 1)
          {
            QMouseEvent *MouseEvent = (QMouseEvent *)event;
            if(MouseEvent->button() == Qt::LeftButton)
            {
                counter_for_drawwall = 0;
                flag_for_wall = false;
                form_wall->show();
            }
          }

      }

  }


  //рисуем картины
  if (target==ui->graphicsView->viewport() && Flag_for_picture)
  {
      if(event->type() == QEvent::MouseMove)
      {
          if(counter_for_picture == 1)
          {
            QMouseEvent *MouseEvent = (QMouseEvent *)event;
            qDebug() << "Зашел_3";
            if(flag_for_picture)
            {
                //поиск и удаление ненужной линии картины на области рисования
                QList<QGraphicsItem *> list;
                list = scene.items();
                QVector <QGraphicsItem *>  Vector = list.toVector();
                int size = Vector.size();
                for(int i = 0; i < size; i++)
                {

                    if(Vector[i] == line_picture)
                    {
                        scene.removeItem(Vector[i]);
                        qDebug() << "007";
                        break;
                    }
                }
                //поиск и удаление ненужной линии картины в векторе линий картин
                size = Vector_MyPicture.size();
                for(int i = 0; i < size; i++)
                {
                    if(Vector_MyPicture[i] != NULL)
                    {
                        if(Vector_MyPicture[i]->Get_Line() == line_picture)
                        {
                            Vector_MyPicture.remove(i);
                            break;
                        }
                    }
                }
            }
            End_x = MouseEvent->x();
            End_y = MouseEvent->y();
            line_picture = scene.addLine(Start_x, Start_y, End_x, End_y, Pen);
            My_Picture *my_picture = new My_Picture;
            my_picture->Set_Line(line_picture);
            //my_picture->Set_Color(Pen.color());
            Vector_MyPicture.push_back(my_picture);
            line_picture->setFlag(QGraphicsItem::ItemIsMovable); // возможность двигать
            flag_for_picture = true;
          }
          return true;
      }

      if (event->type() == QEvent::MouseButtonPress)
      {
            QMouseEvent *MouseEvent = (QMouseEvent *)event;
            if(MouseEvent->button() == Qt::LeftButton && counter_for_picture == 0)
            {
                Start_x = MouseEvent->x();
                Start_y = MouseEvent->y();
                counter_for_picture = 1;
                qDebug() << "Зашел_1";
            }

            qDebug() << "Клик мышки";
            qDebug() << MouseEvent->x() << "   " << MouseEvent->y();
            //mouseMoveEvent (MouseEvent);

            qDebug() << "Вошел в фильтр событий - Клик";
              return true;
       }

      if (event->type() == QEvent::MouseButtonRelease)
      {
          if(counter_for_picture == 1)
          {
            QMouseEvent *MouseEvent = (QMouseEvent *)event;
            if(MouseEvent->button() == Qt::LeftButton)
            {
                counter_for_picture = 0;
                flag_for_picture = false;
                form_picture->show();
            }
          }

      }

  }

  //Обработки нажатия кнокпи ОК на форме ввода параметров стены
  if(target ==  form_wall->ui->pushButton_2)
  {

      if (event->type() == QEvent::MouseButtonPress)
      {
          QColor color = form_wall->Get_color();
          //поиск и смена цвета линии стены на области рисования
          QList<QGraphicsItem *> list;
          list = scene.items();
          QVector <QGraphicsItem *>  Vector = list.toVector();
          int size = Vector.size();
          for(int i = 0; i < size; i++)
          {
              if(Vector[i] == line_wall)
              {
                  QGraphicsLineItem *line_temp = (QGraphicsLineItem*)Vector[i];
                  QPen pen_temp = line_temp->pen();
                  pen_temp.setColor(color);
                  line_temp->setPen(pen_temp);
                 // Vector[i] = line_temp;
              }
          }
          //поиск и смена цвета линии стены в хранилище
          size = Vector_MyWall.size();
          for(int i = 0; i < size; i++)
          {
              if(Vector_MyWall[i] != NULL)
              {
                if(Vector_MyWall[i]->Get_Line() == line_wall)
                {
                    QGraphicsLineItem *line_temp = Vector_MyWall[i]->Get_Line();
                    Vector_MyWall[i]->Set_Color(color);
                    Vector_MyWall[i]->Set_Height(form_wall->ui->doubleSpinBox->value());
                    QPen pen_temp = line_temp->pen();
                    pen_temp.setColor(color);
                    line_temp->setPen(pen_temp);
                }
              }
          }
      }
  }

  //Обработки нажатия кнокпи Отмена на форме ввода параметров стены
  if(target ==  form_wall->ui->pushButton_3)
  {

      if (event->type() == QEvent::MouseButtonPress)
      {
          //поиск и удаление линии стены на области рисования
          QList<QGraphicsItem *> list;
          list = scene.items();
          QVector <QGraphicsItem *>  Vector = list.toVector();
          int size = Vector.size();
          for(int i = 0; i < size; i++)
          {
              if(Vector[i] == line_wall)
              {
                  scene.removeItem(Vector[i]);
              }
          }
          //поиск и удаление линии стены в хранилище
          size = Vector_MyWall.size();
          for(int i = 0; i < size; i++)
          {
              if(Vector_MyWall[i] != NULL)
              {
                if(Vector_MyWall[i]->Get_Line() == line_wall)
                {
                    delete Vector_MyWall[i];
                    Vector_MyWall[i] = NULL;
                    break;
                }
              }
          }
      }
  }

  //Обработки нажатия кнокпи ОК на форме редактирования параметров стены
  if(target ==  form_wall_edit->ui->pushButton_2)
  {

      if (event->type() == QEvent::MouseButtonPress)
      {
          QColor color = form_wall_edit->Get_color();
          //поиск и смена цвета линии стены на области рисования
          QList<QGraphicsItem *> list;
          list = scene.items();
          QVector <QGraphicsItem *>  Vector = list.toVector();
          int size = Vector.size();
          for(int i = 0; i < size; i++)
          {
              if(Vector[i] == line_wall)
              {
                  QGraphicsLineItem *line_temp = (QGraphicsLineItem*)Vector[i];
                  QPen pen_temp = line_temp->pen();
                  pen_temp.setColor(color);
                  line_temp->setPen(pen_temp);
                 // Vector[i] = line_temp;
              }
          }
          //поиск и смена цвета линии стены в хранилище
          size = Vector_MyWall.size();
          for(int i = 0; i < size; i++)
          {
              if(Vector_MyWall[i] != NULL)
              {
                if(Vector_MyWall[i]->Get_Line() == line_wall)
                {
                    QGraphicsLineItem *line_temp = Vector_MyWall[i]->Get_Line();
                    Vector_MyWall[i]->Set_Color(color);
                    Vector_MyWall[i]->Set_Height(form_wall_edit->ui->doubleSpinBox->value());
                    QPen pen_temp = line_temp->pen();
                    pen_temp.setColor(color);
                    line_temp->setPen(pen_temp);
                }
              }
          }
      }
  }


  //Обработки нажатия кнокпи ОК на форме ввода параметров картины
  if(target ==  form_picture->ui->pushButton)
  {

      if (event->type() == QEvent::MouseButtonPress)
      {
          //поиск и запись месторасположения файла для картины
          int size = Vector_MyPicture.size();
          for(int i = 0; i < size; i++)
          {
              if(Vector_MyPicture[i] != NULL)
              {
                if(Vector_MyPicture[i]->Get_Line() == line_picture)
                {
                    Vector_MyPicture[i]->Set_WayFile(form_picture->Get_WayFile());
                    Vector_MyPicture[i]->Set_Specification_Picture(form_picture->ui->textEdit->toPlainText());
                    break;
                }
              }
          }
      }
  }

  //Обработки нажатия кнокпи Отмена на форме ввода параметров картины
  if(target ==  form_picture->ui->pushButton_2)
  {

      if (event->type() == QEvent::MouseButtonPress)
      {
          //поиск и удаление линии картины на области рисования
          QList<QGraphicsItem *> list;
          list = scene.items();
          QVector <QGraphicsItem *>  Vector = list.toVector();
          int size = Vector.size();
          for(int i = 0; i < size; i++)
          {
              if(Vector[i] == line_picture)
              {
                  scene.removeItem(Vector[i]);
              }
          }

          //поиск и удаление картины из хранилища
          int size_VP = Vector_MyPicture.size();
          for(int i = 0; i < size_VP; i++)
          {
              if(Vector_MyPicture[i] != NULL)
              {
                if(Vector_MyPicture[i]->Get_Line() == line_picture)
                {
                    delete Vector_MyPicture[i];
                    Vector_MyPicture[i] = NULL;
                    break;
                }
              }
          }
      }
  }




  //Обработки нажатия кнокпи ОК на форме редактирования параметров картины
  if(target ==  form_picture_edit->ui->pushButton)
  {

      if (event->type() == QEvent::MouseButtonPress)
      {
          //поиск и запись месторасположения файла для картины
          int size = Vector_MyPicture.size();
          for(int i = 0; i < size; i++)
          {
              if(Vector_MyPicture[i] != NULL)
              {
                if(Vector_MyPicture[i]->Get_Line() == line_picture)
                {
                   Vector_MyPicture[i]->Set_WayFile(form_picture_edit->ui->label_2->text());
                   Vector_MyPicture[i]->Set_Specification_Picture(form_picture_edit->ui->textEdit->toPlainText());
                   break;
                }
              }
          }
      }
  }

  return QDialog::eventFilter(target, event);
}



Dialog::~Dialog()
{
    delete ui;
}

void Dialog::Edit_param_wall()
{
    int size = Vector_MyWall.size();
    for(int i = 0; i < size; i++)
    {
        if(Vector_MyWall[i] != NULL)
        {
            if(Vector_MyWall[i]->Get_Line() == line_wall)
            {
                form_wall_edit->ui->doubleSpinBox->setValue(Vector_MyWall[i]->Get_Height());
                QPalette p = form_wall_edit->ui->graphicsView->palette();
                p.setColor(form_wall_edit->ui->graphicsView->backgroundRole(), Vector_MyWall[i]->Get_Color());
                form_wall_edit->ui->graphicsView->setPalette(p);
                form_wall_edit->show();
            }
        }
    }
}

void Dialog::Delete_wall()
{
    QList<QGraphicsItem *> list;
    list = scene.items();
    QVector <QGraphicsItem *>  Vector_Graphics = list.toVector();
    int size_VG = Vector_Graphics.size();
    int size_VW = Vector_MyWall.size();
    for(int i = 0; i < size_VG; i++)
    {
        if(Vector_Graphics[i] == line_wall)
        {
            scene.removeItem(Vector_Graphics[i]);
            break;
        }
    }
    for(int i = 0; i < size_VW; i++)
    {
        if(Vector_MyWall[i] != NULL)
        {
            if(Vector_MyWall[i]->Get_Line() == line_wall)
            {
                delete Vector_MyWall[i];
                Vector_MyWall[i] = NULL;
                break;
            }
        }
    }
}



void Dialog::Edit_param_picture()
{
    int size = Vector_MyPicture.size();
    for(int i = 0; i < size; i++)
    {
        if(Vector_MyPicture[i] != NULL)
        {
            if(Vector_MyPicture[i]->Get_Line() == line_picture)
            {
                form_picture_edit->ui->label_2->setText(Vector_MyPicture[i]->Get_WayFile());
                form_picture_edit->ui->textEdit->setText(Vector_MyPicture[i]->Get_Specification_Picture());
                form_picture_edit->show();
            }
        }
    }
}

void Dialog::Delete_picture()
{
    QList<QGraphicsItem *> list;
    list = scene.items();
    QVector <QGraphicsItem *>  Vector_Graphics = list.toVector();
    int size_VG = Vector_Graphics.size();
    int size_VP = Vector_MyPicture.size();
    for(int i = 0; i < size_VG; i++)
    {
        if(Vector_Graphics[i] == line_picture)
        {
            scene.removeItem(Vector_Graphics[i]);
            break;
        }
    }
    for(int i = 0; i < size_VP; i++)
    {
        if(Vector_MyPicture[i] != NULL)
        {
            if(Vector_MyPicture[i]->Get_Line() == line_picture)
            {
                delete Vector_MyPicture[i];
                Vector_MyPicture[i] = NULL;
                break;
            }
        }
    }
}

void Dialog::Delete_Point_Origin()
{
    QList<QGraphicsItem *> list;
    list = scene.items();
    QVector <QGraphicsItem *>  Vector_Graphics = list.toVector();
    int size_VG = Vector_Graphics.size();
    for(int i = 0; i < size_VG; i++)
    {
        if(Vector_Graphics[i] == Point_Origin)
        {
            scene.removeItem(Vector_Graphics[i]);
            break;
        }
    }

    delete Point_Origin;

    Flag_for_OriginPoint = false;
    flag_for_OriginPoint = false;
}



