#include "rotationbylinewidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>


RotationByLineWidget::RotationByLineWidget(XYZTuple a, XYZTuple b, double angle)
    : QWidget(0), defaultA(a), defaultB(b), defaultAngle(angle)
{
    this->create();
}

XYZTuple RotationByLineWidget::getCurrentAPoint()
{
    return aPoint->getCurrentValues();
}

XYZTuple RotationByLineWidget::getCurrentBPoint()
{
    return bPoint->getCurrentValues();
}

double RotationByLineWidget::getCurrentAngle()
{
    return angle->value();
}

void RotationByLineWidget::setDefaults()
{
    aPoint->setDefaults();
    bPoint->setDefaults();
    angle->setValue(defaultAngle);
}

void RotationByLineWidget::create()
{
    auto groupBox = new QGroupBox("Rotation");
    auto vBox = new QVBoxLayout;
    groupBox->setLayout(vBox);

    //xy
    this->aPoint = new TrippleSpinBoxXYZ("A", defaultA.x, defaultA.y, defaultA.z);
    this->bPoint = new TrippleSpinBoxXYZ("B", defaultB.x, defaultB.y, defaultB.z);
    this->angle = this->getQDoubleSpinBox(0, 360);
    this->angle->setValue(defaultAngle);

    //slider

    auto hBox = new QHBoxLayout;
    hBox->addWidget(aPoint);
    hBox->addWidget(bPoint);

    auto widget = new QWidget;
    widget->setLayout(hBox);
    vBox->addWidget(widget);

    auto widgetSlider = new QWidget;
    auto formLayout = new QFormLayout;
    formLayout->addRow("Angle", angle);
    widgetSlider->setLayout(formLayout);

    vBox->addWidget(widgetSlider);

    auto layout = new QHBoxLayout;
    layout->addWidget(groupBox);
    setLayout(layout);
}

QDoubleSpinBox *RotationByLineWidget::getQDoubleSpinBox(int from, int to)
{
    QDoubleSpinBox * spinBox = new QDoubleSpinBox;

    spinBox->setMaximum(to);
    spinBox->setMinimum(from);
    spinBox->setValue(90.0);

    return spinBox;
}
