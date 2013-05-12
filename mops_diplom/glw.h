#ifndef GLW_H
#define GLW_H
#include <QGLWidget>
#include <QtOpenGL>
#include "math.h"
#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>

class GLW : public QGLWidget
{
public:
    GLW();

    GLfloat m_xRotate;
    GLfloat m_yRotate;
    GLfloat m_zRotate;


    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;

    GLfloat xTra;
    GLfloat yTra;
    GLfloat zTra;

    GLfloat WW;
    GLfloat AA;
    GLfloat SS;
    GLfloat DD;
    GLfloat YY;
    GLfloat nSca;
    QPoint m_ptPosition;

    ///глобальные переменные с адресами текстур
    QString textur1,textur2,textur3,textur4,textur5,textur6,textur7,textur8,textur9,textur10,textur11,textur12,textur13;
    QString info1,info2,info3,info4,info5,info6,info7,info8,info9,info10,info11,info12,info13;
    ///
    GLuint  textureID[10];

    int color_1,color_2,color_3;
    int i,j;
    int mas[7][8];
    int color_mas[2][2];
    float X,Y,Z;

    float rotX, rotY, rotZ; //i want access these variable so public

    short int col;

    int get();
    int getX();
    int getZ();
    void setW();
    void setA();
    void setS();
    void setD();
    void setY();
    void setYminis();
    void startTextur();
    void resizeGL(int width, int height);
    void scale_plus();
    void scale_minus();
    bool createStart;

    // управление камерой -----//
    void step_forward();
    void step_back();
    void step_left();
    void step_right();
    //-------------------------//
    //  создаем стены   //
    void createWall(int x1, int z1, int x2, int z2, int height, int rgb1, int rgb2, int rgb3);
    void createGalery();
    //-------------------------//

protected:
    void paintGL();
    void initializeGL();
    void wheelEvent(QWheelEvent* pe);
    void keyPressEvent(QKeyEvent* pe);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);
};
#endif // GLW_H
