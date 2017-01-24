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

ControlTuple ControlWidget::getCurrentValues()
{
    return ControlTuple(rotationWidget->getCurrentAPoint(),
                        rotationWidget->getCurrentBPoint(),
                        rotationWidget->getCurrentAngle(),
                        eyeWidget->getCurrentValues(),
                        directionWidget->getCurrentValues());
}

void ControlWidget::create()
{
    auto groupBox = new QGroupBox("Controls");
    auto vLayout = new QVBoxLayout;

    this->rotationWidget = new RotationByLineWidget(XYZTuple(1,1,1), XYZTuple(0,0,0), 90.0);
    this->eyeWidget = new TrippleSpinBoxXYZ("Eye Position", 0, 0, 2);
    this->directionWidget = new TrippleSpinBoxXYZ("View Vector", 0, 0, -1);
    this->applyResetRotationWidget = new ApplyResetWidget();
    this->applyResetPositionWidget = new ApplyResetWidget();

    vLayout->addWidget(rotationWidget);
    vLayout->addWidget(applyResetRotationWidget);

    auto hLayout = new QHBoxLayout;

    hLayout->addWidget(eyeWidget);
    hLayout->addWidget(directionWidget);

    auto widget = new QWidget;
    widget->setLayout(hLayout);
    vLayout->addWidget(widget);
    vLayout->addWidget(applyResetPositionWidget);

    groupBox->setLayout(vLayout);

    auto layout = new QVBoxLayout;
    layout->addWidget(groupBox);

    setLayout(layout);
}
