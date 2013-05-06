#include "glw.h"
#include <QtGui/QApplication>
#include <qmessagebox.h>
#include "math.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/GLAUX.H>
#include "glext.h"
#include <QFile>

#define PI 3.14159265


GLW::GLW()
{
    startTimer(11 ); //64-65fps

    nSca = 1;

    col = 0;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    xTra = 0;
    yTra = -0.5;
    zTra = 5;

 ///////////////////////.начинаем подгружать текстуры и информацию о картинах///////////////////////.
   // QFile file1("C:\\image\\textur1.txt");
    //s1 = "C:\\image\\01.jpg";
   // QString str = QFileDialog::getOpenFileName(0,"OpenFile"," ","*.txt");


    QFile file("C://res//textur1.txt");

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия для чтения";
        textur1 = "C:\\image\\no_images.jpg";
    }
    textur1 = file.readAll();

    QFile file2("C://res//textur2.txt");

    if(!file2.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия для чтения";
        textur2 = "C:\\image\\no_images.jpg";
    }
    textur2 = file2.readAll();

    QFile file3("C://res//textur3.txt");

    if(!file3.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия для чтения";
        textur3 = "C:\\image\\no_images.jpg";
    }
    textur3 = file3.readAll();

    QFile file4("C://res//textur4.txt");

    if(!file4.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия для чтения";
        textur4 = "C:\\image\\no_images.jpg";
    }
    textur4 = file4.readAll();

    QFile file5("C://res//textur5.txt");

    if(!file5.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия для чтения";
        textur5 = "C:\\image\\no_images.jpg";
    }
    textur5 = file5.readAll();

    QFile file6("C://res//textur6.txt");

    if(!file6.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия для чтения";
        textur6 = "C:\\image\\no_images.jpg";
    }
    textur6 = file6.readAll();

    QFile file7("C://res//textur7.txt");

    if(!file7.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия для чтения";
        textur7 = "C:\\image\\no_images.jpg";
    }
    textur7 = file7.readAll();

    QFile file8("C://res//textur8.txt");

    if(!file8.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия для чтения";
        textur8 = "C:\\image\\no_images.jpg";
    }
    textur8 = file8.readAll();

    QFile file9("C://res//textur9.txt");

    if(!file9.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия для чтения";
        textur9 = "C:\\image\\no_images.jpg";
    }
    textur9 = file9.readAll();

    QFile file10("C://res//textur10.txt");

    if(!file10.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия для чтения";
        textur10 = "C:\\image\\no_images.jpg";
    }
    textur10 = file10.readAll();

    QFile file11("C://res//textur11.txt");

    if(!file11.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия для чтения";
        textur11 = "C:\\image\\no_images.jpg";
    }
    textur11 = file11.readAll();

    QFile file12("C://res//textur12.txt");

    if(!file12.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия для чтения";
        textur12 = "C:\\image\\no_images.jpg";
    }
    textur12 = file12.readAll();

    QFile file13("C://res//textur13.txt");

    if(!file13.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия для чтения";
        textur13 = "C:\\image\\no_images.jpg";
    }
    textur13 = file13.readAll();

///////////////////////.///////////////////////.///////////////////////.///////////////////////.
   // QMessageBox::information(0, s1);

    color_1 = 152;
    color_2 = 251;
    color_3 = 152;
}
void GLW::initializeGL()
{
    //initialization of OpenGL

    glClearColor(0.85f, 0.77f, 0.76f, 0.66f);
    //resizeGL( 10 , 10 );

    //glShadeModel( GL_SMOOTH );
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_DEPTH_TEST );
   // glEnable(GL_CULL_FACE);

    startTextur();


}

