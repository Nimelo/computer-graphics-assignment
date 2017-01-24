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
    auto boxLayout = new QHBoxLayout;

    this->applyButton = new QPushButton("Apply");
    this->resetButton = new QPushButton("Reset");

    boxLayout->addWidget(applyButton);
    boxLayout->addWidget(resetButton);

    setLayout(boxLayout);
}
