#ifndef ROTATIONBYLINEWIDGET_H
#define ROTATIONBYLINEWIDGET_H

#include <QWidget>
#include <QSlider>
#include "tripplespinboxxyz.h"
#include "xyztuple.h"

class RotationByLineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RotationByLineWidget(QWidget *parent = 0);
    XYZTuple getCurrentAPoint();
    XYZTuple getCurrentBPoint();
    double getCurrentAngle();
private:
    void create();
    QDoubleSpinBox * getQDoubleSpinBox(int from, int to);
    QDoubleSpinBox * angle;
    TrippleSpinBoxXYZ * aPoint;
    TrippleSpinBoxXYZ * bPoint;
signals:

public slots:
};

#endif // ROTATIONBYLINEWIDGET_H