void GLW::paintGL()
{
    //draw scene here

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    /*glRotatef( m_xRotate, 0.5, 0, 0 );
    glRotatef( m_yRotate, 0, 0.5, 0 );
    glRotatef( m_zRotate, 0, 0, 1 );

    glTranslated(AA, YY, WW);*/

   // glScalef(nSca, nSca, nSca);

    glRotatef(xRot, 0.5f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 0.5f, 0.0f);
   // glRotatef(zRot, 0.0f, 0.0f, 1.0f);

     glTranslatef(xTra, yTra, zTra);

     glEnable( GL_CULL_FACE );


     glColor3ub( 139, 58 ,58  );
     glBegin(GL_POLYGON);
       glVertex3f(-10,0,-10);
       glVertex3f(-10,0,0);
       glVertex3f(10,0,0);
       glVertex3f(10,0,-10);
     glEnd();
     glDisable( GL_CULL_FACE );

     glBindTexture(GL_TEXTURE_2D, textureID[0]);
     //01
     glBegin(GL_POLYGON);
     glColor3ub( 255.0f,255.0f,255.0f );
     glTexCoord2f(0,0);
     glVertex3f(-9,0.2f,-10);
     glTexCoord2f(0,1);
     glVertex3f(-9,1,-10);
     glTexCoord2f(1,1);
     glVertex3f(-8,1,-10);
     glTexCoord2f(1,0);
     glVertex3f(-8,0.2f,-10);
     glEnd();
     glBindTexture(GL_TEXTURE_2D, textureID[2]);
     //02
     glBegin(GL_POLYGON);
     glColor3ub( 255.0f,255.0f,255.0f );
     glTexCoord2f(0,0);
     glVertex3f(-7,0.2f,-10);
     glTexCoord2f(0,1);
     glVertex3f(-7,1,-10);
     glTexCoord2f(1,1);
     glVertex3f(-6,1,-10);
     glTexCoord2f(1,0);
     glVertex3f(-6,0.2f,-10);
     glEnd();

     glBindTexture(GL_TEXTURE_2D, textureID[3]);
     //03
     glBegin(GL_POLYGON);
     glColor3ub( 255.0f,255.0f,255.0f );
     glTexCoord2f(0,0);
     glVertex3f(-5,0.2f,-10);
     glTexCoord2f(0,1);
     glVertex3f(-5,1,-10);
     glTexCoord2f(1,1);
     glVertex3f(-4,1,-10);
     glTexCoord2f(1,0);
     glVertex3f(-4,0.2f,-10);
     glEnd();

     glBindTexture(GL_TEXTURE_2D, textureID[4]);
     //04
     glBegin(GL_POLYGON);
     glColor3ub( 255.0f,255.0f,255.0f );
     glTexCoord2f(0,0);
     glVertex3f(-3,0.2f,-10);
     glTexCoord2f(0,1);
     glVertex3f(-3,2,-10);
     glTexCoord2f(1,1);
     glVertex3f(0,2,-10);
     glTexCoord2f(1,0);
     glVertex3f(0,0.2f,-10);
     glEnd();

     glBindTexture(GL_TEXTURE_2D, textureID[5]);
     //05
     glBegin(GL_POLYGON);
     glColor3ub( 255.0f,255.0f,255.0f );
     glTexCoord2f(0,0);
     glVertex3f(1,0.2f,-10);
     glTexCoord2f(0,1);
     glVertex3f(1,1,-10);
     glTexCoord2f(1,1);
     glVertex3f(2,1,-10);
     glTexCoord2f(1,0);
     glVertex3f(2,0.2f,-10);
     glEnd();

     glBindTexture(GL_TEXTURE_2D, textureID[6]);
     //06
     glBegin(GL_POLYGON);
     glColor3ub( 255.0f,255.0f,255.0f );
     glTexCoord2f(0,0);
     glVertex3f(3,0.2f,-10);
     glTexCoord2f(0,1);
     glVertex3f(3,2,-10);
     glTexCoord2f(1,1);
     glVertex3f(7,2,-10);
     glTexCoord2f(1,0);
     glVertex3f(7,0.2f,-10);
     glEnd();

     glBindTexture(GL_TEXTURE_2D, textureID[7]);
     //07
     glBegin(GL_POLYGON);
     glColor3ub( 255.0f,255.0f,255.0f );
     glTexCoord2f(0,0);
     glVertex3f(-9,0.2f,0);
     glTexCoord2f(0,1);
     glVertex3f(-9,1,0);
     glTexCoord2f(1,1);
     glVertex3f(-8,1,0);
     glTexCoord2f(1,0);
     glVertex3f(-8,0.2f,0);
     glEnd();

     glBindTexture(GL_TEXTURE_2D, textureID[8]);
     //08
     glBegin(GL_POLYGON);
     glColor3ub( 255.0f,255.0f,255.0f );
     glTexCoord2f(0,0);
     glVertex3f(-7,0.2f,0);
     glTexCoord2f(0,1);
     glVertex3f(-7,2,0);
     glTexCoord2f(1,1);
     glVertex3f(-5,2,0);
     glTexCoord2f(1,0);
     glVertex3f(-5,0.2f,0);
     glEnd();

     glBindTexture(GL_TEXTURE_2D, textureID[9]);
     //09
     glBegin(GL_POLYGON);
     glColor3ub( 255.0f,255.0f,255.0f );
     glTexCoord2f(0,0);
     glVertex3f(-3,0.2f,0);
     glTexCoord2f(0,1);
     glVertex3f(-3,1,0);
     glTexCoord2f(1,1);
     glVertex3f(-1,1,0);
     glTexCoord2f(1,0);
     glVertex3f(-1,0.2f,0);
     glEnd();

     glBindTexture(GL_TEXTURE_2D, textureID[10]);
     //10
     glBegin(GL_POLYGON);
     glColor3ub( 255.0f,255.0f,255.0f );
     glTexCoord2f(0,0);
     glVertex3f(0,0.2f,0);
     glTexCoord2f(0,1);
     glVertex3f(0,1,0);
     glTexCoord2f(1,1);
     glVertex3f(2,1,0);
     glTexCoord2f(1,0);
     glVertex3f(2,0.2f,0);
     glEnd();

     glBindTexture(GL_TEXTURE_2D, textureID[11]);
     //07
     glBegin(GL_POLYGON);
     glColor3ub( 255.0f,255.0f,255.0f );
     glTexCoord2f(0,0);
     glVertex3f(3,0.2f,0);
     glTexCoord2f(0,1);
     glVertex3f(3,1,0);
     glTexCoord2f(1,1);
     glVertex3f(4,1,0);
     glTexCoord2f(1,0);
     glVertex3f(4,0.2f,0);
     glEnd();

     glBindTexture(GL_TEXTURE_2D, textureID[12]);
     //07
     glBegin(GL_POLYGON);
     glColor3ub( 255.0f,255.0f,255.0f );
     glTexCoord2f(0,0);
     glVertex3f(5,0.2f,0);
     glTexCoord2f(0,1);
     glVertex3f(5,1.5f,0);
     glTexCoord2f(1,1);
     glVertex3f(6,1.5f,0);
     glTexCoord2f(1,0);
     glVertex3f(6,0.2f,0);
     glEnd();

     glBindTexture(GL_TEXTURE_2D, textureID[13]);
     //07
     glBegin(GL_POLYGON);
     glColor3ub( 255.0f,255.0f,255.0f );
     glTexCoord2f(0,0);
     glVertex3f(7,0.2f,0);
     glTexCoord2f(0,1);
     glVertex3f(7,2,0);
     glTexCoord2f(1,1);
     glVertex3f(8,2,0);
     glTexCoord2f(1,0);
     glVertex3f(8,0.2f,0);
     glEnd();

     glBegin(GL_POLYGON);

     glColor3ub( 245.0f,255.0f,250.0f );
     glVertex3f(-10,0,-10.1);
     glVertex3f(-10,5,-10.1);
     glVertex3f(10,5,-10.1);
     glVertex3f(10,0,-10.1);
     glEnd();

     glBegin(GL_POLYGON);
     glColor3ub( 245.0f,255.0f,250.0f );
     glVertex3f(10,0,-10);
     glVertex3f(10,5,-10);
     glVertex3f(10,5,0);
     glVertex3f(10,0,0);
     glEnd();

     glBegin(GL_POLYGON);
     glColor3ub( 245.0f,255.0f,250.0f );
     glVertex3f(10,0,0.1);
     glVertex3f(10,5,0.1);
     glVertex3f(-10,5,0.1);
     glVertex3f(-10,0,0.1);
     glEnd();

     glBegin(GL_POLYGON);
     glColor3ub( 245.0f,255.0f,250.0f );
     glVertex3f(-10,0,0);
     glVertex3f(-10,5,0);
     glVertex3f(-10,5,-10);
     glVertex3f(-10,0,-10);
     glEnd();

     glBegin(GL_POLYGON);
     glColor3ub( 255.0f,248.0f,220.0f );
     glVertex3f(-10,5,-10);
     glVertex3f(10,5,-10);
     glVertex3f(10,5,0);
     glVertex3f(-10,5,0);
     glEnd();


 }
