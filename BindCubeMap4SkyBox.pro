#-------------------------------------------------
#
# Project created by QtCreator 2013-02-05T17:13:47
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BindCubeMap4SkyBox
TEMPLATE = app

LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc
PKGCONFIG += opencv


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h

FORMS    += mainwindow.ui
