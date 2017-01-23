#-------------------------------------------------
#
# Project created by QtCreator 2017-01-23T19:38:03
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

TARGET = cg-project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    glslprogram.cpp \
    glutils.cpp \
    mainview.cpp \
    scenebasic.cpp

HEADERS  += mainwindow.h \
    glslprogram.h \
    glutils.h \
    mainview.h \
    scene.h \
    scenebasic.h \
    ui_mainwindow.h

FORMS    += mainwindow.ui

win32: LIBS += -L$$PWD/./ -lglew32 -lopengl32 -lglu32

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
