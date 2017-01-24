#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QMainWindow>
#include <QSpacerItem>

#include "mainview.h"
#include "mainwindow.h"

#include "controlwidget.h"
#include <QSplitter>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *window = new MainWindow();


    QGLFormat format;
    format.setVersion(4,0);
    format.setProfile(QGLFormat::CoreProfile);
    MainView *glView = new MainView(format,window);
    auto control = new ControlWidget();
    window->setView(glView, control);

    window->show();

    return app.exec();
}

