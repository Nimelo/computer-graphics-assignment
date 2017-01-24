#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSplitter>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <iostream>

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

    this->setUpConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rotateXYZ(double x, double y, double z)
{
    view->setRotAxis(x, 1, 0, 0);
    view->setRotAxis(y, 0, 1, 0);
    view->setRotAxis(z, 0, 0, 1);
}

void MainWindow::setUpConnections()
{
   auto applyButton = this->controlWidget->getApplyResetWidget()->getApplyButton();
   connect(applyButton, SIGNAL (released()), this, SLOT (onApplyClick()));
}

void MainWindow::onApplyClick()
{
    auto currentValues = this->controlWidget->getCurrentValues();
    auto rotation = currentValues.rotation;
    std::cout << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;
    this->rotateXYZ(rotation.x, rotation.y, rotation.z);
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