void GLW::resizeGL(int width, int height)
{
     glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLfloat)width/(GLfloat)height, 0.01f, 1000.0f);

    //-- показывает направление откуда и куда смотреть на сцену ----////
    //glMatrixMode (GL_MODELVIEW);
    //gluLookAt (150, 150, 150, 0, 0, 0, 0, 100, 0);

    glMatrixMode(GL_MODELVIEW);
}
void GLW::mousePressEvent(QMouseEvent *event)
{
    m_ptPosition = event->pos();
   // QMessageBox::information(0, "Information", "Operation Complete");


}

void GLW::keyPressEvent(QKeyEvent* pe)
{
    qDebug() << pe->key();
   switch (pe->key())
   {
       case Qt::Key_W:
          step_forward();
       break;

       case Qt::Key_S:
         step_back();
       break;

       case Qt::Key_A:
         step_left();
       break;

       case Qt::Key_D:
         step_right();
       break;
   }

   updateGL();
}
void GLW::step_forward()
{
    zTra += cos(-yRot*PI/180) * 0.05;
    xTra += sin(-yRot*PI/180) * 0.05;

    qDebug() << yRot << " X_grad ";
    qDebug() << cos(-yRot*PI/180) * 0.05 << " X_step ";
    qDebug() << xTra << " X ";
    qDebug()<< "____________________________________";
    qDebug() << yRot << " Z_grad ";
    qDebug() << cos(-yRot*PI/180) * 0.05 << " Z_step ";
    qDebug() << zTra << " Z ";
}

