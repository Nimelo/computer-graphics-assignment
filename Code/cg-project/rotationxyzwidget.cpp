#include "rotationxyzwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QGroupBox>
#include <QBoxLayout>
#include <QFormLayout>

RotationXYZWidget::RotationXYZWidget(QWidget *parent) : QWidget(parent)
{
    create();
}

void RotationXYZWidget::create()
{
    auto formLayout = new QFormLayout;
    auto groupBox = new QGroupBox("Rotation");

    this->xSlider = this->getSlider(0, 360);
    this->ySlider = this->getSlider(0, 360);
    this->zSlider = this->getSlider(0, 360);

    formLayout->addRow(new QLabel("X"), xSlider);
    formLayout->addRow(new QLabel("Y"), ySlider);
    formLayout->addRow(new QLabel("Z"), zSlider);

    groupBox->setLayout(formLayout);

    auto layout = new QHBoxLayout;
    layout->addWidget(groupBox);

    setLayout(layout);
}

QSlider *RotationXYZWidget::getSlider(int from, int to)
{
    QSlider * slider = new QSlider(Qt::Orientation::Horizontal);

    slider->setMaximum(to);
    slider->setMinimum(from);
    slider->setValue((double)(to - from) / 2);

    return slider;
}
