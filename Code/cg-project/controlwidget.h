#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include "tripplespinboxxyz.h"
#include "rotationxyzwidget.h"
#include "applyresetwidget.h"
#include "controltuple.h"
#include "rotationbylinewidget.h"

class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = 0);
    ControlTuple getCurrentValues();

    RotationByLineWidget * rotationWidget;
    TrippleSpinBoxXYZ * eyeWidget;
    TrippleSpinBoxXYZ * directionWidget;
    ApplyResetWidget * applyResetRotationWidget;
    ApplyResetWidget * applyResetPositionWidget;
private:
    void create();
signals:

public slots:
};

#endif // CONTROLWIDGET_H