void GLW::step_back()
{
    zTra -= cos(-yRot*PI/180) * 0.05;
    xTra -= sin(-yRot*PI/180) * 0.05;

    qDebug() << yRot << " X_grad ";
    qDebug() << cos(-yRot*PI/180) * 0.05 << " X_step ";
    qDebug() << xTra << " X ";
    qDebug()<< "____________________________________";
    qDebug() << yRot << " Z_grad ";
    qDebug() << cos(-yRot*PI/180) * 0.05 << " Z_step ";
    qDebug() << zTra << " Z ";
}

void GLW::step_left()
{
    zTra += cos((-yRot+90)*PI/180) * 0.05;
    xTra += sin((-yRot+90)*PI/180) * 0.05;

    qDebug() << yRot << " X_grad ";
    qDebug() << cos(-yRot*PI/180) * 0.05 << " X_step ";
    qDebug() << xTra << " X ";
    qDebug()<< "____________________________________";
    qDebug() << yRot << " Z_grad ";
    qDebug() << cos(-yRot*PI/180) * 0.05 << " Z_step ";
    qDebug() << zTra << " Z ";
}

void GLW::step_right()
{
    zTra += cos((-yRot-90)*PI/180) * 0.05;
    xTra += sin((-yRot-90)*PI/180) * 0.05;

    qDebug() << yRot << " X_grad ";
    qDebug() << cos(-yRot*PI/180) * 0.05 << " X_step ";
    qDebug() << xTra << " X ";
    qDebug()<< "____________________________________";
    qDebug() << yRot << " Z_grad ";
    qDebug() << cos(-yRot*PI/180) * 0.05 << " Z_step ";
    qDebug() << zTra << " Z ";
}

