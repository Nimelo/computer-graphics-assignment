#include "tripplespinboxxyz.h"

#include <QSlider>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <limits>

TrippleSpinBoxXYZ::TrippleSpinBoxXYZ(const char *groupBoxText, double x, double y, double z)
    : QWidget(0), defaultX(x), defaultY(y), defaultZ(z)
{
    create(groupBoxText);
}

XYZTuple TrippleSpinBoxXYZ::getCurrentValues()
{
    return XYZTuple(xSpinBox->value(), ySpinBox->value(), zSpinBox->value());
}

void TrippleSpinBoxXYZ::setDefaults()
{
    this->xSpinBox->setValue(this->defaultX);
    this->ySpinBox->setValue(this->defaultY);
    this->zSpinBox->setValue(this->defaultZ);
}

void TrippleSpinBoxXYZ::create(const char *groupBoxText)
{
    auto groupBox = new QGroupBox(groupBoxText);
    auto formLayout = new QFormLayout;
    groupBox->setLayout(formLayout);

    this->xSpinBox = this->createQSpinBox();
    this->ySpinBox = this->createQSpinBox();
    this->zSpinBox = this->createQSpinBox();

    formLayout->addRow(new QLabel("X"), this->xSpinBox);
    formLayout->addRow(new QLabel("Y"), this->ySpinBox);
    formLayout->addRow(new QLabel("Z"), this->zSpinBox);

    auto layout = new QHBoxLayout;
    layout->addWidget(groupBox);

    setLayout(layout);
}

QDoubleSpinBox *TrippleSpinBoxXYZ::createQSpinBox()
{
    auto spiner = new QDoubleSpinBox;
    spiner->setMinimum(-1000);
    spiner->setMaximum(+1000);
    return spiner;
}
