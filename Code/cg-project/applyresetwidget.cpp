#include "applyresetwidget.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>

ApplyResetWidget::ApplyResetWidget(QWidget *parent) : QWidget(parent)
{
    create();
}

void ApplyResetWidget::create()
{
    auto groupBox = new QGroupBox("Actions");
    auto boxLayout = new QHBoxLayout;

    groupBox->setLayout(boxLayout);

    this->applyButton = new QPushButton("Apply");
    this->resetButton = new QPushButton("Reset");

    boxLayout->addWidget(applyButton);
    boxLayout->addWidget(resetButton);

    auto layout = new QHBoxLayout;
    layout->addWidget(groupBox);

    setLayout(layout);
}
