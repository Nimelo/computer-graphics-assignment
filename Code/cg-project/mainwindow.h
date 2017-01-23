#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setView(MainView* view);
    ~MainWindow();

private slots:
    void on_actionRot_45_about_y_triggered();

    void on_actionRot_45_about_x_triggered();

    void on_actionRot_45_about_z_triggered();

private:
    Ui::MainWindow *ui;
    MainView* view;
};

#endif // MAINWINDOW_H
