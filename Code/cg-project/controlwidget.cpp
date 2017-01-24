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

    this->rotationWidget = new RotationByLineWidget(XYZTuple(1,0,0), XYZTuple(1,0,0), 30.0);
    this->eyeWidget = new TrippleSpinBoxXYZ("Eye Position", 0, 0, 2);
    this->directionWidget = new TrippleSpinBoxXYZ("View Vector", 0, 0, -1);
    this->applyResetRotationWidget = new ApplyResetWidget();
    this->applyResetPositionWidget = new ApplyResetWidget();

    auto rotationGroupLayout = new QGroupBox("Rotation");
    auto rotationLayout = new QVBoxLayout;

    rotationGroupLayout->setLayout(rotationLayout);

    rotationLayout->addWidget(rotationWidget);
    rotationLayout->addWidget(applyResetRotationWidget);

    vLayout->addWidget(rotationGroupLayout);

    auto hLayout = new QHBoxLayout;
    auto positionGroupBox = new QGroupBox("View Point");

    hLayout->addWidget(eyeWidget);
    hLayout->addWidget(directionWidget);

    auto positionWidget = new QWidget;
    positionWidget->setLayout(hLayout);
    auto positionLayout = new QVBoxLayout;

    positionLayout->addWidget(positionWidget);
    positionLayout->addWidget(applyResetPositionWidget);

    positionGroupBox->setLayout(positionLayout);
    vLayout->addWidget(positionGroupBox);
    groupBox->setLayout(vLayout);

    auto layout = new QVBoxLayout;
    layout->addWidget(groupBox);

    setLayout(layout);
}
