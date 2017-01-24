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
    explicit RotationByLineWidget(XYZTuple a, XYZTuple b, double angle);
    XYZTuple getCurrentAPoint();
    XYZTuple getCurrentBPoint();
    double getCurrentAngle();
    void setDefaults();
private:
    void create();
    QDoubleSpinBox * getQDoubleSpinBox(int from, int to);
    QDoubleSpinBox * angle;
    TrippleSpinBoxXYZ * aPoint;
    TrippleSpinBoxXYZ * bPoint;

    XYZTuple defaultA;
    XYZTuple defaultB;
    double defaultAngle;
signals:

public slots:
};

#endif // ROTATIONBYLINEWIDGET_H
