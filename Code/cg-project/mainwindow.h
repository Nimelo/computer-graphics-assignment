#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainview.h"
#include "controlwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setView(MainView* view, ControlWidget * controlWidget);
    ~MainWindow();
private:
    void rotateXYZ(double x, double y, double z);
    void setUpConnections();
private slots:
    void onApplyPositionClick();
    void onResetPositionClick();
    void onApplyRotationClick();
    void onResetRotationCLick();

    void on_actionRot_45_about_y_triggered();

    void on_actionRot_45_about_x_triggered();

    void on_actionRot_45_about_z_triggered();

private:
    Ui::MainWindow *ui;
    MainView* view;
    ControlWidget * controlWidget;

};

#endif // MAINWINDOW_H
