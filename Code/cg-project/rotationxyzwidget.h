#ifndef ROTATIONXYZWIDGET_H
#define ROTATIONXYZWIDGET_H

#include <QWidget>
#include <QSlider>

#include "xyztuple.h"

class RotationXYZWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RotationXYZWidget(QWidget *parent = 0);
    XYZTuple getCurrentValues();
private:
    void create();
    QSlider * getSlider(int from, int to);
    QSlider * xSlider;
    QSlider * ySlider;
    QSlider * zSlider;
signals:

public slots:
};

#endif // ROTATIONXYZWIDGET_H
