#include "dialog.h"
#include <QApplication>
#include "glw.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    Dialog w;
//    w.show();
    
//    return a.exec();

    GLW gw;
       gw.resize(500,500);
       gw.show();


       return app.exec();
}
