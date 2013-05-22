#-------------------------------------------------
#
# Project created by QtCreator 2013-04-04T14:49:35
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_dialog
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    form_wall.cpp \
    form_picture.cpp \
    my_wall.cpp \
    my_picture.cpp \
    glw.cpp

HEADERS  += dialog.h \
    form_wall.h \
    form_picture.h \
    my_wall.h \
    my_picture.h \
    glw.h

FORMS    += dialog.ui \
    form_wall.ui \
    form_picture.ui


