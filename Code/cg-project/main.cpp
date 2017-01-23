#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMainWindow>

#include "mainview.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *window = new MainWindow();

    // The main window
    QWidget* win = new QWidget(window);


    QGLFormat format;
    format.setVersion(4,0);
    format.setProfile(QGLFormat::CoreProfile);
    MainView *glView = new MainView(format,window);
    window->setView(glView);

    QVBoxLayout *mainLayout = new QVBoxLayout(win);
    mainLayout->addWidget(glView);
    window->setCentralWidget(win);

   // win->setLayout(mainLayout);
   // win->setWindowTitle("Qt OpenGL Example 3");
    window->show();

    return app.exec();
}

