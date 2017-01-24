#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include "tripplespinboxxyz.h"
#include "rotationxyzwidget.h"
#include "applyresetwidget.h"

class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = 0);
private:
    void create();

    RotationXYZWidget * rotationWidget;
    TrippleSpinBoxXYZ * eyeWidget;
    TrippleSpinBoxXYZ * directionWidget;
    ApplyResetWidget * applyResetWidget;
signals:

public slots:
};

#endif // CONTROLWIDGET_H
