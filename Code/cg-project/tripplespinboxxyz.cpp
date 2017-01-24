#include "tripplespinboxxyz.h"

#include <QSlider>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <limits>

TrippleSpinBoxXYZ::TrippleSpinBoxXYZ(const char *groupBoxText) : QWidget(0)
{
    create(groupBoxText);
}

XYZTuple TrippleSpinBoxXYZ::getCurrentValues()
{
    return XYZTuple(xSpinBox->value(), ySpinBox->value(), zSpinBox->value());
}

TrippleSpinBoxXYZ::TrippleSpinBoxXYZ(QWidget *parent) : QWidget(parent)
{

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

QSpinBox *TrippleSpinBoxXYZ::createQSpinBox()
{
    auto spiner = new QSpinBox;
    spiner->setMinimum(INT_MIN);
    spiner->setMaximum(INT_MAX);
    return spiner;
}
