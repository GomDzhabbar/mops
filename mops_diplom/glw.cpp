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


    QFile file("qwe.txt");

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error read";
        textur1 = "C:\\image\\no_images.jpg";
    }
    textur1 = file.readAll();
    qDebug() << textur1;


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

     /*glBindTexture(GL_TEXTURE_2D, textureID[0]);
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
     glBindTexture(GL_TEXTURE_2D, textureID[2]);*/



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
   updateGL();
}

void GLW::timerEvent(QTimerEvent *event){
     updateGL();
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
