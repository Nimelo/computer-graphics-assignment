#ifndef TRIPPLESPINBOXXYZ_H
#define TRIPPLESPINBOXXYZ_H

#include <QWidget>
#include <QDoubleSpinBox>
#include "xyztuple.h"

class TrippleSpinBoxXYZ : public QWidget
{
    Q_OBJECT
public:
    TrippleSpinBoxXYZ(const char * groupBoxText, double x, double y, double z);
    XYZTuple getCurrentValues();
    void setDefaults();
    QDoubleSpinBox * xSpinBox;
    QDoubleSpinBox * ySpinBox;
    QDoubleSpinBox * zSpinBox;
private:
    explicit TrippleSpinBoxXYZ(QWidget *parent = 0);

    void create(const char * groupBoxText);
    QDoubleSpinBox * createQSpinBox();

    double defaultX;
    double defaultY;
    double defaultZ;

signals:

public slots:
};

#endif // TRIPPLESPINBOXXYZ_H
