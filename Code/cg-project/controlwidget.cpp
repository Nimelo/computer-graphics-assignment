#include "controlwidget.h"

#include "tripplespinboxxyz.h"
#include "rotationxyzwidget.h"
#include "applyresetwidget.h"
#include "QVBoxLayout"
#include "QGroupBox"

ControlWidget::ControlWidget(QWidget *parent) : QWidget(parent)
{
    create();
}

void ControlWidget::create()
{
    auto groupBox = new QGroupBox("Controls");
    auto hLayout = new QVBoxLayout;

    this->rotationWidget = new RotationXYZWidget();
    this->eyeWidget = new TrippleSpinBoxXYZ("Eye Position");
    this->directionWidget = new TrippleSpinBoxXYZ("View Vector");
    this->applyResetWidget = new ApplyResetWidget();

    hLayout->addWidget(rotationWidget);
    hLayout->addWidget(eyeWidget);
    hLayout->addWidget(directionWidget);
    hLayout->addWidget(applyResetWidget);

    groupBox->setLayout(hLayout);

    auto layout = new QVBoxLayout;
    layout->addWidget(groupBox);

    setLayout(layout);
}
