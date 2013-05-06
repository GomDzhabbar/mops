/*#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
*/

#include <QApplication>
#include "scene3D.h"
#include "glw.h"

int main(int argc, char** argv)
{
   QApplication app(argc, argv);

   /*Scene3D scene1;
   scene1.setWindowTitle("lecture1");
   scene1.resize(500, 500);
   scene1.show();*/

   GLW gw;
   gw.resize(500,500);
   gw.show();


   return app.exec();
}
