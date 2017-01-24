#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSplitter>
#include <QHBoxLayout>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setView(MainView *view, ControlWidget *controlWidget)
{
    this->view = view;
    this->controlWidget = controlWidget;

    auto splitter = new QHBoxLayout;
    QSizePolicy leftPolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    leftPolicy.setHorizontalStretch(8);
    view->setSizePolicy(leftPolicy);

    QSizePolicy rightPolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    leftPolicy.setHorizontalStretch(2);
    controlWidget->setSizePolicy(rightPolicy);

    splitter->addWidget(view);
    splitter->addWidget(controlWidget);

    QWidget * widget = new QWidget();
    widget->setLayout(splitter);

    setCentralWidget(widget);

    this->setMinimumHeight(600);
    this->setMinimumWidth(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRot_45_about_y_triggered()
{
    view->setRotAxis(45,0,1,0);
}

void MainWindow::on_actionRot_45_about_x_triggered()
{
     view->setRotAxis(45,1,0,0);
}

void MainWindow::on_actionRot_45_about_z_triggered()
{
     view->setRotAxis(45,0,0,1);
}
