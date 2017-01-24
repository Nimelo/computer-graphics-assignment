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

    this->setMinimumHeight(800);
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
   auto applyPosition = this->controlWidget->applyResetPositionWidget->applyButton;
   connect(applyPosition, SIGNAL (released()), this, SLOT (onApplyPositionClick()));

   auto resetPosition = this->controlWidget->applyResetPositionWidget->resetButton;
   connect(resetPosition, SIGNAL (released()), this, SLOT (onResetPositionClick()));

   auto applyRotation = this->controlWidget->applyResetRotationWidget->applyButton;
   connect(applyRotation, SIGNAL (released()), this, SLOT (onApplyRotationClick()));

   auto resetRotation = this->controlWidget->applyResetRotationWidget->resetButton;
   connect(resetRotation, SIGNAL (released()), this, SLOT (onResetRotationClick()));
}

void MainWindow::onApplyPositionClick()
{
    auto currentValues = this->controlWidget->getCurrentValues();
    this->view->updateView(currentValues.eye, currentValues.direction);
}

void MainWindow::onResetPositionClick()
{
    this->controlWidget->eyeWidget->setDefaults();
    this->controlWidget->directionWidget->setDefaults();
    auto currentValues = this->controlWidget->getCurrentValues();
    this->view->updateView(currentValues.eye, currentValues.direction);
}

void MainWindow::onApplyRotationClick()
{
    auto currentValues = this->controlWidget->getCurrentValues();
    this->view->rotateModel(currentValues.aPoint, currentValues.bPoint, currentValues.angle);
}

void MainWindow::onResetRotationCLick()
{
    this->controlWidget->rotationWidget->setDefaults();

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