void GLW::mouseMoveEvent(QMouseEvent *event)
{
    xRot += 180 * (GLfloat)(event->y() - m_ptPosition.y())/ height();
    yRot += 180 * (GLfloat)(event->x() - m_ptPosition.x())/ width();

    m_ptPosition = event->pos();

    qDebug() << "x = " << xRot << "/n y = " << yRot;

    updateGL();
}

void GLW::wheelEvent(QWheelEvent* pe)
{
    qDebug() << "mouse";
   if ((pe->delta())>0) scale_plus(); else if ((pe->delta())<0) scale_minus();

   updateGL();
}

void GLW::scale_plus()
{
   nSca = nSca*1.1;
}

void GLW::scale_minus()
{
   nSca = nSca/1.1;
}

void GLW::timerEvent(QTimerEvent *event){
     updateGL();
}

int GLW::get(){
    return WW;
}
void GLW::setW(){
    if(WW < 9.5)
    WW+=0.5;
 updateGL();
}
void GLW::setA(){
    if(AA < 9.5)
    AA+=0.5;
 updateGL();
}

void GLW::setS(){
    if(WW > 0.5)
    WW-=0.5;
 updateGL();
}

void GLW::setD(){
    if(AA > -9.5)
    AA-=0.5;
 updateGL();
}
void GLW::setY(){
    if(YY >= -4.0)
    YY-=0.5;
 updateGL();
}
void GLW::setYminis(){
    if(YY < -0.5)
    YY+=0.5;
 updateGL();
}
int GLW::getX(){
    return AA;
}

int GLW::getZ(){
    return WW;
}

void GLW::startTextur()
{
    textureID[0]=bindTexture(QPixmap(QString(textur1)), GL_TEXTURE_2D);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
     textureID[1]=bindTexture(QPixmap(QString("C:\\image\\picture1.jpg")), GL_TEXTURE_2D);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   textureID[2]=bindTexture(QPixmap(QString(textur2)), GL_TEXTURE_2D);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      textureID[3]=bindTexture(QPixmap(QString(textur3)), GL_TEXTURE_2D);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
     textureID[4]=bindTexture(QPixmap(QString(textur4)), GL_TEXTURE_2D);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   textureID[5]=bindTexture(QPixmap(QString(textur5)), GL_TEXTURE_2D);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

     textureID[6]=bindTexture(QPixmap(QString(textur6)), GL_TEXTURE_2D);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//////////
       textureID[7]=bindTexture(QPixmap(QString(textur7)), GL_TEXTURE_2D);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

         textureID[8]=bindTexture(QPixmap(QString(textur8)), GL_TEXTURE_2D);
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

           textureID[9]=bindTexture(QPixmap(QString(textur9)), GL_TEXTURE_2D);
             glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
             glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

             textureID[10]=bindTexture(QPixmap(QString(textur10)), GL_TEXTURE_2D);
               glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
               glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

               textureID[11]=bindTexture(QPixmap(QString(textur11)), GL_TEXTURE_2D);
                 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                 textureID[12]=bindTexture(QPixmap(QString(textur12)), GL_TEXTURE_2D);
                   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                   textureID[13]=bindTexture(QPixmap(QString(textur13)), GL_TEXTURE_2D);
                     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}
